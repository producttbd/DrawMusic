#include "GridData.h"

namespace
{
inline int pointToLinear(GridPoint p, int gridHeight) { return p.x * gridHeight + p.y; }
inline int pointToLinear(int x, int y, int gridHeight) { return x * gridHeight + y; }
}

GridData::GridData(int gridWidth, int gridHeight)
    : data_(), gridWidth_(gridWidth), gridHeight_(gridHeight)
{
  data_.insertMultiple(0, 0.0f, gridWidth_ * gridHeight_);
  jassert(gridWidth_ > 0);
  jassert(gridHeight_ > 0);
}

void GridData::zero()
{
  for (auto& value : data_)
  {
    value = 0.0f;
  }
}

void GridData::resize(int newWidth, int newHeight)
{
  gridWidth_ = newWidth;
  gridHeight_ = newHeight;
  data_.clearQuick();
  data_.insertMultiple(0, 0.0f, gridWidth_ * gridHeight_);
}

int GridData::getWidth() const { return gridWidth_; }

int GridData::getHeight() const { return gridHeight_; }

float GridData::getXY(int x, int y) const
{
  jassert(x >= 0 && x < gridWidth_);
  jassert(y >= 0 && y < gridHeight_);
  return data_[pointToLinear(x, y, gridHeight_)];
}

float GridData::operator[](GridPoint p) const
{
  jassert(p.x >= 0 && p.x < gridWidth_);
  jassert(p.y >= 0 && p.y < gridHeight_);
  return data_[pointToLinear(p, gridHeight_)];
}

float& GridData::operator[](GridPoint p)
{
  jassert(p.x >= 0 && p.x < gridWidth_);
  jassert(p.y >= 0 && p.y < gridHeight_);
  return data_.getReference(pointToLinear(p, gridHeight_));
}
