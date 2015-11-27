/*
  ==============================================================================

    BrushPalette.h
    Created: 28 Oct 2015 12:03:02pm
    Author:  Trevor Knight

  ==============================================================================
*/

#ifndef BRUSHPALETTE_H_INCLUDED
#define BRUSHPALETTE_H_INCLUDED

#include "JuceHeader.h"

#include "GridColourScheme.h"
#include "PixelBrush.h"

class BrushPalette : public Component, public Slider::Listener
{
public:
    BrushPalette(const String& componentName,
                          const GridColourScheme& colourScheme) noexcept;

    PixelBrush* getCurrentBrush() const;

    // Component overrides
    void mouseDown(const MouseEvent &event) override;
    void paint (Graphics&) override;
    void resized() override;

    // Slider::Listener overrides
    void sliderValueChanged(Slider* slider) override;

private:
    const GridColourScheme& colourScheme_;
    int currentBrush_;
    OwnedArray<PixelBrush> brushes_;
    Slider intensitySlider_;
};


#endif  // BRUSHPALETTE_H_INCLUDED
