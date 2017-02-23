#include "GridActionManager.h"

#include "Configuration.h"
#include "GridBrushAction.h"

GridActionManager::GridActionManager(const BrushPalette& brushPalette, GridData& gridData,
                                     GridDataChangedNotifier& gridDataChangedNotifier)
    : brushPalette_(brushPalette),
      gridData_(gridData),
      gridDataChangedNotifier_(gridDataChangedNotifier),
      gridDataFile_(gridData_),
      undoManager_(1000 /* maxNumberOfUnitsToKeep */, 1 /* minimumTransactionsToKeep */)
{
}

void GridActionManager::resize(int width, int height)
{
  gridData_.resize(width, height);
  undoManager_.clearUndoHistory();
  gridDataChangedNotifier_.callGridResizedListeners();
}

void GridActionManager::clearGrid()
{
  gridData_.zero();
  undoManager_.clearUndoHistory();
  gridDataChangedNotifier_.callGridUpdatedListeners();
}

void GridActionManager::mouseDown(const juce::MouseEvent& event)
{
  float pressure = event.isPressureValid() ? event.pressure : Configuration::getDefaultPressure();
  undoManager_.beginNewTransaction();
  UndoableAction* action = new MouseDownGridBrushAction(
      gridData_, brushPalette_.getCurrentBrushAction(), StrokePoint(event.x, event.y, pressure),
      gridDataChangedNotifier_);
  undoManager_.perform(action);
}

void GridActionManager::mouseDrag(const juce::MouseEvent& event)
{
  float pressure = event.isPressureValid() ? event.pressure : Configuration::getDefaultPressure();
  UndoableAction* action = new MouseDragGridBrushAction(
      gridData_, brushPalette_.getCurrentBrushAction(), StrokePoint(event.x, event.y, pressure),
      gridDataChangedNotifier_);
  undoManager_.perform(action);
}

void GridActionManager::mouseUp(const juce::MouseEvent& event)
{
  float pressure = event.isPressureValid() ? event.pressure : Configuration::getDefaultPressure();
  UndoableAction* action =
      new MouseUpGridBrushAction(gridData_, brushPalette_.getCurrentBrushAction(),
                                 StrokePoint(event.x, event.y, pressure), gridDataChangedNotifier_);
  undoManager_.perform(action);
}

bool GridActionManager::canUndo()
{
  return undoManager_.canUndo();
}

void GridActionManager::undo()
{
  undoManager_.undo();
}

bool GridActionManager::canRedo()
{
  return undoManager_.canRedo();
}

void GridActionManager::redo()
{
  undoManager_.redo();
}

void GridActionManager::save()
{
  gridDataFile_.save(true /* askUserForFileIfNotSpecified */, true /* showMessageOnFailure */);
}

void GridActionManager::saveAs()
{
  gridDataFile_.saveAsInteractive(true /* warnAboutOverwritingExistingFiles */);
}

void GridActionManager::load()
{
  gridDataFile_.loadFromUserSpecifiedFile(true /* showMessageOnFailure */);
  gridDataChangedNotifier_.callGridUpdatedListeners();
}