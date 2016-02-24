#ifndef PLAYBACKTIMELINE_H_INCLUDED
#define PLAYBACKTIMELINE_H_INCLUDED

#include "JuceHeader.h"

#include "GridAudioRendererAudioSource.h"

class PlaybackTimeline : public Component,
                         public GridAudioRendererAudioSource::NewPositionListener
{
public:
    explicit PlaybackTimeline(const String name);
    
    void newPositionCallback(float fraction) override;
    
    void paint(Graphics& g) override;
    
private:
    float currentPlayFraction_ = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaybackTimeline);
};

#endif  // PLAYBACKTIMELINE_H_INCLUDED
