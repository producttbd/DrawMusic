#ifndef PLAYBACKTIMELINE_H_INCLUDED
#define PLAYBACKTIMELINE_H_INCLUDED

#include "JuceHeader.h"

#include "GridAudioRendererAudioSource.h"

class PlaybackTimeline : public Component,
public GridAudioRendererAudioSource::NewPositionListener
{
public:
    explicit PlaybackTimeline(const String name);
    void setToControlAudioSource(Rectangle<int> activeClickArea, PositionableAudioSource* audioSource);

    void newPositionCallback(float fraction) override;

    bool hitTest(int x, int y) override;
    void mouseDown(const MouseEvent& event) override;
    void paint(Graphics& g) override;

private:
    float currentPlayFraction_ = 0.0f;
    Rectangle<int> activeClickArea_;
    PositionableAudioSource* audioSource_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaybackTimeline);
};

#endif  // PLAYBACKTIMELINE_H_INCLUDED