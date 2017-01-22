#include "GridAudioRendererAudioSource.h"

#include "Configuration.h"

GridAudioRendererAudioSource::GridAudioRendererAudioSource(const GridData* gridData) noexcept
: gridData_(gridData),
  readyToPlay_(true),
  fullPieceAudioBuffer_(Configuration::getNumberChannels(), Configuration::getTotalAudioSampleLength()),
  currentOutputOffset_(0),
  reconstructor_(gridData)
{
    fullPieceAudioBuffer_.clear();
}

GridAudioRendererAudioSource::~GridAudioRendererAudioSource()
{
}

const AudioSampleBuffer& GridAudioRendererAudioSource::getOutputBuffer()
{
    return fullPieceAudioBuffer_;
}

void GridAudioRendererAudioSource::rerender()
{
    reconstructor_.perform(fullPieceAudioBuffer_);
    readyToPlay_ = true;
    newAudioListeners_.call(&GridAudioRendererAudioSource::NewAudioListener::newAudioCallback,
                            fullPieceAudioBuffer_);
}

void GridAudioRendererAudioSource::addNewAudioListener(
        GridAudioRendererAudioSource::NewAudioListener* listener)
{
    newAudioListeners_.add(listener);
}

void GridAudioRendererAudioSource::removeNewAudioListener(
        GridAudioRendererAudioSource::NewAudioListener* listener)
{
    newAudioListeners_.remove(listener);
}

void GridAudioRendererAudioSource::addNewPositionListener(
        GridAudioRendererAudioSource::NewPositionListener* listener)
{
    newPositionListeners_.add(listener);
}

void GridAudioRendererAudioSource::removeNewPositionListener(GridAudioRendererAudioSource::NewPositionListener* listener)
{
    newPositionListeners_.remove(listener);
}

// ChangeListener method
void GridAudioRendererAudioSource::changeListenerCallback(juce::ChangeBroadcaster* /*source*/)
{
    readyToPlay_ = false;
    rerender();
}

// AudioSource methods
void GridAudioRendererAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    if (!readyToPlay_)
    {
        rerender();
    }
}

void GridAudioRendererAudioSource::releaseResources()
{
}

void GridAudioRendererAudioSource::getNextAudioBlock (const AudioSourceChannelInfo &bufferToFill)
{
    // TODO remove this hack
    if (currentOutputOffset_ >= fullPieceAudioBuffer_.getNumSamples())
    {
        setNextReadPosition(0);
    }
        
    auto readPtr = fullPieceAudioBuffer_.getReadPointer(0, currentOutputOffset_);
    auto leftWritePtr = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto rightWritePtr = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);

    auto endPoint = jmin(bufferToFill.numSamples,
                         fullPieceAudioBuffer_.getNumSamples() - currentOutputOffset_);
    
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
    newPositionListeners_.call(
            &GridAudioRendererAudioSource::NewPositionListener::newPositionCallback, fraction);
}

int64 GridAudioRendererAudioSource::getNextReadPosition () const
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
};
