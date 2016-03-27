#include "WaveletReconstructor.h"

WaveletReconstructor::WaveletReconstructor(WaveletReconstructorConfiguration config)
: config_(config)
{

}

void WaveletReconstructor::perform(const GridData& gridData, AudioSampleBuffer& buffer) const
{
    for (int column = 0; column < gridData.getWidth(); ++column)
    {
        for (int row = 0; row < gridData.getHeight(); ++row)
        {

        }
    }
}

void WaveletReconstructor::createBinInformation()
{
    waveTables_.allocate(config_.NumberFrequencies, false);
    for (int i = 0; i < config_.NumberFrequencies; ++i)
    {
        waveTables_[i].Frequency = config_.MinimumFrequency
                * powf(2.0, static_cast<float>(i) / config_.BinsPerOctave);
        const int tableLength = roundToInt(ceilf(config_.SampleRate / waveTables_[i].Frequency));
        auto& waveTable = waveTables_[i].Waveform;
        waveTable.allocate(tableLength, false);
        float scaleFactor = 2.0f * float_Pi / static_cast<float>(tableLength);
        for (int j = 0; j < tableLength; ++j)
        {
            waveTable[i] = sinf(static_cast<float>(j) * scaleFactor);
        }
    }
}