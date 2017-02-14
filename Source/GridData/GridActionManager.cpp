#include "GridActionManager.h"

#include "Configuration.h"

GridActionManager::GridActionManager(const BrushPalette& brushPalette, GridData& gridData)
: brushPalette_(brushPalette), gridData_(gridData)
{
}

void GridActionManager::resize(int width, int height)
{
    gridData_.resize(width, height);
    sendChangeMessage();
}

void GridActionManager::clearGrid()
{
    gridData_.zero();
    sendChangeMessage();
}

void GridActionManager::mouseDown(const juce::MouseEvent& event)
{
    auto currentBrush = brushPalette_.getCurrentBrushAction();
    float pressure = event.isPressureValid() ? event.pressure : Configuration::getDefaultPressure();
    auto affectedPixels = currentBrush->startStroke(StrokePoint(event.x, event.y, pressure), gridData_);
}

void GridActionManager::mouseDrag(const juce::MouseEvent& event)
{
    auto currentBrush = brushPalette_.getCurrentBrushAction();
    float pressure = event.isPressureValid() ? event.pressure : Configuration::getDefaultPressure();
    auto affectedPixels = currentBrush->continueStroke(StrokePoint(event.x, event.y, pressure), gridData_);
}

void GridActionManager::mouseUp(const juce::MouseEvent& event)
{
    auto currentBrush = brushPalette_.getCurrentBrushAction();
    float pressure = event.isPressureValid() ? event.pressure : Configuration::getDefaultPressure();
    auto affectedPixels = currentBrush->finishStroke(StrokePoint(event.x, event.y, pressure), gridData_);
    sendChangeMessage();
}

