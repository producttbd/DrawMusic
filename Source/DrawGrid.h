#ifndef DRAWGRID_H_INCLUDED
#define DRAWGRID_H_INCLUDED

#include "JuceHeader.h"

#include "BrushPalette.h"
#include "GridColourScheme.h"
#include "GridData.h"
#include "GridImageRenderer.h"

class DrawGrid : public Component,
                 public ChangeBroadcaster
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
