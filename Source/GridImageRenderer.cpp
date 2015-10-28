/*
 ==============================================================================
 
 GridImageRenderer.cpp
 Created: 5 Jul 2015 7:08:44pm
 Author:  Trevor Knight
 
 ==============================================================================
*/

#include "GridImageRenderer.h"

GridImageRenderer::GridImageRenderer(const GridColourScheme& colourScheme)
: colourScheme_(colourScheme)
{
}

void GridImageRenderer::renderGridDataToImage(const GridData& gridData, Image& image)
{
    for (int x = 0; x < gridData.getWidth(); ++x)
    {
        for (int y = 0; y < gridData.getHeight(); ++y)
        {
            image.setPixelAt(x, y, colourScheme_.convertToColour((gridData)[GridPoint(x, y)]));
        }
    }
}

void GridImageRenderer::renderSelectPointsToImage(const GridData& gridData, const Array<GridPoint>& points, Image& image)
{
    for (const auto& p : points)
    {
        image.setPixelAt(p.x, p.y, colourScheme_.convertToColour((gridData)[p]));
    }
}