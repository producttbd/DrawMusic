#ifndef __JUCE_HEADER_9002020A4DD09B20__
#define __JUCE_HEADER_9002020A4DD09B20__


#include "JuceHeader.h"

#include "BrushPalette.h"
#include "DrawGrid.h"
#include "GridAudioRendererAudioSource.h"
#include "GridColourScheme.h"
#include "GridData.h"
#include "PlaybackTimeline.h"
#include "WaveformView.h"
#include "WaveletReconstructor.h"

class MainComponent : public Component,
                      public Button::Listener
{
public:
    MainComponent ();
    ~MainComponent();

    void paint(Graphics& g);
    void resized();
    void buttonClicked(Button* buttonThatWasClicked);

private:
    void togglePlayback();
    void stopPlayback();
    void startPlayback();
    
    void openAudioSettingsWindow();

    class PlaybackTimer : public Timer
    {
    public:
        PlaybackTimer(PlaybackTimeline& playbackTimeline)
        : playbackTimeline_(playbackTimeline) {}
        void timerCallback() override
        {
            playbackTimeline_.repaint();
        }
        
    private:
        PlaybackTimeline& playbackTimeline_;
    };
    
    GridData gridData_;
    GridColourScheme colourScheme_;
    BrushPalette brushPalette_;
    DrawGrid drawGrid_;
    WaveletReconstructor reconstructor_;

    AudioDeviceManager deviceManager_;
    AudioSourcePlayer audioSourcePlayer_;
    AudioTransportSource transportSource_;
    GridAudioRendererAudioSource gridAudioSource_;
    PlaybackTimeline playbackTimeline_;
    PlaybackTimer playbackTimer_;
    TimeSliceThread thread_;
    WaveformView waveformView_;
    
    Component::SafePointer<Component> audioSettingsWindow_;

    TextButton gridBiggerButton_;
    TextButton gridSmallerButton_;

    TextButton playStopButton_;
    TextButton clearButton_;
    TextButton exportButton_;
    TextButton settingsButton_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif   // __JUCE_HEADER_9002020A4DD09B20__
