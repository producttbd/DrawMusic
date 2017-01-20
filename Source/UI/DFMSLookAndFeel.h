#ifndef DFMSLOOKANDFEEL_H_INCLUDED
#define DFMSLOOKANDFEEL_H_INCLUDED

#include "JuceHeader.h"

class DFMSLookAndFeel : public LookAndFeel_V1 {
public:
    DFMSLookAndFeel();

    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
                              bool isMouseOverButton, bool isButtonDown) override;
    
    static void drawOutline(Graphics& g, Component& c,
                            bool isMouseOver=false, bool isSelected=false);
    static void drawOutline(Graphics& g, Rectangle<int> bounds,
                            bool isMouseOver=false, bool isSelected=false);
    
    static Colour getDefaultBackgroundColour();
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DFMSLookAndFeel);
};

#endif  // DFMSLOOKANDFEEL_H_INCLUDED