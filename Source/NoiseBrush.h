#ifndef NOISEBRUSH_H_INCLUDED
#define NOISEBRUSH_H_INCLUDED

#include "BasicBrushBase.h"

class NoiseBrush : public BasicBrushBase
{
public:
    NoiseBrush();

    void drawPreviewInto(Graphics& g, const Rectangle<int>& bounds) const override;

protected:
    virtual Array<GridPoint> applyBrushToPoint(GridPoint p, GridData& gridData) const override;

private:
    double size_;
    double density_;
};

#endif // NOISEBRUSH_H_INCLUDED