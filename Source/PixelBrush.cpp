#include "PixelBrush.h"

PixelBrush::PixelBrush(const String name, Array<BrushPoint> points)
: name_(name),
  brushPattern_(points),
  lastPoint_(0, 0)
{
}

PixelBrush::~PixelBrush()
{
    
}

void PixelBrush::drawInTo(juce::Graphics& g, const GridColourScheme& colourScheme,
                          const int offsetX, const int offsetY) const
{
    Colour zeroColour = colourScheme.convertToColour(0.0f);
    g.fillAll(zeroColour);
    for (const auto& brushPoint : brushPattern_)
    {
        const auto x = offsetX + brushPoint.x;
        const auto y = offsetY + brushPoint.y;
        g.setColour(colourScheme.convertToColour(brushPoint.z));
        g.setPixel(x, y);
    }
    g.setColour(zeroColour.contrasting());
    Rectangle<int> gBounds = g.getClipBounds();
    g.drawText(name_, 0, 0, gBounds.getWidth(), 20, Justification::left);
}

Array<GridPoint> PixelBrush::startStroke(GridPoint p, GridData &gridData) const
{
    return applyBrushToPoint(p, gridData);
}

Array<GridPoint> PixelBrush::continueStroke(GridPoint p, GridData &gridData) const
{
    return applyBrushToPoint(p, gridData);
}

Array<GridPoint> PixelBrush::finishStroke(GridPoint p, GridData &gridData) const
{
    return applyBrushToPoint(p, gridData);
}

Array<GridPoint> PixelBrush::applyBrushToPoint(GridPoint p, GridData &gridData) const
{
    Array<GridPoint> affectedPoints;
    const auto width = gridData.getWidth();
    const auto height = gridData.getHeight();
    for (const auto& brushPoint : brushPattern_)
    {
        const auto x = p.x + brushPoint.x;
        const auto y = p.y + brushPoint.y;
        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            GridPoint affectedPoint (x, y);
            switch(brushPoint.type)
            {
                case PointType::Additive:
                    gridData[affectedPoint] += brushPoint.z;
                    break;
                default:
                case PointType::Absolute:
                    gridData[affectedPoint] = brushPoint.z;
                    break;
            }
            gridData[affectedPoint] = gridData.clampToAcceptableValues(gridData[affectedPoint]);
            affectedPoints.add(affectedPoint);
        }
    }
    return affectedPoints;
}