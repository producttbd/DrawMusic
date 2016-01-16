#include "BrushFactory.h"

using BrushPoint = PixelBrush::BrushPoint;
using PointType = PixelBrush::PointType;

OwnedArray<PixelBrush> BrushFactory::getAllBrushes()
{
    OwnedArray<PixelBrush> result;
    Array<BrushPoint> brushPattern;

    // Square brush
//    brushPattern.add(BrushPoint(-1, -1, 0.2, PointType::Additive));
//    brushPattern.add(BrushPoint(-1, 0, 0.2, PointType::Additive));
//    brushPattern.add(BrushPoint(-1, 1, 0.2, PointType::Additive));
//    brushPattern.add(BrushPoint(0, 1, 0.2, PointType::Additive));
//    brushPattern.add(BrushPoint(1, 1, 0.2, PointType::Additive));
//    brushPattern.add(BrushPoint(1, 0, 0.2, PointType::Additive));
//    brushPattern.add(BrushPoint(1, -1, 0.2, PointType::Additive));
//    brushPattern.add(BrushPoint(0, -1, 0.2, PointType::Additive));
    brushPattern.add(BrushPoint(0, 0, 1.0, PointType::Additive));
    result.add(new PointClusterBrush(TRANS("Square brush"), brushPattern));

    // Hann brush
    Array<float> hannProfile({0.1464466094067262f, 0.49999999999999994f, 0.8535533905932737f,
        1.0f, 0.8535533905932738f, 0.5000000000000001f, 0.14644660940672627f});
    result.add(new XYProfileBrush(TRANS("Hann point"), hannProfile, hannProfile, -3, -3));

    // Percussion
    Array<float> xPercussive({0.65f,
        1.0f, 0.8535533905932738f, 0.5000000000000001f, 0.14644660940672627f});
    Array<float> yPercussive;
    for (float i = 250.0f; i > 0.0f; i -= 1.0f)
    {
        yPercussive.add(i / 500.0f);
    }
    result.add(new XYProfileBrush(TRANS("Percussion"), xPercussive, yPercussive, -1, 0));

    // noise cluster
    brushPattern.clear();
    Random random;
    for (int x = -40; x <= 40; ++x)
    {
        for (int y = -40; y <= 40; ++y)
        {
            brushPattern.add(BrushPoint(x, y, random.nextFloat()*0.1f, PointType::Absolute));
        }
    }
    result.add(new PointClusterBrush(TRANS("Noise brush"), brushPattern));

    return result;
}