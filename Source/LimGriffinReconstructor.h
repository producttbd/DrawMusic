#ifndef LIMGRIFFINRECONSTRUCTOR_H_INCLUDED
#define LIMGRIFFINRECONSTRUCTOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "SimpleSpectrumReconstructor.h"

class LimGriffinReconstructor : public SimpleSpectrumReconstructor
{
public:
    LimGriffinReconstructor(int fftOrder, int windowLength, const GridData& gridData, int iterations);
    void perform(AudioSampleBuffer& outputBuffer) override;

protected:
    void copyWindowOutAndZeroFirstHalf(float* destination, AudioSampleBuffer& source, int offset);
    void addBackToOriginal(AudioSampleBuffer& destination, int offset, const float* source);

    const int iterations_;
    FFT forwardFft_;
    FFT inverseFft_;
};




#endif  // LIMGRIFFINRECONSTRUCTOR_H_INCLUDED
