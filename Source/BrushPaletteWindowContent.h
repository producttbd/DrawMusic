#ifndef BRUSHPALETTEWINDOWCONTENT_H_INCLUDED
#define BRUSHPALETTEWINDOWCONTENT_H_INCLUDED

#include "JuceHeader.h"

#include "AbstractCompleteBrush.h"

class BrushPaletteWindowContent : public Component, ChangeBroadcaster
{
public:
    explicit BrushPaletteWindowContent(AbstractCompleteBrush** const brushes,
                                       int numberBrushes, int* currentBrush);

    void paint(Graphics& g) override;

private:
    AbstractCompleteBrush** const brushes_;
    int numberBrushes_;
    int* currentBrush_;

};

#endif // BRUSHPALETTEWINDOWCONTENT_H_INCLUDED