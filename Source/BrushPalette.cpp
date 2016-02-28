#include "BrushPalette.h"

#include "BrushFactory.h"
#include "DFMSLookAndFeel.h"

BrushPalette::BrushPalette(const String& componentName, const GridColourScheme& colourScheme) noexcept
: Component(componentName),
  colourScheme_(colourScheme),
  currentBrush_(0),
  brushCollection_()
{
    brushCollection_.addChangeListener(this);
}

AbstractBrushAction* BrushPalette::getCurrentBrushAction() const
{
    return brushCollection_.getCurrentBrush()->getBrushAction();
}

void BrushPalette::mouseDown(const MouseEvent& event)
{
    openBrushPaletteWindow();
}

void BrushPalette::paint(Graphics& g)
{
    const AbstractCompleteBrush* brush = brushCollection_.getCurrentBrush();
    AbstractBrushAction* brushAction = brush->getBrushAction();
    brushAction->drawPreviewInto(g, getLocalBounds());
    DFMSLookAndFeel::drawOutline(g, *this);

    const Colour zeroColour = GridColourScheme::convertToColour(0.0f);
    g.setColour(zeroColour.contrasting());
    g.drawText(brush->getName(), 0, 0, getWidth(), 20, Justification::left);
}

void BrushPalette::resized()
{
}

void BrushPalette::changeListenerCallback(juce::ChangeBroadcaster* /*source*/)
{
    repaint();
}

void BrushPalette::openBrushPaletteWindow()
{
    if (brushPaletteWindow_ != nullptr)
    {
        return;
    }
    brushPaletteWindow_ = new BrushPaletteWindow("brushPalettewindow", brushCollection_);
}
