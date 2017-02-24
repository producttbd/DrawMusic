#include "BrushPreviewButton.h"

#include "../UI/DrawMusicLookAndFeel.h"

BrushPreviewButton::BrushPreviewButton(const AbstractCompleteBrush* brush)
    : Button(brush->getName()), brush_(brush)
{
  setClickingTogglesState(true);
}

void BrushPreviewButton::paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
  brush_->getBrushAction()->drawPreviewInto(g, getLocalBounds());
  DrawMusicLookAndFeel::drawOutline(g, *this, isMouseOverButton, getToggleState());
}