/*
  ==============================================================================

    GridColorScheme.cpp
    Created: 28 Oct 2015 1:17:29pm
    Author:  Trevor Knight

  ==============================================================================
*/

#include "GridColourScheme.h"

Colour GridColourScheme::convertToColour(float value) const
{
    return Colour::greyLevel(value);
}