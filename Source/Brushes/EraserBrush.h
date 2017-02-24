#ifndef ERASERBRUSH_H_INCLUDED
#define ERASERBRUSH_H_INCLUDED

#include "JuceHeader.h"

#include "../GridData/GridPoint.h"
#include "BasicBrushBase.h"
#include "StrokePoint.h"

class EraserBrush : public BasicBrushBase
{
 public:
  EraserBrush();

  void drawPreviewInto(Graphics& g, const Rectangle<int>& bounds) const override;

 protected:
  Array<GridPoint> applyBrushToPoint(StrokePoint p, GridData& gridData) const override;

  float size_;
};

#endif  // ERASERBRUSH_H_INCLUDED