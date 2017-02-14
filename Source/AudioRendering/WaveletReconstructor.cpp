#include "WaveletReconstructor.h"

#include "Configuration.h"
#include "EqualLoudnessCurve.h"

WaveletReconstructor::WaveletReconstructor(const GridData& gridData) :
gridData_(gridData),
minimumFrequency_(Configuration::getMinimumFrequency()),
binsPerOctave_(Configuration::getBinsPerOctave()),
windowLength_(Configuration::getReconstructionWindowLength()),
sampleRate_(44100.0) // TODO fix this
{
    createBinInformation();
}

void WaveletReconstructor::reinitialize()
{
    minimumFrequency_ = Configuration::getMinimumFrequency();
    binsPerOctave_ = Configuration::getBinsPerOctave();
    windowLength_ = Configuration::getReconstructionWindowLength();
    createBinInformation();
}

void WaveletReconstructor::perform(AudioSampleBuffer& buffer) const
{
    buffer.clear();
    for (int y = 0; y < gridData_.getHeight(); ++y)
    {
        float previousValue = 0.0f;
        const auto& binInformation = waveTables_.getReference(waveTables_.size() - y - 1);
        const Array<float>& waveTable = binInformation.Waveform;
        const auto waveTableLength = waveTable.size();
        const auto cycleLength = binInformation.CycleLength;
        for (int x = 0; x < gridData_.getWidth(); ++x)
        {
            auto bufferOffset = x * windowLength_;
            auto value = gridData_.getXY(x, y);
            auto writePtr = buffer.getWritePointer(0, bufferOffset);
            int waveTableOffset = (windowLength_ * x) % waveTableLength;

            if (previousValue > minThreshold || value > minThreshold)
            {
                int rampLength = jmin(roundToInt(rampTransitionCycles_ * cycleLength), windowLength_);
                float rampFactor = (value - previousValue) / rampLength;
                for (int i = 0; i < rampLength; ++i)
                {
                    writePtr[i] += waveTable[waveTableOffset] * (previousValue + i * rampFactor);
                    waveTableOffset = ++waveTableOffset % waveTableLength;
                }
                if (value > minThreshold)
                {
                    for (int i = rampLength; i < windowLength_; ++i)
                    {
                        writePtr[i] += waveTable[waveTableOffset] * value;
                        waveTableOffset = ++waveTableOffset % waveTableLength;
                    }
                }
            }
            previousValue = value;
        }
    }
}

void WaveletReconstructor::createBinInformation()
{
    const int numberFrequencies = gridData_.getHeight();
    waveTables_.resize(numberFrequencies);
    for (int i = 0; i < numberFrequencies; ++i)
    {
        BinInformation& binInformation = waveTables_.getReference(i);

        auto freq = minimumFrequency_ * powf(2.0, i / binsPerOctave_);
        jassert(freq < sampleRate_ / 2);

        const float repeatLength = sampleRate_ / freq;
        const int minRequiredTableLength = roundToInt(repeatLength);
        binInformation.CycleLength = minRequiredTableLength;

        const int newWaveTableLength =
                jmax(minRequiredTableLength, roundToInt(repeatLength * ceil(minWaveTableLength_ / repeatLength)));
        binInformation.Waveform.resize(newWaveTableLength);

        float scaleFactor = 2.0f * float_Pi * freq / sampleRate_;
        auto freqScaleFactor = globalScalar_ * EqualLoudnessCurve::getScalarForFrequency(freq);
        for (int j = 0; j < newWaveTableLength; ++j)
        {
            binInformation.Waveform.set(j, freqScaleFactor * sinf(static_cast<float>(j) * scaleFactor));
        }

        // std::cout << freq << "\t" << minRequiredTableLength << "\t" << newWaveTableLength
        //           << "\t" << scaleFactor << "\t" << freqScaleFactor << std::endl;
    }
}