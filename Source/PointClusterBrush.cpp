#include "PointClusterBrush.h"

PointClusterBrush::PointClusterBrush(Array<BrushPoint> brushPattern)
: BasicBrushBase(),
  brushPattern_(brushPattern)
{

}

void PointClusterBrush::drawPreviewInto(
        juce::Graphics& g, const Rectangle<int>& bounds) const
{
    Colour zeroColour = GridColourScheme::convertToColour(0.0f);
    g.fillAll(zeroColour);
    for (const auto& brushPoint : brushPattern_)
    {
        const auto x = bounds.getCentreX() + brushPoint.x;
        const auto y = bounds.getCentreY() + brushPoint.y;
        const float value = clampOutputValue(brushPoint.z * intensityScalar_);
        g.setColour(GridColourScheme::convertToColour(value));
        g.setPixel(x, y);
    }
}

Array<GridPoint> PointClusterBrush::applyBrushToPoint(GridPoint p, GridData& gridData) const
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
                    gridData[affectedPoint] += (brushPoint.z * intensityScalar_);
                    break;
                default:
                case PointType::Absolute:
                    gridData[affectedPoint] = jmax(gridData[affectedPoint], brushPoint.z * (float)intensityScalar_);
                    break;
            }
            gridData[affectedPoint] = clampOutputValue(gridData[affectedPoint]);
            affectedPoints.add(affectedPoint);
        }
    }
    return affectedPoints;
}