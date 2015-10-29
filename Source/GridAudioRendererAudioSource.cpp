/*
 ==============================================================================
 
 GridAudioRendererAudioSource.cpp
 Created: 7 Jul 2015 10:53:53pm
 Author:  Trevor Knight
 
 ==============================================================================
 */

#include "GridAudioRendererAudioSource.h"

#include <cmath>
#include "Configuration.h"
#include "SimpleSpectrumReconstructor.h"
#include "LimGriffinReconstructor.h"

GridAudioRendererAudioSource::GridAudioRendererAudioSource(const GridData& gridData) noexcept
: gridData_(gridData),
  shouldLoop_(false),
  fft_(Configuration::getFftOrder(), true),
  fullPieceAudioBuffer_(Configuration::getNumberChannels(), Configuration::getTotalAudioSampleLength()),
  currentOutputOffset_(0),
  lgIterations_(0)
{
    
}

GridAudioRendererAudioSource::~GridAudioRendererAudioSource()
{
    
}

void GridAudioRendererAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
//    SimpleSpectrumReconstructor reconstructor(Configuration::getFftOrder(),
//                                              Configuration::getFftLength(), gridData_);
//    reconstructor.perform(fullPieceAudioBuffer_);

    LimGriffinReconstructor reconstructor(Configuration::getFftOrder(), Configuration::getFftLength(), gridData_, lgIterations_);
    reconstructor.perform(fullPieceAudioBuffer_);
    currentOutputOffset_ = 0;
}

void GridAudioRendererAudioSource::releaseResources()
{
    
}

void GridAudioRendererAudioSource::getNextAudioBlock (const AudioSourceChannelInfo &bufferToFill)
{
    auto readPtr = fullPieceAudioBuffer_.getReadPointer(0, currentOutputOffset_);
    auto writePtr = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample); // LEFT OR RIGHT OR WHAT? TODO Channel
    
    auto endPoint = jmin(bufferToFill.numSamples,
                         fullPieceAudioBuffer_.getNumSamples() - currentOutputOffset_);
    
    for (int i = 0; i < endPoint; ++i)
    {
        writePtr[i] = readPtr[i];
    }
    
    for (int i = endPoint; i < bufferToFill.numSamples; ++i)
    {
        writePtr[i] = 0;
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
    return shouldLoop_;
}

void GridAudioRendererAudioSource::setLooping(bool shouldLoop)
{
    shouldLoop_ = shouldLoop;
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