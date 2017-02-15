#ifndef GRIDIMAGERENDERER_H_INCLUDED
#define GRIDIMAGERENDERER_H_INCLUDED

#include "JuceHeader.h"

#include "GridColourScheme.h"
#include "GridData.h"

class GridImageRenderer
{
 public:
  explicit GridImageRenderer(const GridData& gridData, const GridColourScheme& colourScheme);

  void renderGridDataToImage(Image& image);
  void renderSelectPointsToImage(const Array<GridPoint>& points, Image& image);

 private:
  const GridData& gridData_;
  const GridColourScheme& colourScheme_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GridImageRenderer);
};

#endif  // GRIDIMAGERENDERER_H_INCLUDED
