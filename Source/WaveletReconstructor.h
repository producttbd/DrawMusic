#ifndef WAVELETRECONSTRUCTOR_H_INCLUDED
#define WAVELETRECONSTRUCTOR_H_INCLUDED

#include "JuceHeader.h"

#include "GridData.h"

class WaveletReconstructor
{
public:
    struct WaveletReconstructorConfiguration
    {
        int NumberFrequencies;
        float MinimumFrequency;
        float BinsPerOctave;
        int WindowLength;
        double SampleRate;
    };

    WaveletReconstructor();
    
    void configure(WaveletReconstructorConfiguration config);

    void perform(const GridData& gridData, AudioSampleBuffer& buffer) const;
    

private:
    void createBinInformation();

    WaveletReconstructorConfiguration config_;

    struct BinInformation
    {
        Array<float> Waveform;
        int CycleLength;
    };
    Array<BinInformation> waveTables_;
    
    bool configured = false;
    const float minThreshold = 0.00001f;
    const float impulseThreshold = 0.1f;
    const float globalScalar_ = 0.1f;
    const float rampToZeroCycles_ = 5.0f; // cycles
    const float rampTransitionCycles_ = 5.0f; // cycles
    const int minWaveTableLength_ = 512;
};

#endif // WAVELETRECONSTRUCTOR_H_INCLUDED