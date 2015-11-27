//
//  GridPoint.h
//  DFMS2
//
//  Created by Trevor Knight on 11 Oct 15.
//
//

#ifndef GridPoint_h
#define GridPoint_h

struct GridPoint
{
    GridPoint() : x(0), y(0) {}
    GridPoint(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

#endif /* GridPoint_h */
