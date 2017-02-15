#ifndef GRIDACTIONMANAGER_H_INCLUDED
#define GRIDACTIONMANAGER_H_INCLUDED

#include "JuceHeader.h"

#include "BrushPalette.h"
#include "GridData.h"

class GridActionManager
{
 public:
  GridActionManager(const BrushPalette& brushPalette, GridData& gridData);

  class GridDataResizedListener
  {
   public:
    virtual void gridDataResizedCallback() = 0;
    virtual ~GridDataResizedListener() {}
  };

  class GridDataUpdatedListener
  {
   public:
    virtual void newGridDataCallback() = 0;
    virtual ~GridDataUpdatedListener() {}
  };

  void addGridDataResizedListener(GridDataResizedListener* listener);
  void removeGridDataResizedListener(GridDataResizedListener* listener);
  void addGridDataUpdatedListener(GridDataUpdatedListener* listener);
  void removeGridDataUpdatedListener(GridDataUpdatedListener* listener);

  void resize(int width, int height);
  void clearGrid();
  void mouseDown(const MouseEvent& event);
  void mouseDrag(const MouseEvent& event);
  void mouseUp(const MouseEvent& event);

 private:
  void callGridResizedListeners();
  void callGridUpdatedListeners();

  const BrushPalette& brushPalette_;
  GridData& gridData_;

  ListenerList<GridDataResizedListener> gridDataResizedListeners_;
  ListenerList<GridDataUpdatedListener> gridDataUpdatedListeners_;
};

#endif  // GRIDACTIONMANAGER_H_INCLUDED
