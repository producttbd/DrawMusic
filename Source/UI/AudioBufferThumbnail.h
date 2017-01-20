#ifndef AUDIOBUFFERTHUMBNAIL_H_INCLUDED
#define AUDIOBUFFERTHUMBNAIL_H_INCLUDED

#include "JuceHeader.h"

class AudioBufferThumbnail
{
public:
    AudioBufferThumbnail() {}

    void refresh(const AudioSampleBuffer& source, int samplesPerSample);

    void drawChannel(Graphics& g, const Rectangle<int> &area);

private:

    struct MinMaxValue
    {
        MinMaxValue() noexcept
        {
            values[0] = 0.0f;
            values[1] = 0.0f;
        }

        MinMaxValue(float minimum, float maximum) noexcept
        {
            jassert(maximum >= minimum);
            values[0] = minimum;
            values[1] = maximum;
        }

        void setFloat(float minimum, float maximum)
        {
            jassert(maximum >= minimum);
            values[0] = minimum;
            values[1] = maximum;
        }

        inline float getSpread()
        {
            return values[1] - values[0];
        }

        inline float getMinValue() const noexcept { return values[0]; }
        inline float getMaxValue() const noexcept { return values[1]; }

        inline bool isNonZero() const noexcept
        {
            jassert(values[1] >= values[0]);
            return values[1] > values[0];
        }

        inline int getPeak() const noexcept
        {
            return jmax (std::abs (values[0]),
                         std::abs (values[1]));
        }
        
    private:
        float values[2];
    };

    Array<MinMaxValue> data;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioBufferThumbnail);
};



#endif  // AUDIOBUFFERTHUMBNAIL_H_INCLUDED
