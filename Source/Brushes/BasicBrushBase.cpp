#include "BasicBrushBase.h"

#include "../UI/GridColourScheme.h"

using ControlSpec = AbstractBrushControls::ControlSpec;

BasicBrushBase::BasicBrushBase() : intensityScalar_(0.5f), pointsInStroke_()
{
  ControlSpec spec({"Intensity", 0.0f, 1.0f, intensityScalar_});
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
    recreateBrush(spec);
  }
}

Array<GridPoint> BasicBrushBase::startStroke(StrokePoint p, GridData& gridData)
{
  pointsInStroke_.clearQuick();
  pointsInStroke_.add(p);
  return Array<GridPoint>();
}

Array<GridPoint> BasicBrushBase::continueStroke(StrokePoint p, GridData& gridData)
{
  pointsInStroke_.add(p);
  return Array<GridPoint>();
}

Array<GridPoint> BasicBrushBase::finishStroke(StrokePoint p, GridData& gridData)
{
  pointsInStroke_.add(p);

  auto affectedPixels = applyBrushToStroke(pointsInStroke_, gridData);
  pointsInStroke_.clearQuick();
  return affectedPixels;
}

void BasicBrushBase::recreateBrush(AbstractBrushControls::ControlSpec specChanged)
{
}

Array<StrokePoint> BasicBrushBase::getIntermediaryPoints(StrokePoint start, StrokePoint end) const
{
  Array<StrokePoint> intermediaryPoints;

  if (start.gridPoint == end.gridPoint)
  {
    intermediaryPoints.add(start);
    return intermediaryPoints;
  }

  // Bresenham's line algorithm
  auto steep = abs(end.gridPoint.y - start.gridPoint.y) > abs(end.gridPoint.x - start.gridPoint.x);

  if (steep)
  {
    std::swap(start.gridPoint.x, start.gridPoint.y);
    std::swap(end.gridPoint.x, end.gridPoint.y);
  }

  if (start.gridPoint.x > end.gridPoint.x)
  {
    std::swap(start, end);
  }

  // dx must be positive because of the above swap
  const float dx = static_cast<float>(end.gridPoint.x - start.gridPoint.x);
  const float dy = static_cast<float>(abs(end.gridPoint.y - start.gridPoint.y));
  const float dPressure = (end.pressure - start.pressure) / dx;

  float error = dx / 2.0f;
  const int ystep = (start.gridPoint.y < end.gridPoint.y) ? 1 : -1;
  int y = start.gridPoint.y;
  float pressure = start.pressure;

  for (int x = start.gridPoint.x; x < end.gridPoint.x; ++x)
  {
    if (steep)
    {
      intermediaryPoints.add(StrokePoint(y, x, pressure));
    }
    else
    {
      intermediaryPoints.add(StrokePoint(x, y, pressure));
    }

    error -= dy;
    if (error < 0)
    {
      y += ystep;
      error += dx;
    }
    pressure += dPressure;
  }

  return intermediaryPoints;
}

Array<GridPoint> BasicBrushBase::applyBrushToStroke(const Array<StrokePoint>& pointsInStroke,
                                                    GridData& gridData) const
{
  jassert(pointsInStroke.size() > 1);
  Array<GridPoint> allAffectedPoints;

  StrokePoint start = pointsInStroke[0];
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