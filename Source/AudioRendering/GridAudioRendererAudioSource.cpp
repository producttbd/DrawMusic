#include "GridAudioRendererAudioSource.h"

GridAudioRendererAudioSource::GridAudioRendererAudioSource(
    const GridData& gridData, AudioDataChangedNotifier& audioDataChangedNotifier) noexcept
    : gridData_(gridData),
      readyToPlay_(true),
      fullPieceAudioBuffer_(Configuration::getNumberChannels(),
                            Configuration::getTotalAudioSampleLength()),
      currentOutputOffset_(0),
      audioDataChangedNotifier_(audioDataChangedNotifier),
      reconstructor_(fullPieceAudioBuffer_, gridData, audioDataChangedNotifier)
{
  fullPieceAudioBuffer_.clear();
}

GridAudioRendererAudioSource::~GridAudioRendererAudioSource()
{
}

const AudioSampleBuffer& GridAudioRendererAudioSource::getOutputBuffer() const
{
  return fullPieceAudioBuffer_;
}

void GridAudioRendererAudioSource::reinitialize()
{
  readyToPlay_ = false;
  setNewPlaybackPosition(0);
  reconstructor_.reinitialize();
  fullPieceAudioBuffer_.setSize(Configuration::getNumberChannels(),
                                Configuration::getTotalAudioSampleLength());
  rerenderAll();
}

void GridAudioRendererAudioSource::rerenderAll()
{
  readyToPlay_ = false;
  reconstructor_.perform();
}

void GridAudioRendererAudioSource::rerenderAsNeeded(const Array<GridPoint>& affectedPoints)
{
  readyToPlay_ = false;
  reconstructor_.perform(affectedPoints);
}

void GridAudioRendererAudioSource::setNewPlaybackPosition(float fraction)
{
  setNextReadPosition(static_cast<int64>(getTotalLength() * fraction));
}

// AudioDataChangedNotifier::NewAudioListener
void GridAudioRendererAudioSource::newAudioCallback(const AudioSampleBuffer& /* updatedAudio */)
{
  readyToPlay_ = true;
}

// AudioSource methods
void GridAudioRendererAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
  if (!readyToPlay_)
  {
    rerenderAll();
  }
}

void GridAudioRendererAudioSource::releaseResources()
{
}

void GridAudioRendererAudioSource::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
  // TODO remove this hack
  if (currentOutputOffset_ >= fullPieceAudioBuffer_.getNumSamples())
  {
    setNextReadPosition(0);
  }

  auto readPtr = fullPieceAudioBuffer_.getReadPointer(0, currentOutputOffset_);
  auto leftWritePtr = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
  auto rightWritePtr = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);

  auto endPoint =
      jmin(bufferToFill.numSamples, fullPieceAudioBuffer_.getNumSamples() - currentOutputOffset_);

  for (int i = 0; i < endPoint; ++i)
  {
    leftWritePtr[i] = readPtr[i];
    rightWritePtr[i] = readPtr[i];
  }

  for (int i = endPoint; i < bufferToFill.numSamples; ++i)
  {
    leftWritePtr[i] = 0.0f;
    rightWritePtr[i] = 0.0f;
  }

  setNextReadPosition(currentOutputOffset_ + endPoint);
}

// PositionableAudioSource methods
void GridAudioRendererAudioSource::setNextReadPosition(int64 newPosition)
{
  jassert(newPosition >= 0 && newPosition <= getTotalLength());
  currentOutputOffset_ = newPosition;
  auto fraction = static_cast<float>(newPosition) / static_cast<float>(getTotalLength());
  audioDataChangedNotifier_.callNewPositionListeners(fraction);
}

int64 GridAudioRendererAudioSource::getNextReadPosition() const
{
  return currentOutputOffset_;
}

int64 GridAudioRendererAudioSource::getTotalLength() const
{
  return fullPieceAudioBuffer_.getNumSamples();
}

bool GridAudioRendererAudioSource::isLooping() const
{
  return false;
}

void GridAudioRendererAudioSource::setLooping(bool shouldLoop)
{
  jassert(false);
}
