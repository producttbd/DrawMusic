#include "PlaybackTimeline.h"


PlaybackTimeline::PlaybackTimeline(const String name)
: Component(name)
{
    
}

void PlaybackTimeline::newPositionCallback(float playFraction)
{
    jassert(playFraction >= 0.0f && playFraction <= 1.0f);
    currentPlayFraction_ = playFraction;
}

void PlaybackTimeline::paint(juce::Graphics& g)
{
    g.setColour(Colours::red);
    auto x = currentPlayFraction_ * getWidth();
    g.drawLine(x, 0, x, getHeight());
}

