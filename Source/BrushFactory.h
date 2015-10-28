/*
  ==============================================================================

    BrushFactory.h
    Created: 28 Oct 2015 1:16:54pm
    Author:  Trevor Knight

  ==============================================================================
*/

#ifndef BRUSHFACTORY_H_INCLUDED
#define BRUSHFACTORY_H_INCLUDED

#include "JuceHeader.h"

#include "PixelBrush.h"

class BrushFactory
{
public:
    static OwnedArray<PixelBrush> getAllBrushes();
};


#endif  // BRUSHFACTORY_H_INCLUDED
