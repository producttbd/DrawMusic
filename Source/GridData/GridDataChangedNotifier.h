#ifndef GRIDDATACHANGEDNOTIFIER_H_INCLUDED
#define GRIDDATACHANGEDNOTIFIER_H_INCLUDED

#include "JuceHeader.h"

#include "GridPoint.h"

class GridDataChangedNotifier
{
 public:
  GridDataChangedNotifier() = default;

  class GridDataResizedListener
  {
   public:
    virtual void gridDataResizedCallback() = 0;
    virtual ~GridDataResizedListener() {}
  };

  class GridDataUpdatedListener
  {
   public:
    virtual void entireGridDataUpdatedCallback() = 0;
    virtual void partialGridDataUpdatedCallback(const Array<GridPoint>& affectedPoints) = 0;
    virtual ~GridDataUpdatedListener() {}
  };

  void addGridDataResizedListener(GridDataResizedListener* listener);
  void removeGridDataResizedListener(GridDataResizedListener* listener);
  void addGridDataUpdatedListener(GridDataUpdatedListener* listener);
  void removeGridDataUpdatedListener(GridDataUpdatedListener* listener);

  void callGridResizedListeners();
  void callGridUpdatedListeners();
  void callGridUpdatedListeners(const Array<GridPoint>& affectedPoints);

 private:
  ListenerList<GridDataResizedListener> gridDataResizedListeners_;
  ListenerList<GridDataUpdatedListener> gridDataUpdatedListeners_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GridDataChangedNotifier);
};

#endif  // GRIDDATACHANGEDNOTIFIER_H_INCLUDED
