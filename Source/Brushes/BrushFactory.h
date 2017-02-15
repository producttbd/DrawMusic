#ifndef BRUSHFACTORY_H_INCLUDED
#define BRUSHFACTORY_H_INCLUDED

#include "JuceHeader.h"

#include "BrushCollection.h"

class BrushFactory
{
 public:
  static void getAllBrushes(BrushCollection& brushCollection);

  BrushFactory() = delete;
  BrushFactory(BrushFactory&) = delete;
  BrushFactory& operator=(BrushFactory&) = delete;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BrushFactory);
};

#endif  // BRUSHFACTORY_H_INCLUDED
