/*
  ==============================================================================

    LimGriffinReconstructor.cpp
    Created: 27 Oct 2015 6:06:01pm
    Author:  Trevor Knight

  ==============================================================================
*/

#include "LimGriffinReconstructor.h"

#include "Configuration.h"

LimGriffinReconstructor::LimGriffinReconstructor(int fftOrder, int windowLength, const GridData& gridData, int iterations)
: SimpleSpectrumReconstructor(fftOrder, windowLength, gridData),
iterations_(iterations),
forwardFft_(fftOrder, false),
inverseFft_(fftOrder, true)

{
    //jassert(iterations > 0);
}

void LimGriffinReconstructor::copyWindowOutAndZeroFirstHalf(float* destination, AudioSampleBuffer& source, int offset)
{
    jassert(offset >= 0);

    const float* readPointer = source.getReadPointer(0, offset); //TODO Channel
    float* writePointer = source.getWritePointer(0, offset); //TODO Channel
    for (int i = 0; i < windowLength_; ++i)
    {
        destination[i] = readPointer[i] * hann_window_[i];
    }
    for (int i = 0; i < windowLength_; ++i)
    {
        writePointer[i] = 0.0f; // TODO Use memset?
    }
}

void LimGriffinReconstructor::addBackToOriginal(AudioSampleBuffer& destination, int offset, const float* source)
{
    float* writePointer = destination.getWritePointer(0, offset); // TODO Channel
    for (int i = 0; i < windowLength_; ++i)
    {
        writePointer[i] += source[i];
    }
}

void LimGriffinReconstructor::perform(AudioSampleBuffer& outputBuffer)
{
    SimpleSpectrumReconstructor::perform(outputBuffer);

    HeapBlock<FFT::Complex> bufferA(2 * windowLength_);
    HeapBlock<FFT::Complex> bufferB(2 * windowLength_);
    HeapBlock<float> magnitudeData(windowLength_);

    for (int iter = 0; iter < iterations_; ++iter)
    {
        // In general, we're doing this in-place with overlapping windows
        // So we'll always have two windows copied to buffers so we don't over-write what
        // we're next working on.
        bufferA.clear(2 * windowLength_);
        bufferB.clear(2 * windowLength_);
        FFT::Complex* currentWindowAsComplex = bufferA.getData();
        float* currentWindowAsFloat = (float*)(currentWindowAsComplex);
        float* nextWindowBuffer = (float*)(bufferB.getData());

        // Copy the first window to current buffer before we start
        copyWindowOutAndZeroFirstHalf(currentWindowAsFloat, outputBuffer, 0);

        for (int windowNumber = 0; windowNumber < totalNumberWindows_ - 1; ++windowNumber)
        {
            expandSpectrogramColumnToFullWindowLength(windowNumber, magnitudeData);
            // Forward transformation
            forwardFft_.performRealOnlyForwardTransform(currentWindowAsFloat);
            // scale by original magnitude data
            for (int i = 0; i < windowLength_; ++i)
            {
                float currentMagnitude = sqrt(currentWindowAsComplex[i].r * currentWindowAsComplex[i].r
                                              + currentWindowAsComplex[i].i * currentWindowAsComplex[i].i);
                currentWindowAsComplex[i].r = currentWindowAsComplex[i].r / currentMagnitude * magnitudeData[i];
                currentWindowAsComplex[i].i = currentWindowAsComplex[i].i / currentMagnitude * magnitudeData[i];
            }
            inverseFft_.performRealOnlyInverseTransform(currentWindowAsFloat);

            // Copy next window out
            const int nextWindowOffset = (windowNumber + 1) * windowMidpoint_;
            copyWindowOutAndZeroFirstHalf(nextWindowBuffer, outputBuffer, nextWindowOffset);
            
            // Copy current window in
            const int currentWindowOffset = windowNumber * windowMidpoint_;
            addBackToOriginal(outputBuffer, currentWindowOffset, currentWindowAsFloat);

            //std::swap(currentWindowAsFloat, nextWindowBuffer);
            float* temp = nextWindowBuffer;
            nextWindowBuffer = currentWindowAsFloat;
            currentWindowAsFloat = temp;
        }

        // Last window
        // SOMETHING???
    }
}