#include "Configuration.h"
#include "DFMSLookAndFeel.h"
#include "DrawGrid.h"

DrawGrid::DrawGrid(GridActionManager& gridActionManager, const GridData& gridData, const GridColourScheme& colourScheme)
: gridActionManager_(gridActionManager),
  colourScheme_(colourScheme),
  theImage_(Image::PixelFormat::ARGB, Configuration::getGridWidth(),
            Configuration::getGridHeight(), true),
  gridImageRenderer_(gridData, colourScheme)
{
    setOpaque(true);
    setMouseCursor(MouseCursor::CrosshairCursor);
}

void DrawGrid::refreshAll()
{
    gridImageRenderer_.renderGridDataToImage(theImage_);
    repaint();
}

void DrawGrid::paint (Graphics& g)
{
    g.drawImageAt(theImage_, 0, 0);
    DFMSLookAndFeel::drawOutline(g, *this);
}

void DrawGrid::resized()
{
    theImage_ = Image(Image::PixelFormat::ARGB, Configuration::getGridWidth(), Configuration::getGridHeight(), true);
    refreshAll();
}

void DrawGrid::mouseDown(const MouseEvent& event)
{
    gridActionManager_.mouseDown(event);
}

void DrawGrid::mouseDrag(const juce::MouseEvent& event)
{
    if (event.mods.isShiftDown() && event.y != event.getMouseDownY())
    {
        MouseInputSource inputSource = event.source;
        inputSource.setScreenPosition(Point<float>(event.getScreenX(), event.getMouseDownScreenY()));
        return;
    }
    gridActionManager_.mouseDrag(event);
}

void DrawGrid::mouseUp(const juce::MouseEvent& event)
{
    gridActionManager_.mouseUp(event);
}

void DrawGrid::newGridDataCallback()
{
    // TODO selectively re-render
    refreshAll();
}

void DrawGrid::gridDataResizedCallback()
{
    resized();
}