#ifndef GRIDDATA_H_INCLUDED
#define GRIDDATA_H_INCLUDED

#include "JuceHeader.h"

#include "GridPoint.h"

class GridData
{
 public:
  GridData(int gridWidth, int gridHeight);
  GridData(GridData&& other) = default;
  GridData& operator=(GridData&& other) = default;

  GridData getCopy();

  void zero();
  void resize(int newWidth, int newHeight);
  int getWidth() const;
  int getHeight() const;

  float getXY(int x, int y) const;

  float operator[](GridPoint p) const;

  float& operator[](GridPoint p);

 private:
  Array<float> data_;
  int gridWidth_;
  int gridHeight_;

  static constexpr float minValue_ = 0.0f;
  static constexpr float maxValue_ = 1.0f;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GridData);
};

#endif  // GRIDDATA_H_INCLUDED
