#ifndef PLAYBACKTIMELINE_H_INCLUDED
#define PLAYBACKTIMELINE_H_INCLUDED

#include "JuceHeader.h"

#include "../AudioRendering/AudioDataChangedNotifier.h"
#include "../AudioRendering/AudioSystem.h"

class PlaybackTimeline : public Component, public AudioDataChangedNotifier::NewPositionListener
{
 public:
  explicit PlaybackTimeline(const String name);
  void setToControlAudioSystem(Rectangle<int> activeClickArea, AudioSystem* audioSystem);

  void newPositionCallback(float fraction) override;

  bool hitTest(int x, int y) override;
  void mouseDown(const MouseEvent& event) override;
  void paint(Graphics& g) override;

 private:
  float currentPlayFraction_ = 0.0f;
  Rectangle<int> activeClickArea_;
  AudioSystem* audioSystem_ = nullptr;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaybackTimeline);
};

#endif  // PLAYBACKTIMELINE_H_INCLUDED