#ifndef DRAWGRID_H_INCLUDED
#define DRAWGRID_H_INCLUDED

#include "JuceHeader.h"

#include "GridActionManager.h"
#include "GridColourScheme.h"
#include "GridData.h"
#include "GridImageRenderer.h"

class DrawGrid : public Component,
                 public GridActionManager::GridDataResizedListener,
                 public GridActionManager::GridDataUpdatedListener
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

  // GridActionManager Listeners overrides
  void entireGridDataUpdatedCallback() override;
  void partialGridDataUpdatedCallback(const Array<GridPoint>& affectedPoints) override;
  void gridDataResizedCallback() override;

 private:
  void refreshAll();

  GridActionManager& gridActionManager_;
  const GridColourScheme& colourScheme_;
  Image theImage_;
  GridImageRenderer gridImageRenderer_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DrawGrid)
};

#endif  // DRAWGRID_H_INCLUDED
