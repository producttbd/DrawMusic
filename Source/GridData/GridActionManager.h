#ifndef GRIDACTIONMANAGER_H_INCLUDED
#define GRIDACTIONMANAGER_H_INCLUDED

#include "JuceHeader.h"

#include "BrushPalette.h"
#include "GridData.h"

class GridActionManager : public ChangeBroadcaster
{
public:
    GridActionManager(const BrushPalette& brushPalette, GridData& gridData);

    void resize(int width, int height);
    void clearGrid();
    void mouseDown(const MouseEvent& event);
    void mouseDrag(const MouseEvent& event);
    void mouseUp(const MouseEvent& event);

private:
    const BrushPalette& brushPalette_;
    GridData& gridData_;
};

#endif  // GRIDACTIONMANAGER_H_INCLUDED
