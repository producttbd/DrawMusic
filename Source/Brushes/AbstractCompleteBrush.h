#ifndef ABSTRACTCOMPLETEBRUSH_H_INCLUDED
#define ABSTRACTCOMPLETEBRUSH_H_INCLUDED

#include "JuceHeader.h"

#include "AbstractBrushAction.h"
#include "AbstractBrushControls.h"

class AbstractCompleteBrush
{
public:
    AbstractCompleteBrush() {}
    virtual ~AbstractCompleteBrush() {}

    virtual String getName() const = 0;
    virtual AbstractBrushControls* getBrushControls() const = 0;
    virtual AbstractBrushAction* getBrushAction() const = 0;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AbstractCompleteBrush);
};

#endif // ABSTRACTCOMPLETEBRUSH_H_INCLUDED