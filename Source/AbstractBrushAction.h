#ifndef ABSTRACTBRUSHACTION_H_INCLUDED
#define ABSTRACTBRUSHACTION_H_INCLUDED

#include "JuceHeader.h"

#include "AbstractBrushControls.h"
#include "GridColourScheme.h"
#include "GridData.h"
#include "GridPoint.h"

class AbstractBrushAction :  public AbstractBrushControls::Listener
{
public:
    AbstractBrushAction() {}
    virtual ~AbstractBrushAction() {}

    virtual Array<GridPoint> startStroke(GridPoint p, GridData& gridData) = 0;
    virtual Array<GridPoint> continueStroke(GridPoint p, GridData& gridData) = 0;
    virtual Array<GridPoint> finishStroke(GridPoint p, GridData& gridData) = 0;

    virtual void drawPreviewInto(Graphics& g, const Rectangle<int>& bounds) const = 0;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AbstractBrushAction);
};

#endif // ABSTRACTBRUSHACTION_H_INCLUDED