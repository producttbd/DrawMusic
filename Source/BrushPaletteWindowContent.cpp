#include "BrushPaletteWindowContent.h"

#include "Configuration.h"
#include "DFMSLookAndFeel.h"

BrushPaletteWindowContent::BrushPaletteWindowContent(AbstractCompleteBrush** const brushes,
                                                     int numberBrushes, int* currentBrush)
: brushes_(brushes), numberBrushes_(numberBrushes), currentBrush_(currentBrush)
{
    jassert(brushes_ != nullptr);
    jassert(currentBrush_ != nullptr);
}

void BrushPaletteWindowContent::paint(Graphics& g)
{
    const int margin = Configuration::getGuiMargin();
    const int previewSide = 250;
    const int smallPreviewSide = 100;
    const int controlsHeight = 350;
    //setSize(3 * margin + previewSide + smallPreviewSide, 3 * margin + previewSide + controlsHeight);

    const AbstractCompleteBrush* currentCompleteBrush = brushes_[*currentBrush_];

    // Preview area
    g.saveState();
    const auto mainPreviewArea = Rectangle<int>(margin, margin, previewSide, previewSide);
    g.reduceClipRegion(mainPreviewArea);
    currentCompleteBrush->getBrushAction()->drawPreviewInto(g, mainPreviewArea);
    const Colour zeroColour = GridColourScheme::convertToColour(0.0f);
    g.setColour(zeroColour.contrasting());
    g.drawText(currentCompleteBrush->getName(), mainPreviewArea.getX(), mainPreviewArea.getY(),
               mainPreviewArea.getWidth(), 40, Justification::left);
    DFMSLookAndFeel::drawOutline(g, mainPreviewArea);
    g.restoreState();

    // Controls
    auto controls = currentCompleteBrush->getBrushControls();
    addAndMakeVisible(controls);
    auto controlBounds = Rectangle<int>(mainPreviewArea.getX(), margin + mainPreviewArea.getBottom(),
                                        mainPreviewArea.getWidth(), controlsHeight);
    controls->setBounds(controlBounds);
    DFMSLookAndFeel::drawOutline(g, controlBounds);

    // Other brushes
    const int smallPreviewX = 2 * margin + previewSide;
    for (int i = 0; i < numberBrushes_; ++i)
    {
        g.saveState();
        Rectangle<int> smallPreviewBounds(smallPreviewX, margin + i *(margin + smallPreviewSide),
                              smallPreviewSide, smallPreviewSide);
        g.reduceClipRegion(smallPreviewBounds);
        brushes_[i]->getBrushAction()->drawPreviewInto(g, smallPreviewBounds);
        DFMSLookAndFeel::drawOutline(g, smallPreviewBounds);
        g.restoreState();
    }
}


//void BrushPaletteWindowContent::resized()
//}