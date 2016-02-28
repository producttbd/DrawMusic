#include "BrushPaletteWindowContent.h"

#include "Configuration.h"
#include "DFMSLookAndFeel.h"

BrushPaletteWindowContent::BrushPaletteWindowContent(BrushCollection& brushCollection)
: brushCollection_(brushCollection)
{
    int currentBrush = brushCollection_.getCurrentBrushIndex();
    for (int i = 0; i < brushCollection_.size(); ++i)
    {
        BrushPreviewButton* button = new BrushPreviewButton(brushCollection_.getBrush(i));
        button->addListener(this);
        addAndMakeVisible(button);
        if (i == currentBrush)
        {
            button->setToggleState(true, NotificationType::dontSendNotification);
        }
        sidePreviewButtons_.add(button);
    }
}

void BrushPaletteWindowContent::buttonClicked(Button* button)
{
    const auto name = button->getName();
    for (int i = 0; i < sidePreviewButtons_.size(); ++i)
    {
        sidePreviewButtons_[i]->setToggleState(false, NotificationType::dontSendNotification);
    }
    for (int i = 0; i < brushCollection_.size(); ++i)
    {
        if (brushCollection_.getBrush(i)->getName() == name)
        {
            brushCollection_.setCurrentBrush(i);
            button->setToggleState(true, NotificationType::dontSendNotification);
        }
    }
    repaint();
}

void BrushPaletteWindowContent::paint(Graphics& g)
{
    
    const int margin = Configuration::getGuiMargin();
    const AbstractCompleteBrush* currentCompleteBrush = brushCollection_.getCurrentBrush();

    // Preview area
    g.saveState();
    g.reduceClipRegion(mainPreviewArea_);
    currentCompleteBrush->getBrushAction()->drawPreviewInto(g, mainPreviewArea_);
    const Colour zeroColour = GridColourScheme::convertToColour(0.0f);
    g.setColour(zeroColour.contrasting());
    
    g.drawText(currentCompleteBrush->getName(),
               mainPreviewArea_.getX() + margin, mainPreviewArea_.getY() + margin,
               mainPreviewArea_.getWidth() - 2 * margin, 40, Justification::topLeft);
    DFMSLookAndFeel::drawOutline(g, mainPreviewArea_);
    g.restoreState();

    // Controls
    auto controls = currentCompleteBrush->getBrushControls();
    addAndMakeVisible(controls);

    controls->setBounds(controlsArea_);
    DFMSLookAndFeel::drawOutline(g, controlsArea_);
}

void BrushPaletteWindowContent::resized()
{
    const int smallPreviewSide = 100;
    const int margin = Configuration::getGuiMargin();
    const int previewAreaSide = getWidth() - 3 * margin - smallPreviewSide;
    const int controlsHeight = getHeight() - 3 * margin - previewAreaSide;
    
    mainPreviewArea_ = Rectangle<int>(margin, margin, previewAreaSide, previewAreaSide);
    controlsArea_ = Rectangle<int>(margin, margin + mainPreviewArea_.getBottom(),
                                   mainPreviewArea_.getWidth(), controlsHeight);
    
    const int smallPreviewX = 2 * margin + previewAreaSide;
    for (int i = 0; i < sidePreviewButtons_.size(); ++i)
    {
        sidePreviewButtons_[i]->setBounds(smallPreviewX, margin + i *(margin + smallPreviewSide),
                                          smallPreviewSide, smallPreviewSide);
    }
}