#ifndef ABSTRACTBRUSHCONTROLS_H_INCLUDED
#define ABSTRACTBRUSHCONTROLS_H_INCLUDED

#include "JuceHeader.h"

// TODO: Change this to a list of controls that the palette lays out as it wishes?
class AbstractBrushControls : public Component
{
public:
    AbstractBrushControls() {}
    virtual ~AbstractBrushControls()  {}

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AbstractBrushControls);
};

#endif // ABSTRACTBRUSHCONTROLS_H_INCLUDED