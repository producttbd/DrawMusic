/*
  ==============================================================================

    SimpleSpectrumReconstructor.cpp
    Created: 27 Oct 2015 6:05:49pm
    Author:  Trevor Knight

  ==============================================================================
*/

#include "SimpleSpectrumReconstructor.h"

SimpleSpectrumReconstructor::SimpleSpectrumReconstructor(int fftOrder, int windowLength, const GridData& gridData)
: windowLength_(windowLength),
windowMidpoint_(windowLength / 2),
totalNumberWindows_(gridData.getWidth()),
gridData_(gridData),
fft_(fftOrder, true)
{
    jassert(windowLength_ == windowMidpoint_ * 2);
    jassert(windowLength_ == 1 << fftOrder);
    jassert(gridData_.getHeight() == windowMidpoint_ + 1);
}

SimpleSpectrumReconstructor::~SimpleSpectrumReconstructor()
{
}

void SimpleSpectrumReconstructor::perform(AudioSampleBuffer& outputBuffer)
{
    // Zero the piece
    outputBuffer.clear();

    HeapBlock<FFT::Complex> fftInput(windowLength_);
    HeapBlock<FFT::Complex> fftOutput(windowLength_);
    for (int windowNumber = 0; windowNumber < totalNumberWindows_; ++windowNumber)
    {
        expandSpectrogramColumnToFullWindowLength(windowNumber, fftInput);
        fft_.perform(fftInput, fftOutput);
        float* toWrite = outputBuffer.getWritePointer(0, windowNumber * windowMidpoint_); // TODO channel
        for (int i = 0; i < windowLength_; ++i)
        {
            toWrite[i] = fftOutput[i].r;
        }
    }
}

void SimpleSpectrumReconstructor::expandSpectrogramColumnToFullWindowLength(int spectrogramColumn, HeapBlock<FFT::Complex>& output)
{
    output.clear(windowLength_);

    // Fill in input buffer
    output[0].r = gridData_.getXY(spectrogramColumn, windowMidpoint_);
    output[windowMidpoint_].r = output[0].r;
    for (int i = 1; i < windowMidpoint_; ++i)
    {
        output[i].r = gridData_.getXY(spectrogramColumn, windowMidpoint_ - i);
        output[windowLength_ - i].r = output[i].r;
    }
}

// TODO reduce code duplication with above method
void SimpleSpectrumReconstructor::expandSpectrogramColumnToFullWindowLength(int spectrogramColumn, HeapBlock<float>& output)
{
    output.clear(windowLength_);

    // Fill in input buffer
    output[0] = gridData_.getXY(spectrogramColumn, windowMidpoint_);
    output[windowMidpoint_] = output[0];
    for (int i = 1; i < windowMidpoint_; ++i)
    {
        output[i] = gridData_.getXY(spectrogramColumn, windowMidpoint_ - i);
        output[windowLength_ - i] = output[i];
    }
}