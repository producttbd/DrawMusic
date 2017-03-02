#include "GridDataChangedNotifier.h"

void GridDataChangedNotifier::addGridDataResizedListener(GridDataResizedListener* listener)
{
  gridDataResizedListeners_.add(listener);
}

void GridDataChangedNotifier::removeGridDataResizedListener(GridDataResizedListener* listener)
{
  gridDataResizedListeners_.remove(listener);
}

void GridDataChangedNotifier::callGridResizedListeners()
{
  gridDataResizedListeners_.call(&GridDataResizedListener::gridDataResizedCallback);
}

void GridDataChangedNotifier::addGridDataUpdatedListener(GridDataUpdatedListener* listener)
{
  gridDataUpdatedListeners_.add(listener);
}

void GridDataChangedNotifier::removeGridDataUpdatedListener(GridDataUpdatedListener* listener)
{
  gridDataUpdatedListeners_.remove(listener);
}

void GridDataChangedNotifier::callGridUpdatedListeners()
{
  gridDataUpdatedListeners_.call(&GridDataUpdatedListener::entireGridDataUpdatedCallback);
}

void GridDataChangedNotifier::callGridUpdatedListenersForPartialBrushStroke(
    const Array<GridPoint>& affectedPoints)
{
  if (affectedPoints.size() > 0)
  {
    gridDataUpdatedListeners_.call(&GridDataUpdatedListener::partialBrushStrokeCallback,
                                   affectedPoints);
  }
}

void GridDataChangedNotifier::callGridUpdatedListenersForCompleteBrushStroke(
    const Array<GridPoint>& affectedPoints)
{
  if (affectedPoints.size() > 0)
  {
    gridDataUpdatedListeners_.call(&GridDataUpdatedListener::completeBrushStrokeCallback,
                                   affectedPoints);
  }
}