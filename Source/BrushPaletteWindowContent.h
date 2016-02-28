#ifndef BRUSHPALETTEWINDOWCONTENT_H_INCLUDED
#define BRUSHPALETTEWINDOWCONTENT_H_INCLUDED

#include "JuceHeader.h"

#include "AbstractCompleteBrush.h"
#include "BrushCollection.h"
#include "BrushPreviewButton.h"

class BrushPaletteWindowContent : public Component, Button::Listener, ChangeBroadcaster
{
public:
    explicit BrushPaletteWindowContent(BrushCollection& brushCollection);
    
    // Button::Listener override
    void buttonClicked(Button* button) override;
    
    // Component override
    void paint(Graphics& g) override;
    void resized() override;

private:
    Rectangle<int> mainPreviewArea_;
    Rectangle<int> controlsArea_;
    
    BrushCollection& brushCollection_;
    OwnedArray<BrushPreviewButton> sidePreviewButtons_;
};

#endif // BRUSHPALETTEWINDOWCONTENT_H_INCLUDED