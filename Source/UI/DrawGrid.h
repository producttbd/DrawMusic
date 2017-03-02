#ifndef DRAWGRID_H_INCLUDED
#define DRAWGRID_H_INCLUDED

#include "JuceHeader.h"

#include "../GridData/GridActionManager.h"
#include "../GridData/GridData.h"
#include "../GridData/GridDataChangedNotifier.h"
#include "GridColourScheme.h"
#include "GridImageRenderer.h"

class DrawGrid : public Component,
                 public GridDataChangedNotifier::GridDataResizedListener,
                 public GridDataChangedNotifier::GridDataUpdatedListener
{
 public:
  DrawGrid(GridActionManager& gridActionManager, const GridData& gridData,
           const GridColourScheme& colourScheme);
  ~DrawGrid() override{};

  // Component overrides
  void paint(Graphics&) override;
  void resized() override;

  void mouseDown(const MouseEvent& event) override;
  void mouseDrag(const MouseEvent& event) override;
  void mouseUp(const MouseEvent& event) override;

  // GridDataChangedNotifier Listeners overrides
  void entireGridDataUpdatedCallback() override;
  void partialBrushStrokeCallback(const Array<GridPoint>& affectedPoints) override;
  void completeBrushStrokeCallback(const Array<GridPoint>& affectedPoints) override;
  void gridDataResizedCallback() override;

 private:
  void rerenderPoints(const Array<GridPoint>& affectedPoints);
  void refreshAll();

  // To handle clicks on the UI element.
  GridActionManager& gridActionManager_;
  const GridColourScheme& colourScheme_;
  Image theImage_;
  GridImageRenderer gridImageRenderer_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DrawGrid)
};

#endif  // DRAWGRID_H_INCLUDED
