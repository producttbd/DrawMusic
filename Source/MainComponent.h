#ifndef __JUCE_HEADER_9002020A4DD09B20__
#define __JUCE_HEADER_9002020A4DD09B20__


#include "JuceHeader.h"

#include "BrushPalette.h"
#include "DrawGrid.h"
#include "GridAudioRendererAudioSource.h"
#include "GridColourScheme.h"
#include "GridData.h"
#include "WaveformView.h"

class MainComponent  : public Component,
                       public ButtonListener
{
public:
    MainComponent ();
    ~MainComponent();

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

private:
    void togglePlayback();
    void stopPlayback();
    void startPlayback();

    GridData gridData_;
    GridColourScheme colourScheme_;
    BrushPalette brushPalette_;
    DrawGrid drawGrid_;

    AudioDeviceManager deviceManager_;
    AudioSourcePlayer audioSourcePlayer_;
    AudioTransportSource transportSource_;
    GridAudioRendererAudioSource gridAudioSource_;
    TimeSliceThread thread_;
    WaveformView waveformView_;

    TextButton playStopButton_;
    TextButton clearButton_;

    Slider reconstructionSlider_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif   // __JUCE_HEADER_9002020A4DD09B20__
