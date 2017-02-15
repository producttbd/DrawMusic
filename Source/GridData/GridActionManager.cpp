#include "GridActionManager.h"

#include "Configuration.h"

GridActionManager::GridActionManager(const BrushPalette& brushPalette, GridData& gridData)
    : brushPalette_(brushPalette), gridData_(gridData)
{
}

void GridActionManager::addGridDataResizedListener(GridDataResizedListener* listener)
{
  gridDataResizedListeners_.add(listener);
}

void GridActionManager::removeGridDataResizedListener(GridDataResizedListener* listener)
{
  gridDataResizedListeners_.remove(listener);
}
void GridActionManager::addGridDataUpdatedListener(GridDataUpdatedListener* listener)
{
  gridDataUpdatedListeners_.add(listener);
}
void GridActionManager::removeGridDataUpdatedListener(GridDataUpdatedListener* listener)
{
  gridDataUpdatedListeners_.remove(listener);
}

void GridActionManager::resize(int width, int height)
{
  gridData_.resize(width, height);
  callGridResizedListeners();
}

void GridActionManager::clearGrid()
{
  gridData_.zero();
  callGridUpdatedListeners();
}

void GridActionManager::mouseDown(const juce::MouseEvent& event)
{
  auto currentBrush = brushPalette_.getCurrentBrushAction();
  float pressure = event.isPressureValid() ? event.pressure : Configuration::getDefaultPressure();
  auto affectedPixels =
      currentBrush->startStroke(StrokePoint(event.x, event.y, pressure), gridData_);
}

void GridActionManager::mouseDrag(const juce::MouseEvent& event)
{
  auto currentBrush = brushPalette_.getCurrentBrushAction();
  float pressure = event.isPressureValid() ? event.pressure : Configuration::getDefaultPressure();
  auto affectedPixels =
      currentBrush->continueStroke(StrokePoint(event.x, event.y, pressure), gridData_);
}

void GridActionManager::mouseUp(const juce::MouseEvent& event)
{
  auto currentBrush = brushPalette_.getCurrentBrushAction();
  float pressure = event.isPressureValid() ? event.pressure : Configuration::getDefaultPressure();
  auto affectedPixels =
      currentBrush->finishStroke(StrokePoint(event.x, event.y, pressure), gridData_);
  callGridUpdatedListeners();
}

void GridActionManager::callGridResizedListeners()
{
  gridDataResizedListeners_.call(&GridDataResizedListener::gridDataResizedCallback);
}

void GridActionManager::callGridUpdatedListeners()
{
  gridDataUpdatedListeners_.call(&GridDataUpdatedListener::newGridDataCallback);
}
