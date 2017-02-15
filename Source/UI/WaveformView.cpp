#include "WaveformView.h"

#include "Configuration.h"
#include "DFMSLookAndFeel.h"

WaveformView::WaveformView(const String& name) : Component(name) {}

// Component overrides
void WaveformView::resized() { thumbnail_.zeroOut(); }

void WaveformView::paint(Graphics& g)
{
  DFMSLookAndFeel::drawOutline(g, *this);
  g.setColour(Colours::darkgrey);
  thumbnail_.drawChannel(g, getLocalBounds());
}

// GridAudioRendererAudioSource::Listener
void WaveformView::newAudioCallback(const AudioSampleBuffer& updatedAudio)
{
  thumbnail_.refresh(updatedAudio, 512);
  repaint();
}
