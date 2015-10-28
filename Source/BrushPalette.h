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

class BrushPalette : public Component
{
public:
    BrushPalette(const String& componentName,
                          const GridColourScheme& colourScheme) noexcept;

    void mouseDown(const MouseEvent &event) override;
    void paint (Graphics&) override;
    //void resized() override;

    const PixelBrush* getCurrentBrush() const;

private:
    const GridColourScheme& colourScheme_;
    int currentBrush_;
    OwnedArray<PixelBrush> brushes_;
};


#endif  // BRUSHPALETTE_H_INCLUDED
