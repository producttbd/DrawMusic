#ifndef PIXELBRUSH_H_INCLUDED
#define PIXELBRUSH_H_INCLUDED

#include "JuceHeader.h"

#include "Configuration.h"
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
    void setIntensityScalar(float newValue);

    virtual Array<GridPoint> startStroke(GridPoint p, GridData& gridData);
    virtual Array<GridPoint> continueStroke(GridPoint p, GridData& gridData);
    virtual Array<GridPoint> finishStroke(GridPoint p, GridData& gridData);

protected:
    virtual Array<GridPoint> getIntermediaryPoints(GridPoint start, GridPoint end) const;
    virtual Array<GridPoint> applyBrushToStroke(const Array<GridPoint>& pointsInStroke,  GridData& gridData) const;
    virtual Array<GridPoint> applyBrushToPoint(GridPoint p, GridData& gridData) const;

    static inline float clampOutputValue(float value)
    {
        return jmax(jmin(value, Configuration::getMaxGridValue()), Configuration::getMinGridValue());
    }

    const String name_;
    Array<BrushPoint> brushPattern_;
    float intensityScalar_;

    static constexpr float minIntensityScalar_ = 0.0f;
    static constexpr float maxIntensityScalar_ = 2.0f;

    Array<GridPoint> pointsInStroke_;
    GridPoint lastPoint_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PixelBrush)
};



#endif  // PIXELBRUSH_H_INCLUDED
