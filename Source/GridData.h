/*
 ==============================================================================
 
 GridData.h
 Created: 5 Jul 2015 7:08:44pm
 Author:  Trevor Knight
 
 ==============================================================================
 */

#ifndef GRIDDATA_H_INCLUDED
#define GRIDDATA_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "GridPoint.h"

class GridData
{
public:
    GridData(int gridWidth, int gridHeight)
        : data(gridWidth * gridHeight, true),
          gridWidth(gridWidth),
          gridHeight(gridHeight)
    {
        jassert(gridWidth > 0);
        jassert(gridHeight > 0);
    }

    void clear() { data.clear(gridWidth * gridHeight); }
    int getWidth() const { return gridWidth; }
    int getHeight() const { return gridHeight; }
    float getXY(int x, int y) const
    {
        jassert(x >=  0 && x < gridWidth);
        jassert(y >= 0 && y < gridHeight);
        return data.getData()[PointToLinear(x, y)];
    }
    float operator[](GridPoint p) const
    {
        jassert(p.x >=  0 && p.x < gridWidth);
        jassert(p.y >= 0 && p.y < gridHeight);
        return data.getData()[PointToLinear(p)];
    }
    float& operator[](GridPoint p)
    {
        jassert(p.x >=  0 && p.x < gridWidth);
        jassert(p.y >= 0 && p.y < gridHeight);
        return data.getData()[PointToLinear(p)];
    }
    
private:
    inline int PointToLinear(GridPoint p) const { return p.x * gridHeight + p.y; }
    inline int PointToLinear(int x, int y ) const { return x * gridHeight + y; }
    
    HeapBlock<float> data;
    int gridWidth;
    int gridHeight;

    static constexpr float minValue_ = 0.0f;
    static constexpr float maxValue_ = 1.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GridData)
};

#endif // GRIDDATA_H_INCLUDED
