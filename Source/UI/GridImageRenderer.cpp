#include "GridImageRenderer.h"

GridImageRenderer::GridImageRenderer(const GridData& gridData, const GridColourScheme& colourScheme)
: gridData_(gridData), colourScheme_(colourScheme)
{
}

void GridImageRenderer::renderGridDataToImage(Image& image)
{
    for (int x = 0; x < gridData_.getWidth(); ++x)
    {
        for (int y = 0; y < gridData_.getHeight(); ++y)
        {
            image.setPixelAt(x, y, colourScheme_.convertToColour(gridData_[GridPoint(x, y)]));
        }
    }
}

void GridImageRenderer::renderSelectPointsToImage(const Array<GridPoint>& points, Image& image)
{
    for (const auto& p : points)
    {
        image.setPixelAt(p.x, p.y, colourScheme_.convertToColour(gridData_[p]));
    }
}