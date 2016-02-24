#ifndef BASICBRUSHCONTROLS_H_INCLUDED
#define BASICBRUSHCONTROLS_H_INCLUDED

#include "JuceHeader.h"

#include "AbstractBrushControls.h"

class BasicBrushControls : public AbstractBrushControls
{
public:
    BasicBrushControls();

    void paint(Graphics& g) override;
    void resized() override;

private:
    Slider intensitySlider_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BasicBrushControls);
};

#endif // BASICBRUSHCONTROLS_H_INCLUDED