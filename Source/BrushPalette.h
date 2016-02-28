#ifndef BRUSHPALETTE_H_INCLUDED
#define BRUSHPALETTE_H_INCLUDED

#include "JuceHeader.h"

#include "AbstractBrushAction.h"
#include "AbstractCompleteBrush.h"
#include "BrushPaletteWindow.h"
#include "GridColourScheme.h"
#include "PixelBrush.h"

class BrushPalette : public Component, ChangeListener
{
public:
    BrushPalette(const String& componentName,
                 const GridColourScheme& colourScheme) noexcept;

    AbstractBrushAction* getCurrentBrushAction() const;    
    
    // Component overrides
    void mouseDown(const MouseEvent &event) override;
    void paint (Graphics&) override;
    void resized() override;

    // ChangeListener
    void changeListenerCallback(ChangeBroadcaster* source) override;

private:
    void openBrushPaletteWindow();

    const GridColourScheme& colourScheme_;
    int currentBrush_;
    BrushCollection brushCollection_;
    Component::SafePointer<BrushPaletteWindow> brushPaletteWindow_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BrushPalette);
};


#endif  // BRUSHPALETTE_H_INCLUDED
