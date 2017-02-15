#ifndef GRIDPOINT_H_INCLUDED
#define GRIDPOINT_H_INCLUDED

struct GridPoint
{
  GridPoint() : x(0), y(0) {}

  GridPoint(int x, int y) : x(x), y(y) {}

  bool operator==(const GridPoint& other) { return x == other.x && y == other.y; }

  int x;
  int y;
};

#endif  // GRIDPOINT_H_INCLUDED
