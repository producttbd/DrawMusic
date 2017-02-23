#ifndef GRIDBRUSHACTION_H_INCLUDED
#define GRIDBRUSHACTION_H_INCLUDED

#include "JuceHeader.h"

#include "AbstractBrushAction.h"
#include "GridData.h"
#include "GridDataChangedNotifier.h"
#include "StrokePoint.h"

class GridBrushAction : public UndoableAction
{
 public:
  GridBrushAction(GridData& gridData, AbstractBrushAction* brushAction, StrokePoint point,
                  GridDataChangedNotifier& gridDataChangedNotifier);
  ~GridBrushAction() override {}

  // TODO
  UndoableAction* createCoalescedAction(UndoableAction* nextAction) override { return nullptr; }

 protected:
  GridData& actualGrid_;
  AbstractBrushAction* brushAction_;
  StrokePoint point_;
  GridDataChangedNotifier& gridDataChangedNotifier_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GridBrushAction);
};

class MouseDownGridBrushAction : public GridBrushAction
{
 public:
  MouseDownGridBrushAction(GridData& gridData, AbstractBrushAction* brushAction, StrokePoint point,
                           GridDataChangedNotifier& gridDataChangedNotifier);
  ~MouseDownGridBrushAction() override {}

  bool perform() override;
  bool undo() override;
  int getSizeInUnits() override { return 100; }

 private:
  GridData initialGridState_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MouseDownGridBrushAction);
};

class MouseDragGridBrushAction : public GridBrushAction
{
 public:
  MouseDragGridBrushAction(GridData& gridData, AbstractBrushAction* brushAction, StrokePoint point,
                           GridDataChangedNotifier& gridDataChangedNotifier);
  ~MouseDragGridBrushAction() override {}

  bool perform() override;
  bool undo() override { return true; }
  int getSizeInUnits() override { return 1; }

 private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MouseDragGridBrushAction);
};

class MouseUpGridBrushAction : public GridBrushAction
{
 public:
  MouseUpGridBrushAction(GridData& gridData, AbstractBrushAction* brushAction, StrokePoint point,
                         GridDataChangedNotifier& gridDataChangedNotifier);
  ~MouseUpGridBrushAction() override {}

  bool perform() override;
  bool undo() override { return true; }
  int getSizeInUnits() override { return 1; }

 private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MouseUpGridBrushAction);
};

#endif  // GRIDBRUSHACTION_H_INCLUDED
