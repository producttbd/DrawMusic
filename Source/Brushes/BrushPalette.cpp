#include "BrushPalette.h"

#include "BrushFactory.h"
#include "DFMSLookAndFeel.h"

BrushPalette::BrushPalette(const String& componentName,
                           const GridColourScheme& colourScheme) noexcept
    : Component(componentName), colourScheme_(colourScheme), brushCollection_()
{
  brushCollection_.addChangeListener(this);
}

BrushPalette::~BrushPalette()
{
  if (brushPaletteWindow_ != nullptr)
  {
    brushPaletteWindow_.deleteAndZero();
  }
}

AbstractBrushAction* BrushPalette::getCurrentBrushAction() const
{
  return brushCollection_.getCurrentBrush()->getBrushAction();
}

void BrushPalette::mouseDown(const MouseEvent& event) { openBrushPaletteWindow(); }

void BrushPalette::paint(Graphics& g)
{
  const AbstractCompleteBrush* brush = brushCollection_.getCurrentBrush();
  AbstractBrushAction* brushAction = brush->getBrushAction();
  brushAction->drawPreviewInto(g, getLocalBounds());
  DFMSLookAndFeel::drawOutline(g, *this);
}

void BrushPalette::resized() {}

void BrushPalette::changeListenerCallback(juce::ChangeBroadcaster* /*source*/) { repaint(); }

void BrushPalette::openBrushPaletteWindow()
{
  if (brushPaletteWindow_ == nullptr)
  {
    brushPaletteWindow_ = new BrushPaletteWindow("brushPalettewindow", brushCollection_);
  }
  brushPaletteWindow_->toFront(true);
}
