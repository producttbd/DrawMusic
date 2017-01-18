#include "NoiseBrush.h"

#include "AbstractBrushControls.h"
#include "GridColourScheme.h"

NoiseBrush::NoiseBrush()
: size_(25.0f), density_(0.2)
{
    AbstractBrushControls::ControlSpec spec({"Size", 1.0f, 150.0f, size_});
    supportedControls_.add(spec);
    controlWirings_.set(spec.name, &size_);

    spec = AbstractBrushControls::ControlSpec({"Density", 0.0f, 1.0f, density_});
    supportedControls_.add(spec);
    controlWirings_.set(spec.name, &density_);
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
                if (random.nextFloat() < density_)
                {
                    const float value = clampOutputValue(random.nextFloat() * intensityScalar_);
                    g.setColour(GridColourScheme::convertToColour(value));
                    g.setPixel(x, y);
                }
            }
        }
    }
}

Array<GridPoint> NoiseBrush::applyBrushToPoint(StrokePoint p, GridData& gridData) const
{
    Random random;
    Array<GridPoint> affectedPoints;
    const auto width = gridData.getWidth();
    const auto height = gridData.getHeight();

    const int size = roundDoubleToInt(size_);

    for (int x = p.gridPoint.x - size; x <= p.gridPoint.x + size; ++x)
    {
        for (int y = p.gridPoint.y - size; y <= p.gridPoint.y + size; ++y)
        {
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                if (random.nextFloat() < density_)
                {
                    const float value = clampOutputValue(random.nextFloat() * intensityScalar_ * p.pressure);
                    GridPoint affectedPoint(x, y);
                    if (value > gridData[affectedPoint])
                    {
                        gridData[affectedPoint] = value;
                        affectedPoints.add(affectedPoint);
                    }
                }
            }
        }
    }
    return affectedPoints;
}