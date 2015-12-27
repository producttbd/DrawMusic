#ifndef GRIDDATA_H_INCLUDED
#define GRIDDATA_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "GridPoint.h"

class GridData
{
public:
    GridData(int gridWidth, int gridHeight)
        : data_(gridWidth * gridHeight, true),
          gridWidth_(gridWidth),
          gridHeight_(gridHeight)
    {
        jassert(gridWidth_ > 0);
        jassert(gridHeight_ > 0);
    }

    void clear() { data_.clear(gridWidth_ * gridHeight_); }
    int getWidth() const { return gridWidth_; }
    int getHeight() const { return gridHeight_; }
    
    float getXY(int x, int y) const
    {
        jassert(x >=  0 && x < gridWidth_);
        jassert(y >= 0 && y < gridHeight_);
        return data_.getData()[PointToLinear(x, y)];
    }
    
    float operator[](GridPoint p) const
    {
        jassert(p.x >=  0 && p.x < gridWidth_);
        jassert(p.y >= 0 && p.y < gridHeight_);
        return data_.getData()[PointToLinear(p)];
    }
    
    float& operator[](GridPoint p)
    {
        jassert(p.x >=  0 && p.x < gridWidth_);
        jassert(p.y >= 0 && p.y < gridHeight_);
        return data_.getData()[PointToLinear(p)];
    }
    
private:
    inline int PointToLinear(GridPoint p) const { return p.x * gridHeight_ + p.y; }
    inline int PointToLinear(int x, int y ) const { return x * gridHeight_ + y; }
    
    HeapBlock<float> data_;
    int gridWidth_;
    int gridHeight_;

    static constexpr float minValue_ = 0.0f;
    static constexpr float maxValue_ = 1.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GridData)
};

#endif // GRIDDATA_H_INCLUDED
