#include "GridAudioRendererAudioSource.h"

#include <cmath>
#include "Configuration.h"
#include "SimpleSpectrumReconstructor.h"
#include "LimGriffinReconstructor.h"

GridAudioRendererAudioSource::GridAudioRendererAudioSource(const GridData& gridData) noexcept
: gridData_(gridData),
  fft_(Configuration::getFftOrder(), true),
  fullPieceAudioBuffer_(Configuration::getNumberChannels(), Configuration::getTotalAudioSampleLength()),
  currentOutputOffset_(0),
  lgIterations_(0)
{

}

GridAudioRendererAudioSource::~GridAudioRendererAudioSource()
{

}

void GridAudioRendererAudioSource::rerender()
{
    LimGriffinReconstructor reconstructor(Configuration::getFftOrder(), Configuration::getFftLength(), gridData_, lgIterations_);
    reconstructor.perform(fullPieceAudioBuffer_);
    currentOutputOffset_ = 0;
    readyToPlay_ = true;
    listeners_.call(&GridAudioRendererAudioSource::Listener::newAudioCallback,
                    fullPieceAudioBuffer_);
}

void GridAudioRendererAudioSource::addListener(GridAudioRendererAudioSource::Listener* listener)
{
    listeners_.add(listener);
}

void GridAudioRendererAudioSource::removeListener(GridAudioRendererAudioSource::Listener* listener)
{
    listeners_.remove(listener);
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
    auto readPtr = fullPieceAudioBuffer_.getReadPointer(0, currentOutputOffset_);
    auto leftWritePtr = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample); // LEFT CHANNEL
    auto rightWritePtr = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample); // RIGHT CHANNEL

    auto endPoint = jmin(bufferToFill.numSamples,
                         fullPieceAudioBuffer_.getNumSamples() - currentOutputOffset_);
    for (int i = 0; i < endPoint; ++i)
    {
        leftWritePtr[i] = readPtr[i];
        rightWritePtr[i] = readPtr[i];
    }

    for (int i = endPoint; i < bufferToFill.numSamples; ++i)
    {
        leftWritePtr[i] = 0;
        rightWritePtr[i] = 0;
    }

    currentOutputOffset_ += endPoint;
}

// PositionableAudioSource methods
void GridAudioRendererAudioSource::setNextReadPosition (int64 newPosition)
{
    currentOutputOffset_ = newPosition;
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

// Slider::Listener methods
void GridAudioRendererAudioSource::sliderValueChanged(Slider* slider)
{
    lgIterations_ = static_cast<int>(slider->getValue());
}

void GridAudioRendererAudioSource::sliderDragStarted(Slider* slider)
{

}
void GridAudioRendererAudioSource::sliderDragEnded(Slider* slider)
{

}
