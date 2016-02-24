#include "BasicBrushControls.h"

BasicBrushControls::BasicBrushControls()
{
    addAndMakeVisible(&intensitySlider_);
}

void BasicBrushControls::paint(Graphics& g)
{
    g.fillAll(Colours::cornflowerblue);
}

void BasicBrushControls::resized()
{
    intensitySlider_.setBounds(0, 0, getWidth(), getHeight());
}