#ifndef BRUSHFACTORY_H_INCLUDED
#define BRUSHFACTORY_H_INCLUDED

#include "JuceHeader.h"

#include "PixelBrush.h"

class BrushFactory
{
public:
    static OwnedArray<PixelBrush> getAllBrushes();
    
    BrushFactory() = delete;
    BrushFactory(BrushFactory&) = delete;
    BrushFactory& operator=(BrushFactory&) = delete;
};


#endif  // BRUSHFACTORY_H_INCLUDED
