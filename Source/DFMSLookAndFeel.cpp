#include "DFMSLookAndFeel.h"

DFMSLookAndFeel::DFMSLookAndFeel()
{
    setColour(TextButton::buttonColourId,          Colours::white);
    setColour(TextButton::buttonOnColourId,        Colours::red.withAlpha(0.6f));
    setColour(TextButton::textColourOffId,         Colours::black);
    setColour(TextButton::textColourOnId,          Colours::white);
    setColour(ListBox::outlineColourId,            findColour (ComboBox::outlineColourId));
    setColour(ScrollBar::thumbColourId,            Colour (0xffbbbbdd));
    setColour(ScrollBar::backgroundColourId,       Colours::transparentBlack);
    //setColour(Slider::backgroundColourId,          Colours::darkgrey);
    setColour(Slider::thumbColourId,               Colours::red);
    setColour(Slider::trackColourId,               Colours::white);
}

void DFMSLookAndFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
                                           bool isMouseOverButton, bool isButtonDown)
{
    const int width = button.getWidth();
    const int height = button.getHeight();

    const float indent = 1.0f;

    Path outline;
    outline.addRectangle(indent, indent, width - indent * 2.0f, height - indent * 2.0f);

    Colour bc (backgroundColour);//.withMultipliedSaturation (0.3f));

    if (isMouseOverButton)
    {
        if (isButtonDown)
            bc = bc.brighter();
        else if (bc.getBrightness() > 0.5f)
            bc = bc.darker (0.1f);
        else
            bc = bc.brighter (0.1f);
    }

    g.setColour (bc);
    g.fillPath (outline);

    g.setColour (Colours::black.withAlpha ((isMouseOverButton) ? 0.6f : 0.4f));
    g.strokePath (outline, PathStrokeType ((isMouseOverButton) ? 2.0f : 1.4f));
}
