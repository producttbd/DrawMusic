#include "WaveletReconstructor.h"

WaveletReconstructor::WaveletReconstructor()
{
    
}

void WaveletReconstructor::configure(WaveletReconstructor::WaveletReconstructorConfiguration config)
{
    config_ = config;
    createBinInformation();
    configured = true;
}

void WaveletReconstructor::perform(const GridData& gridData, AudioSampleBuffer& buffer) const
{
    buffer.clear();
    jassert(configured);
    for (int y = 0; y < gridData.getHeight(); ++y)
    {
        int waveTableOffset = 0;
        float previousValue = 0.0f;
        const Array<float>& waveTable = waveTables_.getReference(waveTables_.size() - y - 1);
        auto waveTableLength = waveTable.size();
        for (int x = 0; x < gridData.getWidth(); ++x)
        {
            auto bufferOffset = x * config_.WindowLength;
            auto value = gridData.getXY(x, y);
            auto writePtr = buffer.getWritePointer(0, bufferOffset);

            /*
            // New impulse
            if (previousValue < minThreshold && value > minThreshold)
            {
                waveTableOffset = 0;
                for (int i = 0; i < config_.WindowLength; ++i)
                {
                    writePtr[i] += waveTable[waveTableOffset];
                    waveTableOffset = ++waveTableOffset % waveTableLength;
                }
            }
            // Ramp down
            else if (previousValue > minThreshold && value < minThreshold)
            {
                int rampDownLength = jmin(roundToInt(rampToZeroTime_ * config_.SampleRate), config_.WindowLength);
                float rampFactor = 1.0f / rampDownLength;
                for (int i = 0; i < rampDownLength; ++i)
                {
                    writePtr[i] += waveTable[waveTableOffset] * (1.0f - i * rampFactor);
                    waveTableOffset = ++waveTableOffset % waveTableLength;
                }
            }
             */
            // Continue
            if (previousValue > minThreshold || value > minThreshold)
            {
                int rampLength = jmin(roundToInt(rampTransitionTime_ * config_.SampleRate), config_.WindowLength);
                float rampFactor = (value - previousValue) / rampLength;
                for (int i = 0; i < rampLength; ++i)
                {
                    writePtr[i] += waveTable[waveTableOffset] * (previousValue + i * rampFactor);
                    waveTableOffset = ++waveTableOffset % waveTableLength;
                }
                for (int i = rampLength; i < config_.WindowLength; ++i)
                {
                    writePtr[i] += waveTable[waveTableOffset];
                    waveTableOffset = ++waveTableOffset % waveTableLength;
                }
            }
            previousValue = value;
        }
    }
}

void WaveletReconstructor::createBinInformation()
{
    waveTables_.resize(config_.NumberFrequencies);
    for (int i = 0; i < config_.NumberFrequencies; ++i)
    {
        auto freq = config_.MinimumFrequency * powf(2.0, i / config_.BinsPerOctave);
        std::cout << freq << std::endl;
        const int tableLength = roundToInt(floorf(config_.SampleRate / freq));
        waveTables_.getReference(i).resize(tableLength);
        float scaleFactor = 2.0f * float_Pi / static_cast<float>(tableLength);
        for (int j = 0; j < tableLength; ++j)
        {
            waveTables_.getReference(i).set(j, globalScalar_ * sinf(static_cast<float>(j) * scaleFactor));
        }
    }
}