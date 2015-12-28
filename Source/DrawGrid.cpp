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
    
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
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
    DFMSLookAndFeel::drawComponentOutline(g, *this);
    //TODO Allow grid and image to be different sizes
}

void DrawGrid::resized()
{
}

void DrawGrid::mouseDown(const MouseEvent& event)
{
    PixelBrush* currentBrush = brushPalette_.getCurrentBrush();
    auto affectedPixels = currentBrush->startStroke(GridPoint(event.x, event.y), gridData_);
    gridImageRenderer_.renderSelectPointsToImage(gridData_, affectedPixels, theImage_);
}

void DrawGrid::mouseDrag(const juce::MouseEvent& event)
{
    PixelBrush* currentBrush = brushPalette_.getCurrentBrush();
    auto affectedPixels = currentBrush->continueStroke(GridPoint(event.x, event.y), gridData_);
    gridImageRenderer_.renderSelectPointsToImage(gridData_, affectedPixels, theImage_);
}

void DrawGrid::mouseUp(const juce::MouseEvent& event)
{
    PixelBrush* currentBrush = brushPalette_.getCurrentBrush();
    auto affectedPixels = currentBrush->finishStroke(GridPoint(event.x, event.y), gridData_);
    gridImageRenderer_.renderSelectPointsToImage(gridData_, affectedPixels, theImage_);
    repaint();
    sendChangeMessage();
}
