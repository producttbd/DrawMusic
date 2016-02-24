#ifndef BRUSHPALETTEWINDOW_H_INCLUDED
#define BRUSHPALETTEWINDOW_H_INCLUDED

#include "JuceHeader.h"

#include "AbstractCompleteBrush.h"
#include "BaseWindow.h"

class BrushPaletteWindow : public BaseWindow
{
public:
    BrushPaletteWindow(String name,
                       AbstractCompleteBrush** const brushes,
                       int numberBrushes, int* currentBrush);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BrushPaletteWindow);
};

#endif // BRUSHPALETTEWINDOW_H_INCLUDED