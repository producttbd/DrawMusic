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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BrushPalette);
};


#endif  // BRUSHPALETTE_H_INCLUDED
