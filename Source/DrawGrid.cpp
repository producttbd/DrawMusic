#include "Configuration.h"
#include "DFMSLookAndFeel.h"
#include "DrawGrid.h"

DrawGrid::DrawGrid(GridData& gridData, const GridColourScheme& colourScheme,
                   const BrushPalette& brushPalette)
: gridData_(gridData),
  brushPalette_(brushPalette),
  colourScheme_(colourScheme),
  theImage_(Image::PixelFormat::ARGB, Configuration::getGridWidth(),
            Configuration::getGridHeight(), true),
  gridImageRenderer_(colourScheme)
{
    setOpaque(true);
    
    setMouseCursor(MouseCursor::CrosshairCursor);
    
    gridImageRenderer_.renderGridDataToImage(gridData_, theImage_);
}

DrawGrid::~DrawGrid()
{
}

void DrawGrid::refreshAll()
{
    gridImageRenderer_.renderGridDataToImage(gridData_, theImage_);
    repaint();
    sendChangeMessage();
}

void DrawGrid::paint (Graphics& g)
{
    g.drawImageAt(theImage_, 0, 0);
    DFMSLookAndFeel::drawOutline(g, *this);
    //TODO Allow grid and image to be different sizes
}

void DrawGrid::resized()
{
}

void DrawGrid::mouseDown(const MouseEvent& event)
{
    auto currentBrush = brushPalette_.getCurrentBrushAction();
    float pressure = event.isPressureValid() ? event.pressure : Configuration::getDefaultPressure();
    auto affectedPixels = currentBrush->startStroke(StrokePoint(event.x, event.y, pressure), gridData_);
    gridImageRenderer_.renderSelectPointsToImage(gridData_, affectedPixels, theImage_);
}

void DrawGrid::mouseDrag(const juce::MouseEvent& event)
{
    if (event.mods.isShiftDown() && event.y != event.getMouseDownY())
    {
        MouseInputSource inputSource = event.source;
        inputSource.setScreenPosition(Point<float>(event.getScreenX(), event.getMouseDownScreenY()));
        return;
    }
    auto currentBrush = brushPalette_.getCurrentBrushAction();
    std::cout << (event.isPressureValid() ? "valid pressure" : "not valid pressure") << std::endl;
    float pressure = event.isPressureValid() ? event.pressure : Configuration::getDefaultPressure();
    auto affectedPixels = currentBrush->continueStroke(StrokePoint(event.x, event.y, pressure), gridData_);
    gridImageRenderer_.renderSelectPointsToImage(gridData_, affectedPixels, theImage_);
}

void DrawGrid::mouseUp(const juce::MouseEvent& event)
{
    auto currentBrush = brushPalette_.getCurrentBrushAction();
    float pressure = event.isPressureValid() ? event.pressure : Configuration::getDefaultPressure();
    auto affectedPixels = currentBrush->finishStroke(StrokePoint(event.x, event.y, pressure), gridData_);
    gridImageRenderer_.renderSelectPointsToImage(gridData_, affectedPixels, theImage_);
    repaint();
    sendChangeMessage();
}
