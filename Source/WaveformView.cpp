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
  unused_audioFormatManager_(),
  thumbnailCache_(/*maxNumThumbsToStore*/ 1),
  audioThumbnail_(Configuration::getSamplesPerThumbnailSample(), unused_audioFormatManager_, thumbnailCache_),
  scrollbar_(/*isVertical*/ false),
  zoomSlider_()
{

}

void WaveformView::resized()
{

}

void WaveformView::paint(Graphics& g)
{
    g.fillAll(Colours::darkgrey);
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
