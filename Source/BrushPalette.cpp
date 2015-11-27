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
  brushes_(BrushFactory::getAllBrushes()),
  intensitySlider_("intensitySlider")
{
    addAndMakeVisible(intensitySlider_);
    intensitySlider_.setSliderStyle(Slider::SliderStyle::LinearVertical);
    intensitySlider_.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    intensitySlider_.setRange(0.0, 2.0);
    intensitySlider_.setValue(1.0);
    intensitySlider_.addListener(this);
}

PixelBrush* BrushPalette::getCurrentBrush() const
{
    jassert(currentBrush_ >= 0 && currentBrush_ < brushes_.size());
    auto brush = brushes_[currentBrush_];
    brush->setIntensityScalar(intensitySlider_.getValue());
    return brush;
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
    brush->setIntensityScalar(intensitySlider_.getValue());
    brush->drawInTo(g, colourScheme_, getWidth() / 2, getHeight() / 2);
}

void BrushPalette::resized()
{
    int sliderWidth = 12;
    intensitySlider_.setBounds(getWidth() - sliderWidth, 0, sliderWidth, getHeight());
}

void BrushPalette::sliderValueChanged(Slider* slider)
{
    repaint();
}
