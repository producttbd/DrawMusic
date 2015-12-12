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
    g.fillAll(Colours::green.withAlpha(0.01f)); // Wavelength container color
    g.setColour (Colours::white); // Wavelength color
    thumbnail_.drawChannel(g, getLocalBounds());
}

// GridAudioRendererAudioSource::Listener
void WaveformView::newAudioCallback(const AudioSampleBuffer& updatedAudio)
{
    thumbnail_.refresh(updatedAudio, 512);
    repaint();
}

