#ifndef BASICBRUSHCONTROLS_H_INCLUDED
#define BASICBRUSHCONTROLS_H_INCLUDED

#include "JuceHeader.h"

#include "AbstractBrushControls.h"

class BasicBrushControls : public AbstractBrushControls, Slider::Listener
{
public:
    explicit BasicBrushControls();
    
    void addControl(ControlSpec spec);
    void addControls(Array<ControlSpec> specs);
    
    // Slider::Listener override
    void sliderValueChanged(Slider* slider) override;
    
    // Component overrides
    void resized() override;

private:
    OwnedArray<Slider> sliders_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BasicBrushControls);
};

#endif // BASICBRUSHCONTROLS_H_INCLUDED