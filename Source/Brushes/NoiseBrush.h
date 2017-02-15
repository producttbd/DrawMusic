#ifndef NOISEBRUSH_H_INCLUDED
#define NOISEBRUSH_H_INCLUDED

#include "BasicBrushBase.h"
#include "GridPoint.h"
#include "StrokePoint.h"

class NoiseBrush : public BasicBrushBase
{
 public:
  NoiseBrush();

  void drawPreviewInto(Graphics& g, const Rectangle<int>& bounds) const override;

 protected:
  virtual Array<GridPoint> applyBrushToPoint(StrokePoint p, GridData& gridData) const override;

 private:
  float size_;
  float density_;
};

#endif  // NOISEBRUSH_H_INCLUDED