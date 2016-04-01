#ifndef DFMS2_CONFIGURATION_H_INCLUDED
#define DFMS2_CONFIGURATION_H_INCLUDED
#include "JuceHeader.h"

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
    static constexpr int getSamplesPerThumbnailSample() { return thumbnailSampleWindow_; }

    static constexpr int getGridHeight() { return gridHeight_; }
    static constexpr int getGridWidth() { return totalNumberWindows_; }
    static constexpr float getMinGridValue() { return minGridValue_; }
    static constexpr float getMaxGridValue() { return maxGridValue_; }

    static constexpr int getNewWindowWidth() { return newWindowWidth_; }
    static constexpr int getNewWindowHeight() { return newWindowHeight_; }

    static constexpr int getTotalAudioSampleLength()
    {
        return totalNumberWindows_ * reconstructionWindowLength_;
    }

    static constexpr float getMinimumFrequency() { return minimumFrequency_; }
    static constexpr float getBinsPerOctave() { return binsPerOctave_; }
    static constexpr int getReconstructionWindowLength() { return reconstructionWindowLength_; }
    static constexpr int getPlaybackTimerInterval() { return playbackTimerInterval_; }

private:


    static constexpr int buttonWidth_ = 80;
    static constexpr int buttonHeight_ = 24;
    static constexpr int guiMargin_ = 10;
    static constexpr int waveformViewHeight_ = 120;

    static constexpr int reconstructionWindowLength_ = 2048;
    static constexpr float minimumFrequency_ = 80.0f;
    static constexpr float maxiumTargetFrequency = 10000.0f;
    static constexpr float binsPerOctave_ = 160.0f;
    
    static constexpr int gridHeight_ = 1200;
    static constexpr int totalNumberWindows_ = 2500;
    
    static constexpr int thumbnailSampleWindow_ = 256;
    
    static constexpr int paletteSide_ = 100;
    static constexpr float minGridValue_ = 0.0f;
    static constexpr float maxGridValue_ = 1.0f;

    static constexpr int newWindowWidth_ = 500;
    static constexpr int newWindowHeight_ = 1000;

    static constexpr int playbackTimerInterval_ = 50;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Configuration);
};

#endif // DFMS2_CONFIGURATION_H_INCLUDED
