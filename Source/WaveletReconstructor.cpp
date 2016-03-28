#include "WaveletReconstructor.h"

#include "EqualLoudnessCurve.h"

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
        float previousValue = 0.0f;
        const auto& binInformation = waveTables_.getReference(waveTables_.size() - y - 1);
        const Array<float>& waveTable = binInformation.Waveform;
        const auto waveTableLength = waveTable.size();
        const auto cycleLength = binInformation.CycleLength;
        for (int x = 0; x < gridData.getWidth(); ++x)
        {
            auto bufferOffset = x * config_.WindowLength;
            auto value = gridData.getXY(x, y);
            auto writePtr = buffer.getWritePointer(0, bufferOffset);
            int waveTableOffset = (config_.WindowLength * x) % waveTableLength;

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
            }*/
            // Ramp down
            if (previousValue > minThreshold && value < minThreshold)
            {
                int rampDownLength = jmin(roundToInt(rampToZeroCycles_ * cycleLength), config_.WindowLength);
                float rampFactor = 1.0f / rampDownLength;
                for (int i = 0; i < rampDownLength; ++i)
                {
                    writePtr[i] += waveTable[waveTableOffset] * (1.0f - i * rampFactor);
                    waveTableOffset = ++waveTableOffset % waveTableLength;
                }
            }
            // Start or continue
            else if (previousValue > minThreshold || value > minThreshold)
            {
                int rampLength = jmin(roundToInt(rampTransitionCycles_ * cycleLength), config_.WindowLength);
                std::cout << rampLength << std::endl;
                float rampFactor = (value - previousValue) / rampLength;
                for (int i = 0; i < rampLength; ++i)
                {
                    writePtr[i] += waveTable[waveTableOffset] * (previousValue + i * rampFactor);
                    waveTableOffset = ++waveTableOffset % waveTableLength;
                }
                for (int i = rampLength; i < config_.WindowLength; ++i)
                {
                    writePtr[i] += waveTable[waveTableOffset] * value;
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
        BinInformation& binInformation = waveTables_.getReference(i);

        auto freq = config_.MinimumFrequency * powf(2.0, i / config_.BinsPerOctave);

        const float repeatLength = config_.SampleRate / freq;
        const int minRequiredTableLength = roundToInt(repeatLength);
        binInformation.CycleLength = minRequiredTableLength;

        const int newWaveTableLength = jmax(minRequiredTableLength, roundToInt(repeatLength * ceil(minWaveTableLength_ / repeatLength)));
        binInformation.Waveform.resize(newWaveTableLength);

        float scaleFactor = 2.0f * float_Pi * freq / config_.SampleRate;
        auto freqScaleFactor = globalScalar_ * EqualLoudnessCurve::getScalarForFrequency(freq);
        for (int j = 0; j < newWaveTableLength; ++j)
        {
            binInformation.Waveform.set(j, freqScaleFactor * sinf(static_cast<float>(j) * scaleFactor));
        }

        std::cout << freq << "\t" << minRequiredTableLength << "\t" << newWaveTableLength << "\t" << scaleFactor << "\t" << freqScaleFactor << std::endl;
    }
}