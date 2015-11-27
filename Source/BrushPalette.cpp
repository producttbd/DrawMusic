/*
  ==============================================================================

    BrushPalette.cpp
    Created: 28 Oct 2015 12:03:02pm
    Author:  Trevor Knight

  ==============================================================================
*/

#include "BrushPalette.h"

#include "BrushFactory.h"

BrushPalette::BrushPalette(const String& componentName, const GridColourScheme& colourScheme) noexcept
: Component(componentName),
  colourScheme_(colourScheme),
  currentBrush_(0),
  brushes_(BrushFactory::getAllBrushes())
{
}

void BrushPalette::mouseDown(const MouseEvent& event)
{
    currentBrush_ = (currentBrush_ + 1) % brushes_.size();
    jassert(currentBrush_ >= 0);
    repaint();
}

void BrushPalette::paint(Graphics& g)
{
    jassert(currentBrush_ >= 0 && currentBrush_ < brushes_.size());
    PixelBrush* brush = brushes_[currentBrush_];
    brush->drawInTo(g, colourScheme_, getWidth() / 2, getHeight() / 2);
}

PixelBrush* BrushPalette::getCurrentBrush() const
{
    jassert(currentBrush_ >= 0 && currentBrush_ < brushes_.size());
    return brushes_[currentBrush_];
}

