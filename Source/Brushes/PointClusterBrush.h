#ifndef POINTCLUSTERBRUSH_H_INCLUDED
#define POINTCLUSTERBRUSH_H_INCLUDED

#include "../GridData/GridPoint.h"
#include "BasicBrushBase.h"
#include "StrokePoint.h"

class PointClusterBrush : public BasicBrushBase
{
 public:
  enum class PointType
  {
    Absolute,
    Additive
  };

  struct BrushPoint : public GridPoint
  {
    BrushPoint(int x, int y, float z, PointType type) : GridPoint(x, y), z(z), type(type) {}

    float z;
    PointType type;
  };

  explicit PointClusterBrush(Array<BrushPoint> brushPattern);

  void drawPreviewInto(juce::Graphics& g, const Rectangle<int>& bounds) const override;

 protected:
  Array<GridPoint> applyBrushToPoint(StrokePoint p, GridData& gridData) const override;

 private:
  Array<BrushPoint> brushPattern_;
};

#endif  // POINTCLUSTERBRUSH_H_INCLUDED