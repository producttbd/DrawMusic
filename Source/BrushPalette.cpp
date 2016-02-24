#include "BrushPalette.h"



#include "BrushFactory.h"
#include "DFMSLookAndFeel.h"

BrushPalette::BrushPalette(const String& componentName, const GridColourScheme& colourScheme) noexcept
: Component(componentName),
  colourScheme_(colourScheme),
  currentBrush_(0),
  brushes_()
{
    BrushFactory::getAllBrushes(brushes_);
}

AbstractBrushAction* BrushPalette::getCurrentBrushAction() const
{
    jassert(currentBrush_ >= 0 && currentBrush_ < brushes_.size());
    return brushes_[currentBrush_]->getBrushAction();
}

void BrushPalette::mouseDown(const MouseEvent& event)
{
    openBrushPaletteWindow();
}

void BrushPalette::paint(Graphics& g)
{
    jassert(currentBrush_ >= 0 && currentBrush_ < brushes_.size());
    AbstractCompleteBrush* brush = brushes_[currentBrush_];
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

void BrushPalette::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (brushPaletteWindow_ != nullptr)
    {
        repaint();
    }
}

void BrushPalette::openBrushPaletteWindow()
{
    if (brushPaletteWindow_ != nullptr)
    {
        return;
    }
    brushPaletteWindow_ = new BrushPaletteWindow("brush palette window",
                                                 brushes_.getRawDataPointer(),
                                                 brushes_.size(), &currentBrush_);
}
