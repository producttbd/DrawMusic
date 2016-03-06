#ifndef POINTCLUSTERBRUSH_H_INCLUDED
#define POINTCLUSTERBRUSH_H_INCLUDED

#include "BasicBrushBase.h"

class PointClusterBrush : public BasicBrushBase
{
public:
    explicit PointClusterBrush(Array<BrushPoint> brushPattern);

    void drawPreviewInto(juce::Graphics& g, const Rectangle<int>& bounds) const override;

protected:
    Array<GridPoint> applyBrushToPoint(GridPoint p, GridData& gridData) const override;

private:
    Array<BrushPoint> brushPattern_;
};

#endif // POINTCLUSTERBRUSH_H_INCLUDED