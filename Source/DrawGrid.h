/*
  ==============================================================================

    DrawGrid.h
    Created: 3 Jul 2015 10:34:23pm
    Author:  Trevor Knight

  ==============================================================================
*/

#ifndef DRAWGRID_H_INCLUDED
#define DRAWGRID_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "BrushPalette.h"
#include "GridColourScheme.h"
#include "GridData.h"
#include "GridImageRenderer.h"
#include "PixelBrush.h"

class DrawGrid : public Component
{
public:
    DrawGrid(GridData& gridData,
             const GridColourScheme& colourScheme,
             const BrushPalette& brushPalette);
    ~DrawGrid();

    void refreshAll();
    void paint (Graphics&) override;
    void resized() override;
    
    void mouseDown(const MouseEvent& event) override;
    void mouseDrag(const MouseEvent& event) override;
    void mouseUp(const MouseEvent& event) override;

private:
    GridData& gridData_;
    const BrushPalette& brushPalette_;
    const GridColourScheme& colourScheme_;
    Image theImage_;
    GridImageRenderer gridImageRenderer_;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrawGrid)
};


#endif  // DRAWGRID_H_INCLUDED
