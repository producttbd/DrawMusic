/*
  ==============================================================================

    WaveformView.cpp
    Created: 29 Oct 2015 8:39:13pm
    Author:  Trevor Knight

  ==============================================================================
*/

#include "WaveformView.h"

#include "Configuration.h"

WaveformView::WaveformView(const String& name)
: Component(name),
  scrollbar_(/*isVertical*/ false),
  zoomSlider_()
{
    addAndMakeVisible(&scrollbar_);
    addAndMakeVisible(&zoomSlider_);
}

// Component overrides
void WaveformView::resized()
{

}

void WaveformView::paint(Graphics& g)
{
    g.fillAll(Colours::darkgrey);
    g.setColour (Colours::lightblue);
    thumbnail_.drawChannel(g, getLocalBounds());
}

// GridAudioRendererAudioSource::Listener
void WaveformView::newAudioCallback(const AudioSampleBuffer& updatedAudio)
{
    thumbnail_.refresh(updatedAudio, 512);
    repaint();
}

// Scrollbar::Listener overrides
void WaveformView::scrollBarMoved(ScrollBar *scrollBarThatHasMoved, double newRangeStart)
{

}

// Slider::Listener
void WaveformView::sliderValueChanged(Slider* slider)
{

}

void WaveformView::sliderDragStarted(Slider* slider)
{

}

void WaveformView::sliderDragEnded(Slider* slider)
{

}
