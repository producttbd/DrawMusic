#ifndef DFMSLOOKANDFEEL_H_INCLUDED
#define DFMSLOOKANDFEEL_H_INCLUDED

#include "JuceHeader.h"

class DFMSLookAndFeel : public LookAndFeel_V1 {
public:
    DFMSLookAndFeel();

    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
                              bool isMouseOverButton, bool isButtonDown) override;
    
    static void drawComponentOutline(Graphics& g, Component& c);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DFMSLookAndFeel);
};

#endif  // DFMSLOOKANDFEEL_H_INCLUDED