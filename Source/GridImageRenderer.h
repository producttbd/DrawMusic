/*
 ==============================================================================
 
 GridImageRenderer.h
 Created: 5 Jul 2015 7:08:44pm
 Author:  Trevor Knight
 
 ==============================================================================
*/


#ifndef GRIDIMAGERENDERER_H_INCLUDED
#define GRIDIMAGERENDERER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "GridColourScheme.h"
#include "GridData.h"

class GridImageRenderer
{
public:
    GridImageRenderer(const GridColourScheme& colourScheme);

    void renderGridDataToImage(const GridData& gridData, Image& image);
    void renderSelectPointsToImage(const GridData& gridData, const Array<GridPoint>& points, Image& image);

private:
    const GridColourScheme& colourScheme_;
};

#endif // GRIDIMAGERENDERER_H_INCLUDED
