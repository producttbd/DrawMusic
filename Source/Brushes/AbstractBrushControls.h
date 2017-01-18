#ifndef ABSTRACTBRUSHCONTROLS_H_INCLUDED
#define ABSTRACTBRUSHCONTROLS_H_INCLUDED

#include "JuceHeader.h"

class AbstractBrushControls : public Component
{
public:
    struct ControlSpec
    {
        String name;
        float minValue;
        float maxValue;
        float currentValue;
    };
    
    class Listener
    {
    public:
        virtual ~Listener() {}
        virtual void controlChanged(ControlSpec spec) = 0;
    };
    
    AbstractBrushControls() {}
    virtual ~AbstractBrushControls()  {}
    
    virtual void addListener(AbstractBrushControls::Listener* listener)
    {
        listeners_.add(listener);
    }
    
protected:
    ListenerList<AbstractBrushControls::Listener> listeners_;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AbstractBrushControls);
};

#endif // ABSTRACTBRUSHCONTROLS_H_INCLUDED