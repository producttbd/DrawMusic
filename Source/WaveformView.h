/*
  ==============================================================================

    WaveformView.h
    Created: 29 Oct 2015 8:39:13pm
    Author:  Trevor Knight

  ==============================================================================
*/

#ifndef WAVEFORMVIEW_H_INCLUDED
#define WAVEFORMVIEW_H_INCLUDED

#include "JuceHeader.h"

#include "AudioBufferThumbnail.h"
#include "GridAudioRendererAudioSource.h"

class WaveformView : public Component,
                     public ScrollBar::Listener,
                     public Slider::Listener,
                     public GridAudioRendererAudioSource::Listener
{
public:
    explicit WaveformView(const String& name);

    // Component overrides
    void resized() override;
    void paint(Graphics& g) override;

    // GridAudioRendererAudioSource::Listener override
    void newAudioCallback(const AudioSampleBuffer& updatedAudio) override;

    // Scrollbar::Listener overrides
    void scrollBarMoved(ScrollBar *scrollBarThatHasMoved, double newRangeStart) override;

    // Slider::Listener overrides
    void sliderValueChanged(Slider* slider) override;
    void sliderDragStarted(Slider* slider) override;
    void sliderDragEnded(Slider* slider) override;

private:
    AudioBufferThumbnail thumbnail_;
    ScrollBar scrollbar_;
    Slider zoomSlider_;
};


#endif  // WAVEFORMVIEW_H_INCLUDED
