#ifndef WAVELETRECONSTRUCTOR_H_INCLUDED
#define WAVELETRECONSTRUCTOR_H_INCLUDED

#include "JuceHeader.h"

#include "GridData.h"

class WaveletReconstructor
{
public:
    struct WaveletReconstructorConfiguration
    {
        const int NumberFrequencies;
        const int MinimumFrequency;
        const int BinsPerOctave;
        const int WindowLength;
        const double SampleRate;
    };

    explicit WaveletReconstructor(WaveletReconstructorConfiguration config);

    void perform(const GridData& gridData, AudioSampleBuffer& buffer) const;
    

private:
    struct BinWavetable
    {
        float Frequency;
        HeapBlock<float> Waveform;

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FrequencyBinInformation);
    };

    void createBinInformation();

    WaveletReconstructorConfiguration config_;
    HeapBlock<BinWavetable> waveTables_;
};

#endif // WAVELETRECONSTRUCTOR_H_INCLUDED