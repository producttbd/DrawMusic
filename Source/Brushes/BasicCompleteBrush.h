#ifndef BASICCOMPLETEBRUSH_H_INCLUDED
#define BASICCOMPLETEBRUSH_H_INCLUDED

#include "JuceHeader.h"

#include "AbstractBrushAction.h"
#include "AbstractBrushControls.h"
#include "AbstractCompleteBrush.h"

class BasicCompleteBrush : public AbstractCompleteBrush
{
 public:
  BasicCompleteBrush(String name, ScopedPointer<AbstractBrushAction> action,
                     ScopedPointer<AbstractBrushControls> controls);

  String getName() const override;
  AbstractBrushAction* getBrushAction() const override;
  AbstractBrushControls* getBrushControls() const override;

 private:
  const String name_;
  ScopedPointer<AbstractBrushAction> action_;
  ScopedPointer<AbstractBrushControls> controls_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BasicCompleteBrush);
};

#endif  // BASICCOMPLETEBRUSH_H_INCLUDED