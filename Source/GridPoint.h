#ifndef GridPoint_h
#define GridPoint_h

struct GridPoint
{
    GridPoint()
    : x(0), y(0) {}

    GridPoint(int x, int y)
    : x(x), y(y) {}

    bool operator==(const GridPoint& other)
    {
        return x == other.x && y == other.y;
    }
    
    int x;
    int y;
};

#endif /* GridPoint_h */
