#include "BasicBrushBase.h"

#include "GridColourScheme.h"

using ControlSpec = AbstractBrushControls::ControlSpec;

BasicBrushBase::BasicBrushBase()
: intensityScalar_(1.0f),
  pointsInStroke_()
{
    ControlSpec spec({"Intensity", 0.0f, 2.0f, 1.0f});
    supportedControls_.add(spec);
    controlWirings_.set(spec.name, &intensityScalar_);
}

BasicBrushBase::~BasicBrushBase()
{
}

Array<AbstractBrushControls::ControlSpec> BasicBrushBase::getSupportedControls()
{
    return supportedControls_;
}

void BasicBrushBase::controlChanged(AbstractBrushControls::ControlSpec spec)
{
    if (controlWirings_.contains(spec.name))
    {
        *(controlWirings_[spec.name]) = spec.currentValue;
    }
}

Array<GridPoint> BasicBrushBase::startStroke(GridPoint p, GridData &gridData)
{
    pointsInStroke_.clearQuick();
    pointsInStroke_.add(p);
    return Array<GridPoint>();
}

Array<GridPoint> BasicBrushBase::continueStroke(GridPoint p, GridData &gridData)
{
    pointsInStroke_.add(p);
    return Array<GridPoint>();
}

Array<GridPoint> BasicBrushBase::finishStroke(GridPoint p, GridData &gridData)
{
    pointsInStroke_.add(p);

    auto affectedPixels = applyBrushToStroke(pointsInStroke_, gridData);
    pointsInStroke_.clearQuick();
    return affectedPixels;
}

void BasicBrushBase::recreateBrush(AbstractBrushControls::ControlSpec specChanged)
{
    
}

Array<GridPoint> BasicBrushBase::getIntermediaryPoints(GridPoint start, GridPoint end) const
{
    Array<GridPoint> intermediaryPoints;

    if (start == end)
    {
        intermediaryPoints.add(start);
        return intermediaryPoints;
    }

    // Bresenham's line algorithm
    auto steep = abs(end.y - start.y) > abs(end.x - start.x);

    if (steep)
    {
        std::swap(start.x, start.y);
        std::swap(end.x, end.y);
    }

    if(start.x > end.x)
    {
        std::swap(start, end);
    }

    // dx must be positive because of the above swap
    const float dx = static_cast<float>(end.x - start.x);
    const float dy = static_cast<float>(abs(end.y - start.y));

    float error = dx / 2.0f;
    const int ystep = (start.y < end.y) ? 1 : -1;
    int y = start.y;
    const int maxX = end.x;

    for(int x = start.x; x < maxX; ++x)
    {
        if(steep)
        {
            intermediaryPoints.add(GridPoint(y,x));
        }
        else
        {
            intermediaryPoints.add(GridPoint(x,y));
        }
            
        error -= dy;
        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }

    return intermediaryPoints;
}

Array<GridPoint> BasicBrushBase::applyBrushToStroke(const Array<GridPoint>& pointsInStroke, GridData& gridData) const
{
    jassert(pointsInStroke.size() > 1);
    Array<GridPoint> allAffectedPoints;

    GridPoint start = pointsInStroke[0];
    for (int i = 1; i < pointsInStroke.size(); ++i)
    {
        const auto intermediatePoints = getIntermediaryPoints(start, pointsInStroke[i]);
        for (const auto& point : intermediatePoints)
        {
            allAffectedPoints.addArray(applyBrushToPoint(point, gridData));
        }
        start = pointsInStroke[i];
    }
    return allAffectedPoints;
}