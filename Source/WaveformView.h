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

class WaveformView : public Component,
                     public ScrollBar::Listener,
                     public Slider::Listener
{
public:
    explicit WaveformView(const String& name);

    // Component overrides
    void resized() override;
    void paint(Graphics& g) override;

    // Scrollbar::Listener overrides
    void scrollBarMoved(
            ScrollBar *scrollBarThatHasMoved, double newRangeStart) override;

    // Slider::Listener
    void sliderValueChanged(Slider* slider) override;
    void sliderDragStarted(Slider* slider) override;
    void sliderDragEnded(Slider* slider) override;

private:
    AudioFormatManager unused_audioFormatManager_;
    AudioThumbnailCache thumbnailCache_;
    AudioThumbnail audioThumbnail_;
    ScrollBar scrollbar_;
    Slider zoomSlider_;
};


#endif  // WAVEFORMVIEW_H_INCLUDED
