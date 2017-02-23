#ifndef GRIDACTIONMANAGER_H_INCLUDED
#define GRIDACTIONMANAGER_H_INCLUDED

#include "JuceHeader.h"

#include "BrushPalette.h"
#include "GridData.h"
#include "GridDataChangedNotifier.h"
#include "GridDataFile.h"

class GridActionManager
{
 public:
  GridActionManager(const BrushPalette& brushPalette, GridData& gridData,
                    GridDataChangedNotifier& gridDataChangedNotifier);

  void resize(int width, int height);
  void clearGrid();
  void mouseDown(const MouseEvent& event);
  void mouseDrag(const MouseEvent& event);
  void mouseUp(const MouseEvent& event);

  bool canUndo();
  void undo();
  bool canRedo();
  void redo();

  void save();
  void saveAs();
  void load();

 private:
  const BrushPalette& brushPalette_;
  GridData& gridData_;
  GridDataChangedNotifier& gridDataChangedNotifier_;
  GridDataFile gridDataFile_;

  UndoManager undoManager_;
};

#endif  // GRIDACTIONMANAGER_H_INCLUDED
