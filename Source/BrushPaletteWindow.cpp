#include "BrushPaletteWindow.h"


#include "BrushPaletteWindowContent.h"
#include "Configuration.h"
#include "DFMSLookAndFeel.h"

BrushPaletteWindow::BrushPaletteWindow(String name,
                                       AbstractCompleteBrush** const brushes,
                                       int numberBrushes, int* currentBrush)
: BaseWindow(name)
{
    setContentOwned(new BrushPaletteWindowContent(brushes, numberBrushes, currentBrush), false);
}