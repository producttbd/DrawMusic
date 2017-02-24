#ifndef XYPROFILEBRUSH_H_INCLUDED
#define XYPROFILEBRUSH_H_INCLUDED

#include "JuceHeader.h"

#include "../GridData/GridPoint.h"
#include "BasicBrushBase.h"
#include "StrokePoint.h"

class XYProfileBrush : public BasicBrushBase
{
 public:
  XYProfileBrush(Array<float> xProfile, Array<float> yProfile, int xOffset, int yOffset);

  void drawPreviewInto(juce::Graphics& g, const Rectangle<int>& bounds) const override;

 protected:
  Array<GridPoint> applyBrushToPoint(StrokePoint p, GridData& gridData) const override;

 private:
  int xOffset_;
  int yOffset_;
  Array<float> xProfile_;
  Array<float> yProfile_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XYProfileBrush)
};

#endif  // XYPROFILEBRUSH_H_INCLUDED