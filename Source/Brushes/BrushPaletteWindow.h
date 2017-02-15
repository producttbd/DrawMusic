#ifndef BRUSHPALETTEWINDOW_H_INCLUDED
#define BRUSHPALETTEWINDOW_H_INCLUDED

#include "JuceHeader.h"

#include "BaseWindow.h"
#include "BrushCollection.h"

class BrushPaletteWindow : public BaseWindow
{
 public:
  BrushPaletteWindow(String name, BrushCollection& brushCollection);

 private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BrushPaletteWindow);
};

#endif  // BRUSHPALETTEWINDOW_H_INCLUDED