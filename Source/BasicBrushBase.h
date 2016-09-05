#ifndef BasicBrushBase_H_INCLUDED
#define BasicBrushBase_H_INCLUDED

#include "JuceHeader.h"

#include "AbstractBrushAction.h"
#include "AbstractBrushControls.h"
#include "Configuration.h"
#include "GridData.h"
#include "StrokePoint.h"

class BasicBrushBase : public AbstractBrushAction
{
public:
    BasicBrushBase();
    virtual ~BasicBrushBase();

    virtual Array<AbstractBrushControls::ControlSpec> getSupportedControls();
    void controlChanged(AbstractBrushControls::ControlSpec spec) override;
    
    Array<GridPoint> startStroke(StrokePoint p, GridData& gridData) override;
    Array<GridPoint> continueStroke(StrokePoint p, GridData& gridData) override;
    Array<GridPoint> finishStroke(StrokePoint p, GridData& gridData) override;

protected:
    virtual void recreateBrush(AbstractBrushControls::ControlSpec specChanged);

    virtual Array<StrokePoint> getIntermediaryPoints(StrokePoint start, StrokePoint end) const;
    virtual Array<GridPoint> applyBrushToStroke(
        const Array<StrokePoint>& pointsInStroke,  GridData& gridData) const;
    virtual Array<GridPoint> applyBrushToPoint(StrokePoint p, GridData& gridData) const = 0;

    static inline float clampOutputValue(float value)
    {
        return jmax(jmin(value, Configuration::getMaxGridValue()), Configuration::getMinGridValue());
    }

    Array<AbstractBrushControls::ControlSpec> supportedControls_;
    HashMap<String, double*> controlWirings_;
    double intensityScalar_; // TODO Discrepancy between types in brush values and control values

    static constexpr float minIntensityScalar_ = 0.0f;
    static constexpr float maxIntensityScalar_ = 1.0f;

    Array<StrokePoint> pointsInStroke_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BasicBrushBase)
};

#endif  // BasicBrushBase_H_INCLUDED
