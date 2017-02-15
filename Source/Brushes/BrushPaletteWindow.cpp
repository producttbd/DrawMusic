#include "BrushPaletteWindow.h"

#include "BrushPaletteWindowContent.h"

BrushPaletteWindow::BrushPaletteWindow(String name, BrushCollection& brushCollection)
    : BaseWindow(name)
{
  setContentOwned(new BrushPaletteWindowContent(brushCollection),
                  /*resizeToFitWhenContentChangesSize*/ false);
}