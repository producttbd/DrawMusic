#ifndef WAVEFORMVIEW_H_INCLUDED
#define WAVEFORMVIEW_H_INCLUDED

#include "JuceHeader.h"

#include "AudioBufferThumbnail.h"
#include "GridAudioRendererAudioSource.h"

class WaveformView : public Component, public GridAudioRendererAudioSource::NewAudioListener
{
 public:
  explicit WaveformView(const String& name);

  // Component overrides
  void resized() override;
  void paint(Graphics& g) override;

  // GridAudioRendererAudioSource::Listener override
  void newAudioCallback(const AudioSampleBuffer& updatedAudio) override;

 private:
  AudioBufferThumbnail thumbnail_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformView);
};

#endif  // WAVEFORMVIEW_H_INCLUDED
