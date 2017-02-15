#ifndef DFMS2_CONFIGURATION_H_INCLUDED
#define DFMS2_CONFIGURATION_H_INCLUDED

#include "JuceHeader.h"

#include <tgmath.h>

class Configuration
{
 public:
  static int getMainWindowHeight()
  {
    return getGridHeight() + 4 * guiMargin_ + waveformViewHeight_ + paletteSide_;
  }
  static int getMainWindowWidth() { return getGridWidth() + 2 * guiMargin_; }

  static constexpr int getGuiMargin() { return guiMargin_; }
  static constexpr int getPaletteSide() { return paletteSide_; }
  static constexpr int getButtonHeight() { return buttonHeight_; }
  static constexpr int getButtonWidth() { return buttonWidth_; }
  static constexpr int getWaveformViewHeight() { return waveformViewHeight_; }

  static constexpr int getNumberChannels() { return 1; }
  static constexpr int getSamplesPerThumbnailSample() { return thumbnailSampleWindow_; }

  static int getGridHeight()
  {
    constexpr static const int gridHeights_[numGridSizes_] = {400, 800, 1000, 1200, 1400};
    return gridHeights_[currentGridSize_];
  }
  static int getGridWidth()
  {
    constexpr static const int gridWidths_[numGridSizes_] = {800, 1600, 2000, 2400, 2800};
    return gridWidths_[currentGridSize_];
  }
  static bool canIncreaseGridSize() { return currentGridSize_ < numGridSizes_ - 1; }
  static bool increaseGridSize()
  {
    auto oldSize = currentGridSize_;
    return oldSize != (currentGridSize_ = jmin(numGridSizes_ - 1, currentGridSize_ + 1));
  }
  static bool canDecreaseGridSize() { return currentGridSize_ > 0; }
  static bool decreaseGridSize()
  {
    auto oldSize = currentGridSize_;
    return oldSize != (currentGridSize_ = jmax(0, currentGridSize_ - 1));
  }

  static constexpr float getMinimumFrequency() { return minimumFrequency_; }

  // Highest freq will be lowestFreq * 2^(gridHeight / binsPerOctave) = highestFreq
  // highestFreq / lowestFreq = 2^(gridHeight / binsPerOctave)
  // log2(highestFreq / lowestFreq) = gridHeight / binsPerOctave
  // binsPerOctave = gridHeight / log2(highestFreq / lowestFreq)
  static float getBinsPerOctave()
  {
    return getGridHeight() / log2(maxiumTargetFrequency_ / minimumFrequency_);
  }

  static constexpr int getReconstructionWindowLength() { return reconstructionWindowLength_; }
  static constexpr int getPlaybackTimerInterval() { return playbackTimerInterval_; }

  static constexpr float getMinGridValue() { return minGridValue_; }
  static constexpr float getMaxGridValue() { return maxGridValue_; }
  static constexpr float getDefaultPressure() { return defaultPressure_; }

  static constexpr int getNewWindowWidth() { return newWindowWidth_; }
  static constexpr int getNewWindowHeight() { return newWindowHeight_; }

  static int getTotalAudioSampleLength() { return getGridWidth() * reconstructionWindowLength_; }

 private:
  static int currentGridSize_;
  static constexpr int numGridSizes_ = 5;

  static constexpr int buttonWidth_ = 80;
  static constexpr int buttonHeight_ = 24;
  static constexpr int guiMargin_ = 10;
  static constexpr int waveformViewHeight_ = 120;

  static constexpr int reconstructionWindowLength_ = 2048;

  static constexpr float minimumFrequency_ = 80.0f;
  static constexpr float maxiumTargetFrequency_ = 10000.0f;

  static constexpr int thumbnailSampleWindow_ = 256;

  static constexpr int paletteSide_ = 100;
  static constexpr float minGridValue_ = 0.0f;
  static constexpr float maxGridValue_ = 1.0f;
  static constexpr float defaultPressure_ = 1.0f;

  static constexpr int newWindowWidth_ = 500;
  static constexpr int newWindowHeight_ = 1000;

  static constexpr int playbackTimerInterval_ = 100;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Configuration);
};

#endif  // DFMS2_CONFIGURATION_H_INCLUDED
