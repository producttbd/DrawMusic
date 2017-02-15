#include "BrushPreviewButton.h"

#include "DFMSLookAndFeel.h"

BrushPreviewButton::BrushPreviewButton(const AbstractCompleteBrush* brush)
    : Button(brush->getName()), brush_(brush)
{
  setClickingTogglesState(true);
}

void BrushPreviewButton::paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
  brush_->getBrushAction()->drawPreviewInto(g, getLocalBounds());
  DFMSLookAndFeel::drawOutline(g, *this, isMouseOverButton, getToggleState());
}