#include "GridBrushAction.h"

GridBrushAction::GridBrushAction(GridData& gridData, AbstractBrushAction* brushAction,
                                 StrokePoint point,
                                 GridDataChangedNotifier& gridDataChangedNotifier)
    : actualGrid_(gridData),
      brushAction_(brushAction),
      point_(point),
      gridDataChangedNotifier_(gridDataChangedNotifier)
{
}

MouseDownGridBrushAction::MouseDownGridBrushAction(GridData& gridData,
                                                   AbstractBrushAction* brushAction,
                                                   StrokePoint point,
                                                   GridDataChangedNotifier& gridDataChangedNotifier)
    : GridBrushAction(gridData, brushAction, point, gridDataChangedNotifier),
      initialGridState_(gridData)
{
}

bool MouseDownGridBrushAction::perform()
{
  auto affectedPixels = brushAction_->startStroke(point_, actualGrid_);
  gridDataChangedNotifier_.callGridUpdatedListeners(affectedPixels);
  return true;
}

bool MouseDownGridBrushAction::undo()
{
  actualGrid_ = initialGridState_;
  gridDataChangedNotifier_.callGridUpdatedListeners();
  return true;
}

MouseDragGridBrushAction::MouseDragGridBrushAction(GridData& gridData,
                                                   AbstractBrushAction* brushAction,
                                                   StrokePoint point,
                                                   GridDataChangedNotifier& gridDataChangedNotifier)
    : GridBrushAction(gridData, brushAction, point, gridDataChangedNotifier)
{
}

bool MouseDragGridBrushAction::perform()
{
  auto affectedPixels = brushAction_->continueStroke(point_, actualGrid_);
  gridDataChangedNotifier_.callGridUpdatedListeners(affectedPixels);
  return true;
}

MouseUpGridBrushAction::MouseUpGridBrushAction(GridData& gridData, AbstractBrushAction* brushAction,
                                               StrokePoint point,
                                               GridDataChangedNotifier& gridDataChangedNotifier)
    : GridBrushAction(gridData, brushAction, point, gridDataChangedNotifier)
{
}

bool MouseUpGridBrushAction::perform()
{
  auto affectedPixels = brushAction_->finishStroke(point_, actualGrid_);
  gridDataChangedNotifier_.callGridUpdatedListeners(affectedPixels);
  return true;
}