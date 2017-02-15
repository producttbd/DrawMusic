#ifndef COMBBRUSH_H_INCLUDED
#define COMBBRUSH_H_INCLUDED

#include "JuceHeader.h"

#include "BasicBrushBase.h"
#include "GridData.h"
#include "StrokePoint.h"

class CombBrush : public BasicBrushBase
{
 public:
  CombBrush();

  void drawPreviewInto(Graphics& g, const Rectangle<int>& bounds) const override;

 protected:
  Array<GridPoint> applyBrushToPoint(StrokePoint p, GridData& gridData) const override;

  float numberHarmonics_;
  float evenIntensity_;
  float oddIntensity_;
  float taper_;
  float spacing_;
};

#endif  // COMBBRUSH_H_INCLUDED