#ifndef GRIDIMAGERENDERER_H_INCLUDED
#define GRIDIMAGERENDERER_H_INCLUDED

#include "JuceHeader.h"

#include "GridColourScheme.h"
#include "GridData.h"

class GridImageRenderer
{
public:
    explicit GridImageRenderer(const GridColourScheme& colourScheme);

    void renderGridDataToImage(const GridData& gridData, Image& image);
    void renderSelectPointsToImage(const GridData& gridData, const Array<GridPoint>& points, Image& image);

private:
    const GridColourScheme& colourScheme_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GridImageRenderer);
};

#endif // GRIDIMAGERENDERER_H_INCLUDED
