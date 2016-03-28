#include "NoiseBrush.h"

NoiseBrush::NoiseBrush()
{
    AbstractBrushControls::ControlSpec spec({"Size", 1.0f, 150.0f, 15.0f});
    supportedControls_.add(spec);
    controlWirings_.set(spec.name, &size_);
}

void NoiseBrush::drawPreviewInto(Graphics& g, const Rectangle<int>& bounds) const
{
    Random random;
    const auto width = bounds.getWidth();
    const auto height = bounds.getHeight();
    const int centreX = bounds.getCentreX();
    const int centreY = bounds.getCentreY();

    const int size = roundDoubleToInt(size_);

    for (int x = centreX - size; x <= centreX + size; ++x)
    {
        for (int y = centreX - size; y <= centreY + size; ++y)
        {
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                const float value = clampOutputValue(random.nextFloat() * intensityScalar_);
                g.setColour(GridColourScheme::convertToColour(value));
                g.setPixel(x, y);
            }
        }
    }
}

Array<GridPoint> NoiseBrush::applyBrushToPoint(GridPoint p, GridData& gridData) const
{
    Random random;
    Array<GridPoint> affectedPoints;
    const auto width = gridData.getWidth();
    const auto height = gridData.getHeight();

    const int size = roundDoubleToInt(size_);

    for (int x = p.x - size; x <= p.x + size; ++x)
    {
        for (int y = p.y - size; y <= p.y + size; ++y)
        {
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                const float value = clampOutputValue(random.nextFloat() * intensityScalar_);
                GridPoint affectedPoint(x, y);
                if (value > gridData[affectedPoint])
                {
                    gridData[affectedPoint] = value;
                    affectedPoints.add(affectedPoint);
                }
            }
        }
    }
    return affectedPoints;
}