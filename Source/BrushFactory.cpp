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

    brushPattern.clear();

    brushPattern.add(BrushPoint(-4, -4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-3, -4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-2, -4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-1, -4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint( 0, -4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint( 1, -4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint( 2, -4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint( 3, -4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint( 4, -4, 0.0, PointType::Absolute));

    brushPattern.add(BrushPoint(-4, -3, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-3, -3, 0.02144660940672623, PointType::Absolute));
    brushPattern.add(BrushPoint(-2, -3, 0.07322330470336309, PointType::Absolute));
    brushPattern.add(BrushPoint(-1, -3, 0.12499999999999997, PointType::Absolute));
    brushPattern.add(BrushPoint( 0, -3, 0.1464466094067262, PointType::Absolute));
    brushPattern.add(BrushPoint( 1, -3, 0.12499999999999999, PointType::Absolute));
    brushPattern.add(BrushPoint( 2, -3, 0.07322330470336312, PointType::Absolute));
    brushPattern.add(BrushPoint( 3, -3, 0.021446609406726238, PointType::Absolute));
    brushPattern.add(BrushPoint( 4, -3, 0.0, PointType::Absolute));

    brushPattern.add(BrushPoint(-4, -2, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-3, -2, 0.07322330470336309, PointType::Absolute));
    brushPattern.add(BrushPoint(-2, -2, 0.24999999999999994, PointType::Absolute));
    brushPattern.add(BrushPoint(-1, -2, 0.4267766952966368, PointType::Absolute));
    brushPattern.add(BrushPoint( 0, -2, 0.49999999999999994, PointType::Absolute));
    brushPattern.add(BrushPoint( 1, -2, 0.42677669529663687, PointType::Absolute));
    brushPattern.add(BrushPoint( 2, -2, 0.25, PointType::Absolute));
    brushPattern.add(BrushPoint( 3, -2, 0.07322330470336312, PointType::Absolute));
    brushPattern.add(BrushPoint( 4, -2, 0.0, PointType::Absolute));

    brushPattern.add(BrushPoint(-4, -1, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-3, -1, 0.12499999999999997, PointType::Absolute));
    brushPattern.add(BrushPoint(-2, -1, 0.4267766952966368, PointType::Absolute));
    brushPattern.add(BrushPoint(-1, -1, 0.7285533905932737, PointType::Absolute));
    brushPattern.add(BrushPoint( 0, -1, 0.8535533905932737, PointType::Absolute));
    brushPattern.add(BrushPoint( 1, -1, 0.7285533905932738, PointType::Absolute));
    brushPattern.add(BrushPoint( 2, -1, 0.426776695296637, PointType::Absolute));
    brushPattern.add(BrushPoint( 3, -1, 0.12500000000000003, PointType::Absolute));
    brushPattern.add(BrushPoint( 4, -1, 0.0, PointType::Absolute));

    brushPattern.add(BrushPoint(-4, 0, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-3, 0, 0.1464466094067262, PointType::Absolute));
    brushPattern.add(BrushPoint(-2, 0, 0.49999999999999994, PointType::Absolute));
    brushPattern.add(BrushPoint(-1, 0, 0.8535533905932737, PointType::Absolute));
    brushPattern.add(BrushPoint( 0, 0, 1.0, PointType::Absolute));
    brushPattern.add(BrushPoint( 1, 0, 0.8535533905932738, PointType::Absolute));
    brushPattern.add(BrushPoint( 2, 0, 0.5000000000000001, PointType::Absolute));
    brushPattern.add(BrushPoint( 3, 0, 0.14644660940672627, PointType::Absolute));
    brushPattern.add(BrushPoint( 4, 0, 0.0, PointType::Absolute));

    brushPattern.add(BrushPoint(-4, 1, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-3, 1, 0.12499999999999999, PointType::Absolute));
    brushPattern.add(BrushPoint(-2, 1, 0.42677669529663687, PointType::Absolute));
    brushPattern.add(BrushPoint(-1, 1, 0.7285533905932738, PointType::Absolute));
    brushPattern.add(BrushPoint( 0, 1, 0.8535533905932738, PointType::Absolute));
    brushPattern.add(BrushPoint( 1, 1, 0.728553390593274, PointType::Absolute));
    brushPattern.add(BrushPoint( 2, 1, 0.42677669529663703, PointType::Absolute));
    brushPattern.add(BrushPoint( 3, 1, 0.12500000000000003, PointType::Absolute));
    brushPattern.add(BrushPoint( 4, 1, 0.0, PointType::Absolute));

    brushPattern.add(BrushPoint(-4, 2, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-3, 2, 0.07322330470336312, PointType::Absolute));
    brushPattern.add(BrushPoint(-2, 2, 0.25, PointType::Absolute));
    brushPattern.add(BrushPoint(-1, 2, 0.426776695296637, PointType::Absolute));
    brushPattern.add(BrushPoint( 0, 2, 0.5000000000000001, PointType::Absolute));
    brushPattern.add(BrushPoint( 1, 2, 0.42677669529663703, PointType::Absolute));
    brushPattern.add(BrushPoint( 2, 2, 0.2500000000000001, PointType::Absolute));
    brushPattern.add(BrushPoint( 3, 2, 0.07322330470336315, PointType::Absolute));
    brushPattern.add(BrushPoint( 4, 2, 0.0, PointType::Absolute));

    brushPattern.add(BrushPoint(-4, 3, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-3, 3, 0.021446609406726238, PointType::Absolute));
    brushPattern.add(BrushPoint(-2, 3, 0.07322330470336312, PointType::Absolute));
    brushPattern.add(BrushPoint(-1, 3, 0.12500000000000003, PointType::Absolute));
    brushPattern.add(BrushPoint( 0, 3, 0.14644660940672627, PointType::Absolute));
    brushPattern.add(BrushPoint( 1, 3, 0.12500000000000003, PointType::Absolute));
    brushPattern.add(BrushPoint( 2, 3, 0.07322330470336315, PointType::Absolute));
    brushPattern.add(BrushPoint( 3, 3, 0.02144660940672625, PointType::Absolute));
    brushPattern.add(BrushPoint( 4, 3, 0.0, PointType::Absolute));

    brushPattern.add(BrushPoint(-4, 4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-3, 4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-2, 4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint(-1, 4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint( 0, 4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint( 1, 4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint( 2, 4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint( 3, 4, 0.0, PointType::Absolute));
    brushPattern.add(BrushPoint( 4, 4, 0.0, PointType::Absolute));
    result.add(new PixelBrush(TRANS("Hann point"), brushPattern));

    return result;
}