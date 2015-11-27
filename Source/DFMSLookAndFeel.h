#ifndef DFMSLOOKANDFEEL_H_INCLUDED
#define DFMSLOOKANDFEEL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class DFMSLookAndFeel : public LookAndFeel_V1 {
public:
    DFMSLookAndFeel();

    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
                              bool isMouseOverButton, bool isButtonDown) override;

    //void draw

};



#endif  // DFMSLOOKANDFEEL_H_INCLUDED
