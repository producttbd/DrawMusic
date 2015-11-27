#ifndef DFMS2_Configuration_h

#include "../JuceLibraryCode/JuceHeader.h"

class Configuration
{
public:
    static constexpr int getMainWindowHeight()
    {
        return getGridHeight() + 4 * guiMargin_ + waveformViewHeight_+ paletteSide_;
    }
    static constexpr int getMainWindowWidth()
    {
        return totalNumberWindows_ + 2 * guiMargin_;
    }
    
    static constexpr int getGuiMargin() { return guiMargin_; }
    static constexpr int getPaletteSide() { return paletteSide_; }
    static constexpr int getButtonHeight() { return buttonHeight_; }
    static constexpr int getButtonWidth() { return buttonWidth_; }
    static constexpr int getWaveformViewHeight() { return waveformViewHeight_; }

    static constexpr int getNumberChannels() { return 1; }
    static constexpr int getFftOrder() { return fftOrder_; }
    static constexpr int getFftLength() { return windowLength_; }
    static constexpr int getSamplesPerThumbnailSample() { return thumbnailSampleWindow_; }

    static constexpr int getGridHeight() { return windowLength_ / 2 + 1; }
    static constexpr int getGridWidth() { return totalNumberWindows_; }
    static constexpr float getMinGridValue() { return minGridValue_; }
    static constexpr float getMaxGridValue() { return maxGridValue_; }
    
    static constexpr int getTotalAudioSampleLength()
    {
        return (totalNumberWindows_ + 1) * (windowLength_ / 2);
    }

private:
    static constexpr int buttonWidth_ = 80;
    static constexpr int buttonHeight_ = 24;
    static constexpr int guiMargin_ = 10;
    static constexpr int waveformViewHeight_ = 120;
    static constexpr int fftOrder_ = 10;
    static constexpr int windowLength_ = 1 << fftOrder_;
    static constexpr int totalNumberWindows_ = 1000;
    static constexpr int thumbnailSampleWindow_ = 1 << (fftOrder_ - 2);
    static constexpr int paletteSide_ = 100;
    static constexpr float minGridValue_ = 0.0f;
    static constexpr float maxGridValue_ = 1.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Configuration);
};

#define DFMS2_Configuration_h


#endif
