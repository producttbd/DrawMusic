#include "XYProfileBrush.h"

XYProfileBrush::XYProfileBrush(Array<float> xProfile, Array<float> yProfile,
                               int xOffset, int yOffset)
: BasicBrushBase(),
  xOffset_(xOffset),
  yOffset_(yOffset),
  xProfile_(xProfile),
  yProfile_(yProfile)
{
}

void XYProfileBrush::drawPreviewInto(juce::Graphics& g, const Rectangle<int>& bounds) const
{
    const Colour zeroColour = GridColourScheme::convertToColour(0.0f);
    g.fillAll(zeroColour);

    int y = bounds.getCentreY() + yOffset_;
    for (const auto& yP : yProfile_)
    {
        int x = bounds.getCentreX() + xOffset_;
        for (const auto& xP : xProfile_)
        {
            const float value = clampOutputValue(xP * yP * intensityScalar_);
            g.setColour(GridColourScheme::convertToColour(value));
            g.setPixel(x, y);
            ++x;
        }
        --y;
    }
}

Array<GridPoint> XYProfileBrush::applyBrushToPoint(GridPoint p, GridData& gridData) const
{
    Array<GridPoint> affectedPoints;
    const auto width = gridData.getWidth();
    const auto height = gridData.getHeight();

    int y = p.y + yOffset_;
    for (const auto& yP : yProfile_)
    {
        int x = p.x + xOffset_;
        for (const auto& xP : xProfile_)
        {
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                const float value = clampOutputValue(xP * yP * intensityScalar_);
                GridPoint affectedPoint(x, y);
                gridData[affectedPoint] = jmax(value, gridData[affectedPoint]);
                affectedPoints.add(affectedPoint);
            }
            ++x;
        }
        --y;
    }
    return affectedPoints;
}