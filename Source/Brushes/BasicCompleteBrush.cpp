#include "BasicCompleteBrush.h"

BasicCompleteBrush::BasicCompleteBrush(const String name, ScopedPointer<AbstractBrushAction> action,
                                       ScopedPointer<AbstractBrushControls> controls)
    : name_(name), action_(action), controls_(controls)
{
  controls_->addListener(action_);
}

String BasicCompleteBrush::getName() const { return name_; }

AbstractBrushControls* BasicCompleteBrush::getBrushControls() const { return controls_.get(); }

AbstractBrushAction* BasicCompleteBrush::getBrushAction() const { return action_.get(); }
