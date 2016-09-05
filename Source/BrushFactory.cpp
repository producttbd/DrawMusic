#include "BrushFactory.h"

#include "AbstractCompleteBrush.h"
#include "AbstractBrushControls.h"
#include "BasicBrushControls.h"
#include "BasicCompleteBrush.h"
#include "BasicBrushBase.h"
#include "CombBrush.h"
#include "EraserBrush.h"
#include "NoiseBrush.h"
#include "PointClusterBrush.h"
#include "XYProfileBrush.h"

using BrushPoint = PointClusterBrush::BrushPoint;
using PointType = PointClusterBrush::PointType;

void BrushFactory::getAllBrushes(BrushCollection& brushCollection)
{
    // Single dot brush
    Array<BrushPoint> brushPattern;
    brushPattern.add(BrushPoint(0, 0, 1.0, PointType::Additive));
    BasicBrushBase* action = new PointClusterBrush(brushPattern);
    BasicBrushControls* control = new BasicBrushControls();
    control->addControls(action->getSupportedControls());
    brushCollection.add(new BasicCompleteBrush(TRANS("Single dot brush"), action, control));

    // Hann brush
    Array<float> hannProfile({0.1464466094067262f, 0.49999999999999994f, 0.8535533905932737f,
        1.0f, 0.8535533905932738f, 0.5000000000000001f, 0.14644660940672627f});
    action = new XYProfileBrush(hannProfile, hannProfile, -3, -3);
    control = new BasicBrushControls();
    control->addControls(action->getSupportedControls());
    brushCollection.add(new BasicCompleteBrush(TRANS("Hann point"), action, control));

    // Percussion
    Array<float> xPercussive({1.0f, 0.8535533905932738f, 0.5000000000000001f, 0.14644660940672627f});
    Array<float> yPercussive;
    for (float i = 800.0f; i > 0.0f; i -= 1.0f)
    {
        yPercussive.add(i / 800.0f);
    }
    action = new XYProfileBrush(xPercussive, yPercussive, -1, 0);
    control = new BasicBrushControls();
    control->addControls(action->getSupportedControls());
    brushCollection.add(new BasicCompleteBrush(TRANS("Percussive"), action, control));

    // new noise brush
    action = new NoiseBrush();
    control = new BasicBrushControls();
    control->addControls(action->getSupportedControls());
    brushCollection.add(new BasicCompleteBrush(TRANS("Noise Brush"), action, control));

    // Comb brush
    action = new CombBrush();
    control = new BasicBrushControls();
    control->addControls(action->getSupportedControls());
    brushCollection.add(new BasicCompleteBrush(TRANS("Comb brush"), action, control));

    // Eraser brush
    action = new EraserBrush();
    control = new BasicBrushControls();
    control->addControls(action->getSupportedControls());
    brushCollection.add(new BasicCompleteBrush(TRANS("Eraser brush"), action, control));
}