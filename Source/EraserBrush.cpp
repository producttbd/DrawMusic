#include "EraserBrush.h"

EraserBrush::EraserBrush()
: size_(5.0f)
{
    AbstractBrushControls::ControlSpec spec({"Size", 1.0f, 50.0f, size_});
    supportedControls_.add(spec);
    controlWirings_.set(spec.name, &size_);
}

void EraserBrush::drawPreviewInto(juce::Graphics& g, const Rectangle<int>& bounds) const
{
    const Colour oneColour = GridColourScheme::convertToColour(1.0f);
    g.fillAll(oneColour);
    const Colour squareColour = GridColourScheme::convertToColour(1.0f - intensityScalar_);
    g.setFillType(FillType(squareColour));
    const int size = roundDoubleToInt(size_);
    g.fillRect(bounds.getCentreY() - size, bounds.getCentreY() - size, size * 2, size * 2);
}

Array<GridPoint> EraserBrush::applyBrushToPoint(GridPoint p, GridData& gridData) const
{
    Array<GridPoint> affectedPoints;
    const auto width = gridData.getWidth();
    const auto height = gridData.getHeight();

    const float intensityImpact = 1.0f - intensityScalar_;
    const int size = roundDoubleToInt(size_);

    for (int x = p.x - size; x <= p.x + size; ++x)
    {
        for (int y = p.y - size; y <= p.y + size; ++y)
        {
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                GridPoint affectedPoint(x, y);
                const float value = clampOutputValue(intensityImpact * gridData[affectedPoint]);
                gridData[affectedPoint] = value;
                affectedPoints.add(affectedPoint);
            }
        }
    }
    return affectedPoints;
}