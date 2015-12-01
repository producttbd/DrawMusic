#ifndef SIMPLESPECTRUMRECONSTRUCTOR_H_INCLUDED
#define SIMPLESPECTRUMRECONSTRUCTOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "GridData.h"

class SimpleSpectrumReconstructor {
public:
    // Will zero-pad if gridData's height is less than window length
    SimpleSpectrumReconstructor(int fftOrder, int windowLength, const GridData& gridData);
    virtual void perform(AudioSampleBuffer& outputBuffer);
    virtual ~SimpleSpectrumReconstructor();

protected:
    void expandSpectrogramColumnToFullWindowLength(int spectrogramColumn, HeapBlock<FFT::Complex>& output);
    void expandSpectrogramColumnToFullWindowLength(int spectrogramColumn, HeapBlock<float>& output);

    const int windowLength_;
    const int windowMidpoint_;
    const int totalNumberWindows_;
    const GridData& gridData_;
    const float scaleFactor_;

    static const float hann_window_[];//TODO fix (this assumes window length)

private:
    const FFT fft_;
};



#endif  // SIMPLESPECTRUMRECONSTRUCTOR_H_INCLUDED
