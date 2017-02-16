#ifndef GRIDDATA_H_INCLUDED
#define GRIDDATA_H_INCLUDED

#include "JuceHeader.h"

#include "GridPoint.h"

class GridData
{
 public:
  GridData(int gridWidth, int gridHeight);
  GridData(const GridData& other) = default;
  GridData(GridData&& other) = default;
  GridData& operator=(const GridData& other) = default;
  GridData& operator=(GridData&& other) = default;

  void zero();
  void resize(int newWidth, int newHeight);
  int getWidth() const;
  int getHeight() const;

  float getXY(int x, int y) const;

  float operator[](GridPoint p) const;

  float& operator[](GridPoint p);

  Result writeToStream(OutputStream* stream);
  Result readFromStream(InputStream* stream);

 private:
  Array<float> data_;
  int gridWidth_;
  int gridHeight_;

  static constexpr float minValue_ = 0.0f;
  static constexpr float maxValue_ = 1.0f;

  JUCE_LEAK_DETECTOR(GridData);
};

#endif  // GRIDDATA_H_INCLUDED
