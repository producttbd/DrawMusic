#ifndef DFMS2_CONFIGURATION_H_INCLUDED
#define DFMS2_CONFIGURATION_H_INCLUDED
#include "JuceHeader.h"

#define WINDOW_4096

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
    static constexpr float getPreReconstructionScaleFactor()
    {
        return preReconstructionScaleFactor_;
    }
    static constexpr int getSamplesPerThumbnailSample() { return thumbnailSampleWindow_; }

    static constexpr int getGridHeight() { return gridHeight_; }
    static constexpr int getGridWidth() { return totalNumberWindows_; }
    static constexpr float getMinGridValue() { return minGridValue_; }
    static constexpr float getMaxGridValue() { return maxGridValue_; }

    static constexpr int getNewWindowWidth() { return newWindowWidth_; }
    static constexpr int getNewWindowHeight() { return newWindowHeight_; }

    static constexpr int getTotalAudioSampleLength()
    {
        return (totalNumberWindows_ + 1) * (windowLength_ / 2);
    }

    static constexpr int getPlaybackTimerInterval() { return playbackTimerInterval_; }

private:
#ifdef WINDOW_4096
    static constexpr int fftOrder_ = 12;
#endif

    static constexpr int buttonWidth_ = 80;
    static constexpr int buttonHeight_ = 24;
    static constexpr int guiMargin_ = 10;
    static constexpr int waveformViewHeight_ = 120;

    static constexpr int windowLength_ = 1 << fftOrder_;
    static constexpr float preReconstructionScaleFactor_ = 0.01f;

    static constexpr int gridHeight_ = 513;
    static constexpr int totalNumberWindows_ = 1000;
    static constexpr int thumbnailSampleWindow_ = 1 << (fftOrder_ - 2);
    static constexpr int paletteSide_ = 100;
    static constexpr float minGridValue_ = 0.0f;
    static constexpr float maxGridValue_ = 1.0f;

    static constexpr int newWindowWidth_ = 500;
    static constexpr int newWindowHeight_ = 600;

    static constexpr int playbackTimerInterval_ = 50;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Configuration);
};

#endif // DFMS2_CONFIGURATION_H_INCLUDED
