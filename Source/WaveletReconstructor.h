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
    Array<Array<float>> waveTables_;
    
    bool configured = false;
    const float minThreshold = 0.00001f;
    const float impulseThreshold = 0.1f;
    const float globalScalar_ = 0.1f;
    const float rampToZeroTime_ = 0.005; // seconds
    const float rampTransitionTime_ = 0.010; // seconds
};

#endif // WAVELETRECONSTRUCTOR_H_INCLUDED