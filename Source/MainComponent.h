#ifndef __JUCE_HEADER_9002020A4DD09B20__
#define __JUCE_HEADER_9002020A4DD09B20__

#include "JuceHeader.h"

#include "AudioRendering/GridAudioRendererAudioSource.h"
#include "AudioRendering/WaveletReconstructor.h"
#include "Brushes/BrushPalette.h"
#include "GridData/GridActionManager.h"
#include "GridData/GridData.h"
#include "UI/DrawGrid.h"
#include "UI/GridColourScheme.h"
#include "UI/PlaybackTimeline.h"
#include "UI/WaveformView.h"

class MainComponent : public Component, public ApplicationCommandTarget
{
 public:
  MainComponent();
  ~MainComponent();

  // Component overrides
  void paint(Graphics& g) override;
  void resized() override;

  // ApplicationCommandTarget overrides
  ApplicationCommandTarget* getNextCommandTarget() override;
  void getAllCommands(Array<CommandID>& commands) override;
  void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;
  bool perform(const InvocationInfo& info) override;

 private:
  void togglePlayback();
  void stopPlayback();
  void startPlayback();
  void resizeGrid();
  void clearGrid();
  void gridSmaller();
  void gridLarger();
  void openAudioSettingsWindow();

  class PlaybackTimer : public Timer
  {
   public:
    PlaybackTimer(PlaybackTimeline& playbackTimeline) : playbackTimeline_(playbackTimeline) {}
    void timerCallback() override { playbackTimeline_.repaint(); }

   private:
    PlaybackTimeline& playbackTimeline_;
  };

  GridData gridData_;
  BrushPalette brushPalette_;
  GridDataChangedNotifier gridDataChangedNotifier_;
  GridActionManager gridActionManager_;
  GridColourScheme gridColourScheme_;
  DrawGrid drawGrid_;

  AudioDeviceManager deviceManager_;
  AudioSourcePlayer audioSourcePlayer_;
  AudioTransportSource transportSource_;
  GridAudioRendererAudioSource gridAudioSource_;
  PlaybackTimeline playbackTimeline_;
  PlaybackTimer playbackTimer_;
  WaveformView waveformView_;

  Component::SafePointer<Component> audioSettingsWindow_;

  TextButton playStopButton_;
  TextButton undoButton_;
  TextButton redoButton_;
  Array<Button*> allButtons_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

#endif  // __JUCE_HEADER_9002020A4DD09B20__
