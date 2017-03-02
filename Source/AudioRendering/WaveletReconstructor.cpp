#include "WaveletReconstructor.h"

#include "../Configuration.h"
#include "BinInformationCalculator.h"

WaveletReconstructor::WaveletReconstructor(AudioSampleBuffer& output, const GridData& gridData,
                                           AudioDataChangedNotifier& notifier)
    : Thread("reconstructor"), notifier_(notifier), buffer_(output), gridData_(gridData)
{
  reinitialize();
}

void WaveletReconstructor::perform()
{
  DBG("Full reconstruction requested");
  requestThreadExitAndWait();
  buffer_.clear();
  range_ = Range<int>(0, gridData_.getWidth());
  startThread();
}

void WaveletReconstructor::perform(const Array<GridPoint>& affectedPoints)
{
  DBG("Partial reconstruction started");
  if (affectedPoints.size() == 0) return;
  int minX = affectedPoints[0].x;
  int maxX = affectedPoints[0].x;
  for (auto& point : affectedPoints)
  {
    minX = jmin(point.x, minX);
    maxX = jmax(point.x, maxX);
  }
  // For the maxX, we actually want two index beyond the maximum, one for ramp down, one because
  // it's an ending index which doesn't get processed.
  maxX = jmin(gridData_.getWidth(), maxX + 2);
  buffer_.clear(minX * config_.WindowLength, (maxX - minX) * config_.WindowLength);
  // If we killed a run in progress, we need to include that old range in the new range.
  range_ = requestThreadExitAndWait() ? range_.getUnionWith(Range<int>(minX, maxX))
                                      : Range<int>(minX, maxX);
  startThread();
}

bool WaveletReconstructor::requestThreadExitAndWait()
{
  if (isThreadRunning())
  {
    DBG("Waiting for thread to exit");
    // Already running, need to re-start
    signalThreadShouldExit();
    if (Thread::waitForThreadToExit(50 /* timeOutMilliseconds */))
    {
      DBG("Thread exited");
    }
    else
    {
      DBG("Thread did not exit!!!");
    }
    return true;
  }
  return false;
}

void WaveletReconstructor::run()
{
  jassert(waveTables_.size() == gridData_.getHeight());

  DBG("Reconstruction start of run()");

  // Work one frequency (row) at a time.
  for (int y = 0; y < gridData_.getHeight(); ++y)
  {
    // Information for the frequency/row.
    const auto& binInformation = waveTables_.getReference(waveTables_.size() - y - 1);
    const Array<float>& waveTable = binInformation.Waveform;
    const auto waveTableLength = waveTable.size();
    const auto cycleLength = binInformation.CycleLength;

    // At the start of each row, initially ramp from zero.
    float previousValue = range_.getStart() == 0 ? 0.0f : gridData_.getXY(range_.getStart() - 1, y);

    // Now work across the GridData left to right.
    for (int x = range_.getStart(); x < range_.getEnd(); ++x)
    {
      if (threadShouldExit())
      {
        return;
      }
      auto value = gridData_.getXY(x, y);
      // Only write something when the current or previous value is non-zero.
      if (previousValue > config_.MinThreshold || value > config_.MinThreshold)
      {
        auto bufferOffset = x * config_.WindowLength;  // Position in the output
        auto writePtr = buffer_.getWritePointer(0, bufferOffset);
        // waveTableOffset ensures that sequential windows have the same continuous waveform.
        int waveTableOffset = (config_.WindowLength * x) % waveTableLength;
        const int rampLength =
            jmin(roundToInt(config_.RampTransitionCycles * cycleLength), config_.WindowLength);
        float rampFactor = (value - previousValue) / rampLength;
        for (int i = 0; i < rampLength; ++i)  // Ramp smoothly between windows.
        {
          writePtr[i] += waveTable[waveTableOffset] * (previousValue + i * rampFactor);
          waveTableOffset = ++waveTableOffset % waveTableLength;
        }
        if (value > config_.MinThreshold)
        {
          for (int i = rampLength; i < config_.WindowLength; ++i)  // Finish out the window.
          {
            writePtr[i] += waveTable[waveTableOffset] * value;
            waveTableOffset = ++waveTableOffset % waveTableLength;
          }
        }
      }
      previousValue = value;
    }
  }
  DBG("Reconstruction finished");
  const MessageManagerLock mml(Thread::getCurrentThread());
  if (!mml.lockWasGained())
  {
    // if something is trying to kill this job, the lock will fail.
    return;
  }
  notifier_.callNewAudioListeners(buffer_);
}

void WaveletReconstructor::reinitialize()
{
  config_ = AudioSystemConfiguration();
  waveTables_ = BinInformationCalculator::getBinInformation(config_, gridData_);
}