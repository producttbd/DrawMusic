#include "GridDataChangedNotifier.h"

void GridDataChangedNotifier::addGridDataResizedListener(GridDataResizedListener* listener)
{
  gridDataResizedListeners_.add(listener);
}

void GridDataChangedNotifier::removeGridDataResizedListener(GridDataResizedListener* listener)
{
  gridDataResizedListeners_.remove(listener);
}
void GridDataChangedNotifier::addGridDataUpdatedListener(GridDataUpdatedListener* listener)
{
  gridDataUpdatedListeners_.add(listener);
}
void GridDataChangedNotifier::removeGridDataUpdatedListener(GridDataUpdatedListener* listener)
{
  gridDataUpdatedListeners_.remove(listener);
}

void GridDataChangedNotifier::callGridResizedListeners()
{
  gridDataResizedListeners_.call(&GridDataResizedListener::gridDataResizedCallback);
}

void GridDataChangedNotifier::callGridUpdatedListeners()
{
  gridDataUpdatedListeners_.call(&GridDataUpdatedListener::entireGridDataUpdatedCallback);
}

void GridDataChangedNotifier::callGridUpdatedListeners(const Array<GridPoint>& affectedPoints)
{
  gridDataUpdatedListeners_.call(&GridDataUpdatedListener::partialGridDataUpdatedCallback,
                                 affectedPoints);
}