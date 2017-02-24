#ifndef STROKEPOINT_H_INCLUDED
#define STROKEPOINT_H_INCLUDED

#include "../GridData/GridPoint.h"

struct StrokePoint
{
  StrokePoint() : gridPoint(0, 0), pressure(0) {}

  StrokePoint(int x, int y, float pressure) : gridPoint(x, y), pressure(pressure) {}

  StrokePoint(GridPoint gridPoint, float pressure) : gridPoint(gridPoint), pressure(pressure) {}

  GridPoint gridPoint;
  float pressure;
};

#endif  // STROKEPOINT_H_INCLUDED