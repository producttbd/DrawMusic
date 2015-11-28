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

    explicit PixelBrush(const String name);
    virtual ~PixelBrush();

    virtual void drawInTo(Graphics& g, const GridColourScheme& colourScheme,
                          int offsetX, int offsetY) const = 0;
    void setIntensityScalar(float newValue);

    virtual Array<GridPoint> startStroke(GridPoint p, GridData& gridData);
    virtual Array<GridPoint> continueStroke(GridPoint p, GridData& gridData);
    virtual Array<GridPoint> finishStroke(GridPoint p, GridData& gridData);

protected:
    virtual Array<GridPoint> getIntermediaryPoints(GridPoint start, GridPoint end) const;
    virtual Array<GridPoint> applyBrushToStroke(const Array<GridPoint>& pointsInStroke,  GridData& gridData) const;
    virtual Array<GridPoint> applyBrushToPoint(GridPoint p, GridData& gridData) const = 0;

    static inline float clampOutputValue(float value)
    {
        return jmax(jmin(value, Configuration::getMaxGridValue()), Configuration::getMinGridValue());
    }

    const String name_;
    float intensityScalar_;

    static constexpr float minIntensityScalar_ = 0.0f;
    static constexpr float maxIntensityScalar_ = 2.0f;

    Array<GridPoint> pointsInStroke_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PixelBrush)
};

class PointClusterBrush : public PixelBrush
{
public:
    PointClusterBrush(const String name, Array<BrushPoint> brushPattern);

    void drawInTo(juce::Graphics& g, const GridColourScheme& colourScheme,
                  const int offsetX, const int offsetY) const override;

protected:
    Array<GridPoint> applyBrushToPoint(GridPoint p, GridData& gridData) const override;

private:
    Array<BrushPoint> brushPattern_;
};

class XYProfileBrush : public PixelBrush
{
public:
    XYProfileBrush(const String name, Array<float> xProfile, Array<float> yProfile,
                   int xOffset, int yOffset);

    void drawInTo(juce::Graphics& g, const GridColourScheme& colourScheme,
                  const int offsetX, const int offsetY) const override;

protected:
    Array<GridPoint> applyBrushToPoint(GridPoint p, GridData& gridData) const override;

private:
    int xOffset_;
    int yOffset_;
    Array<float> xProfile_;
    Array<float> yProfile_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XYProfileBrush)
};



#endif  // PIXELBRUSH_H_INCLUDED
