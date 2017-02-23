#include "WaveletReconstructor.h"

#include "Configuration.h"
#include "EqualLoudnessCurve.h"

WaveletReconstructor::WaveletReconstructor(const GridData& gridData)
    : gridData_(gridData),
      minimumFrequency_(Configuration::getMinimumFrequency()),
      binsPerOctave_(Configuration::getBinsPerOctave()),
      windowLength_(Configuration::getReconstructionWindowLength()),
      sampleRate_(44100.0)  // TODO fix this
{
  createBinInformation();
}

void WaveletReconstructor::reinitialize()
{
  minimumFrequency_ = Configuration::getMinimumFrequency();
  binsPerOctave_ = Configuration::getBinsPerOctave();
  windowLength_ = Configuration::getReconstructionWindowLength();
  createBinInformation();
}

void WaveletReconstructor::perform(AudioSampleBuffer& buffer,
                                   const Array<GridPoint>& affectedPoints) const
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
  buffer.clear(minX * windowLength_, (maxX - minX) * windowLength_);
  performInternal(buffer, minX, maxX);
}

void WaveletReconstructor::perform(AudioSampleBuffer& buffer) const
{
  DBG("Full reconstruction started");
  buffer.clear();
  performInternal(buffer, 0, gridData_.getWidth());
}

void WaveletReconstructor::performInternal(AudioSampleBuffer& buffer, const int minX,
                                           const int maxX) const
{
  jassert(waveTables_.size() == gridData_.getHeight());

  // Work one frequency (row) at a time.
  for (int y = 0; y < gridData_.getHeight(); ++y)
  {
    // Information for the frequency/row.
    const auto& binInformation = waveTables_.getReference(waveTables_.size() - y - 1);
    const Array<float>& waveTable = binInformation.Waveform;
    const auto waveTableLength = waveTable.size();
    const auto cycleLength = binInformation.CycleLength;

    // At the start of each row, initially ramp from zero.
    float previousValue = minX == 0 ? 0.0f : gridData_.getXY(minX - 1, y);

    // Now work across the GridData left to right.
    for (int x = minX; x < maxX; ++x)
    {
      auto value = gridData_.getXY(x, y);
      // Only write something when the current or previous value is non-zero.
      if (previousValue > minThreshold || value > minThreshold)
      {
        auto bufferOffset = x * windowLength_;  // Position in the output
        auto writePtr = buffer.getWritePointer(0, bufferOffset);
        // waveTableOffset ensures that sequential windows have the same continuous waveform.
        int waveTableOffset = (windowLength_ * x) % waveTableLength;
        const int rampLength = jmin(roundToInt(rampTransitionCycles_ * cycleLength), windowLength_);
        float rampFactor = (value - previousValue) / rampLength;
        for (int i = 0; i < rampLength; ++i)  // Ramp smoothly between windows.
        {
          writePtr[i] += waveTable[waveTableOffset] * (previousValue + i * rampFactor);
          waveTableOffset = ++waveTableOffset % waveTableLength;
        }
        if (value > minThreshold)
        {
          for (int i = rampLength; i < windowLength_; ++i)  // Finish out the window.
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
}

void WaveletReconstructor::createBinInformation()
{
  const int numberFrequencies = gridData_.getHeight();
  waveTables_.resize(numberFrequencies);
  for (int i = 0; i < numberFrequencies; ++i)
  {
    BinInformation& binInformation = waveTables_.getReference(i);

    auto freq = minimumFrequency_ * powf(2.0, i / binsPerOctave_);
    jassert(freq < sampleRate_ / 2);

    const float repeatLength = sampleRate_ / freq;
    const int minRequiredTableLength = roundToInt(repeatLength);
    binInformation.CycleLength = minRequiredTableLength;

    const int newWaveTableLength =
        jmax(minRequiredTableLength,
             roundToInt(repeatLength * ceil(minWaveTableLength_ / repeatLength)));
    binInformation.Waveform.resize(newWaveTableLength);

    float scaleFactor = 2.0f * float_Pi * freq / sampleRate_;
    auto freqScaleFactor = globalScalar_ * EqualLoudnessCurve::getScalarForFrequency(freq);
    for (int j = 0; j < newWaveTableLength; ++j)
    {
      binInformation.Waveform.set(j, freqScaleFactor * sinf(static_cast<float>(j) * scaleFactor));
    }

    // std::cout << freq << "\t" << minRequiredTableLength << "\t" << newWaveTableLength
    //           << "\t" << scaleFactor << "\t" << freqScaleFactor << std::endl;
  }
}