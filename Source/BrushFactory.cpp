/*
  ==============================================================================

    BrushFactory.cpp
    Created: 28 Oct 2015 1:16:54pm
    Author:  Trevor Knight

  ==============================================================================
*/

#include "BrushFactory.h"

using BrushPoint = PixelBrush::BrushPoint;
using PointType = PixelBrush::PointType;

OwnedArray<PixelBrush> BrushFactory::getAllBrushes()
{
    OwnedArray<PixelBrush> result;
    Array<BrushPoint> brushPattern;
    brushPattern.add(BrushPoint(-1, -1, 1.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-1, 0, 1.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-1, 1, 1.0, PointType::Absolute));
    brushPattern.add(BrushPoint(0, 1, 1.0, PointType::Absolute));
    brushPattern.add(BrushPoint(1, 1, 1.0, PointType::Absolute));
    brushPattern.add(BrushPoint(1, 0, 1.0, PointType::Absolute));
    brushPattern.add(BrushPoint(1, -1, 1.0, PointType::Absolute));
    brushPattern.add(BrushPoint(0, -1, 1.0, PointType::Absolute));
    brushPattern.add(BrushPoint(0, 0, 1.0, PointType::Absolute));
    result.add(new PixelBrush(TRANS("Square pencil"), brushPattern));

    brushPattern.clear();

    brushPattern.add(BrushPoint(0, 0, 1.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-1, -1, 0.25, PointType::Absolute));
    brushPattern.add(BrushPoint(-1, 0, 0.5, PointType::Absolute));
    brushPattern.add(BrushPoint(-1, 1, 0.25, PointType::Absolute));
    brushPattern.add(BrushPoint(0, 1, 0.5, PointType::Absolute));
    brushPattern.add(BrushPoint(1, 1, 0.25, PointType::Absolute));
    brushPattern.add(BrushPoint(1, 0, 0.5, PointType::Absolute));
    brushPattern.add(BrushPoint(1, -1, 0.25, PointType::Absolute));
    brushPattern.add(BrushPoint(0, -1, 0.5, PointType::Absolute));
    brushPattern.add(BrushPoint(0, 0, 1.0, PointType::Absolute));
    result.add(new PixelBrush(TRANS("Round pencil"), brushPattern));

    brushPattern.clear();
    brushPattern.add(BrushPoint(-1, -1, 0.2, PointType::Additive));
    brushPattern.add(BrushPoint(-1, 0, 0.2, PointType::Additive));
    brushPattern.add(BrushPoint(-1, 1, 0.2, PointType::Additive));
    brushPattern.add(BrushPoint(0, 1, 0.2, PointType::Additive));
    brushPattern.add(BrushPoint(1, 1, 0.2, PointType::Additive));
    brushPattern.add(BrushPoint(1, 0, 0.2, PointType::Additive));
    brushPattern.add(BrushPoint(1, -1, 0.2, PointType::Additive));
    brushPattern.add(BrushPoint(0, -1, 0.2, PointType::Additive));
    brushPattern.add(BrushPoint(0, 0, 0.2, PointType::Additive));
    result.add(new PixelBrush(TRANS("Square brush"), brushPattern));

    return result;
}