/*
  ==============================================================================

    LimGriffinReconstructor.h
    Created: 27 Oct 2015 6:06:01pm
    Author:  Trevor Knight

  ==============================================================================
*/

#ifndef LIMGRIFFINRECONSTRUCTOR_H_INCLUDED
#define LIMGRIFFINRECONSTRUCTOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "SimpleSpectrumReconstructor.h"

class LimGriffenReconstructor : public SimpleSpectrumReconstructor
{
public:
    LimGriffenReconstructor(int fftOrder, int windowLength, const GridData& gridData, int iterations);
    void perform(AudioSampleBuffer& outputBuffer) override;

protected:
    void copyWindowOutAndZeroFirstHalf(float* destination, AudioSampleBuffer& source, int offset);
    void addBackToOriginal(AudioSampleBuffer& destination, int offset, const float* source);

    const int iterations_;
    FFT forwardFft_;
    FFT inverseFft_;

    static const float hann_window_[];//TODO fix (this assumes window length)
};




#endif  // LIMGRIFFINRECONSTRUCTOR_H_INCLUDED
