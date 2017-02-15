#include "GridColourScheme.h"

Colour GridColourScheme::convertToColour(float value)
{
  return Colour::greyLevel(1.0f - value);
}