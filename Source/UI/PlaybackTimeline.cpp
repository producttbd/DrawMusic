#include "PlaybackTimeline.h"

PlaybackTimeline::PlaybackTimeline(const String name)
{
}

void PlaybackTimeline::setToControlAudioSystem(Rectangle<int> activeClickArea,
                                               AudioSystem* audioSystem)
{
  activeClickArea_ = activeClickArea;
  audioSystem_ = audioSystem;
}

void PlaybackTimeline::newPositionCallback(float playFraction)
{
  jassert(playFraction >= 0.0f && playFraction <= 1.0f);
  currentPlayFraction_ = playFraction;
}

bool PlaybackTimeline::hitTest(int x, int y)
{
  return activeClickArea_.contains(x, y);
}

void PlaybackTimeline::mouseDown(const juce::MouseEvent& event)
{
  if (audioSystem_ != nullptr)
  {
    float newFractionalPosition = static_cast<float>(event.x) / getWidth();
    audioSystem_->setNewPlaybackPosition(newFractionalPosition);
    repaint();
  }
}

void PlaybackTimeline::paint(juce::Graphics& g)
{
  g.setColour(Colours::red);
  float x = currentPlayFraction_ * getWidth();
  g.drawLine(x, 0.0f, x, (float)getHeight());
}