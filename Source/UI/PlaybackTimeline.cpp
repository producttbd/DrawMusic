#include "PlaybackTimeline.h"

PlaybackTimeline::PlaybackTimeline(const String name)
{
}

void PlaybackTimeline::setToControlAudioSource(Rectangle<int> activeClickArea,
                                               PositionableAudioSource* audioSource)
{
  activeClickArea_ = activeClickArea;
  audioSource_ = audioSource;
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
  if (audioSource_ != nullptr)
  {
    float newFractionalPosition = static_cast<float>(event.x) / getWidth();
    currentPlayFraction_ = newFractionalPosition;
    audioSource_->setNextReadPosition(
        static_cast<int64>(audioSource_->getTotalLength() * newFractionalPosition));
    repaint();
  }
}

void PlaybackTimeline::paint(juce::Graphics& g)
{
  g.setColour(Colours::red);
  auto x = currentPlayFraction_ * getWidth();
  g.drawLine(x, 0, x, getHeight());
}