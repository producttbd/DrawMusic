#include "GridColourScheme.h"

Colour GridColourScheme::convertToColour(float value) const
{
    return Colour::greyLevel(1.0-value);  // Drawing Canvas background color
}
