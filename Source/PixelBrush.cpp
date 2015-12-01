#include "PixelBrush.h"

PixelBrush::PixelBrush(const String name)
: name_(name),
  intensityScalar_(1.0f),
  pointsInStroke_()
{
}

PixelBrush::~PixelBrush()
{
    
}

void PixelBrush::setIntensityScalar(float newValue)
{
    intensityScalar_ = jmax(jmin(newValue, maxIntensityScalar_), minIntensityScalar_);
}

Array<GridPoint> PixelBrush::startStroke(GridPoint p, GridData &gridData)
{
    pointsInStroke_.clearQuick();
    pointsInStroke_.add(p);
    return Array<GridPoint>();
}

Array<GridPoint> PixelBrush::continueStroke(GridPoint p, GridData &gridData)
{
    pointsInStroke_.add(p);
    return Array<GridPoint>();
}

Array<GridPoint> PixelBrush::finishStroke(GridPoint p, GridData &gridData)
{
    pointsInStroke_.add(p);

    auto affectedPixels = applyBrushToStroke(pointsInStroke_, gridData);
    pointsInStroke_.clearQuick();
    return affectedPixels;
}

Array<GridPoint> PixelBrush::getIntermediaryPoints(GridPoint start, GridPoint end) const
{
    Array<GridPoint> intermediaryPoints;

    if (start == end)
    {
        intermediaryPoints.add(start);
        return intermediaryPoints;
    }

    // Bresenham's line algorithm
    auto steep = abs(end.y - start.y) > abs(end.x - start.x);

    if (steep)
    {
        std::swap(start.x, start.y);
        std::swap(end.x, end.y);
    }

    if(start.x > end.x)
    {
        std::swap(start, end);
    }

    // dx must be positive because of the above swap
    const float dx = static_cast<float>(end.x - start.x);
    const float dy = static_cast<float>(abs(end.y - start.y));

    float error = dx / 2.0f;
    const int ystep = (start.y < end.y) ? 1 : -1;
    int y = start.y;
    const int maxX = end.x;

    for(int x = start.x; x < maxX; ++x)
    {
        if(steep)
        {
            intermediaryPoints.add(GridPoint(y,x));
        }
        else
        {
            intermediaryPoints.add(GridPoint(x,y));
        }
            
        error -= dy;
        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }

    return intermediaryPoints;
}

Array<GridPoint> PixelBrush::applyBrushToStroke(const Array<GridPoint>& pointsInStroke, GridData& gridData) const
{
    jassert(pointsInStroke.size() > 1);
    Array<GridPoint> allAffectedPoints;

    GridPoint start = pointsInStroke[0];
    for (int i = 1; i < pointsInStroke.size(); ++i)
    {
        const auto intermediatePoints = getIntermediaryPoints(start, pointsInStroke[i]);
        for (const auto& point : intermediatePoints)
        {
            allAffectedPoints.addArray(applyBrushToPoint(point, gridData));
        }
        start = pointsInStroke[i];
    }
    return allAffectedPoints;
}

PointClusterBrush::PointClusterBrush(const String name, Array<BrushPoint> brushPattern)
: PixelBrush(name),
  brushPattern_(brushPattern)
{

}

void PointClusterBrush::drawInTo(juce::Graphics& g, const GridColourScheme& colourScheme,
                          const int offsetX, const int offsetY) const
{
    Colour zeroColour = colourScheme.convertToColour(0.0f);
    g.fillAll(zeroColour);
    for (const auto& brushPoint : brushPattern_)
    {
        const auto x = offsetX + brushPoint.x;
        const auto y = offsetY + brushPoint.y;
        const float value = clampOutputValue(brushPoint.z * intensityScalar_);
        g.setColour(colourScheme.convertToColour(value));
        g.setPixel(x, y);
    }
    g.setColour(zeroColour.contrasting());
    Rectangle<int> gBounds = g.getClipBounds();
    g.drawText(name_, 0, 0, gBounds.getWidth(), 20, Justification::left);
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
                    gridData[affectedPoint] = jmax(gridData[affectedPoint], brushPoint.z * intensityScalar_);
                    break;
            }
            gridData[affectedPoint] = clampOutputValue(gridData[affectedPoint]);
            affectedPoints.add(affectedPoint);
        }
    }
    return affectedPoints;
}

XYProfileBrush::XYProfileBrush(const String name, Array<float> xProfile, Array<float> yProfile,
                               int xOffset, int yOffset)
: PixelBrush(name),
  xOffset_(xOffset),
  yOffset_(yOffset),
  xProfile_(xProfile),
  yProfile_(yProfile)
{
}

void XYProfileBrush::drawInTo(juce::Graphics& g, const GridColourScheme& colourScheme,
                                    const int offsetX, const int offsetY) const
{
    Colour zeroColour = colourScheme.convertToColour(0.0f);
    g.fillAll(zeroColour);

    int y = offsetY + yOffset_;
    for (const auto& yP : yProfile_)
    {
        int x = offsetX + xOffset_;
        for (const auto& xP : xProfile_)
        {
            const float value = clampOutputValue(xP * yP * intensityScalar_);
            g.setColour(colourScheme.convertToColour(value));
            g.setPixel(x, y);
            ++x;
        }
        --y;
    }
    g.setColour(zeroColour.contrasting());
    Rectangle<int> gBounds = g.getClipBounds();
    g.drawText(name_, 0, 0, gBounds.getWidth(), 20, Justification::left);
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
