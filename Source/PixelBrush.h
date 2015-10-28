#ifndef PIXELBRUSH_H_INCLUDED
#define PIXELBRUSH_H_INCLUDED

#include "JuceHeader.h"

#include "GridColourScheme.h"
#include "GridData.h"
#include "GridPoint.h"

class PixelBrush
{
public:
    enum class PointType
    {
        Absolute,
        Additive
    };

    struct BrushPoint : public GridPoint
    {
        BrushPoint(int x, int y, float z, PointType type)
        : GridPoint(x, y),
          z(z),
          type(type)
        {
        }

        float z;
        PointType type;
    };

    PixelBrush(const String name, Array<BrushPoint> points);
    virtual ~PixelBrush();
    void drawInTo(Graphics& g, const GridColourScheme& colourScheme,
                  int offsetX, int offsetY) const;

    virtual Array<GridPoint> startStroke(GridPoint p, GridData& gridData) const;
    virtual Array<GridPoint> continueStroke(GridPoint p, GridData& gridData) const;
    virtual Array<GridPoint> finishStroke(GridPoint p, GridData& gridData) const;

private:
    Array<GridPoint> applyBrushToPoint(GridPoint p, GridData& gridData) const;

    const String name_;
    Array<BrushPoint> brushPattern_;
    GridPoint lastPoint_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PixelBrush)
};



#endif  // PIXELBRUSH_H_INCLUDED
