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
: Component(name)
{
}

// Component overrides
void WaveformView::resized()
{
}

void WaveformView::paint(Graphics& g)
{
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds());
    g.fillAll(Colours::white);
    g.setColour (Colours::darkgrey);
    thumbnail_.drawChannel(g, getLocalBounds());
}

// GridAudioRendererAudioSource::Listener
void WaveformView::newAudioCallback(const AudioSampleBuffer& updatedAudio)
{
    thumbnail_.refresh(updatedAudio, 512);
    repaint();
}

