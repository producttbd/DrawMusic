#include "BrushPaletteWindow.h"

BrushPaletteWindow::BrushPaletteWindow(String name,
                                       BrushPaletteWindowContent& brushPaletteWindowContent)
    : BaseWindow(name)
{
  setContentNonOwned(&brushPaletteWindowContent, false);
}