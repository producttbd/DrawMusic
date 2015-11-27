#include "GridColourScheme.h"

Colour GridColourScheme::convertToColour(float value) const
{
    return Colour::greyLevel(value);
}