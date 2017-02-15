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
  currentControls_ = brushCollection_.getCurrentBrush()->getBrushControls();
  addAndMakeVisible(currentControls_);
}

void BrushPaletteWindowContent::controlChanged(AbstractBrushControls::ControlSpec spec)
{
  repaint();
}

void BrushPaletteWindowContent::buttonClicked(Button* button)
{
  // Deselect current brush
  sidePreviewButtons_[brushCollection_.getCurrentBrushIndex()]->setToggleState(
      false, NotificationType::dontSendNotification);

  // Hide current controls
  currentControls_->setVisible(false);

  // Find the selected brush
  const auto name = button->getName();
  for (int i = 0; i < brushCollection_.size(); ++i)
  {
    if (brushCollection_.getBrush(i)->getName() == name)
    {
      brushCollection_.setCurrentBrush(i);
      button->setToggleState(true, NotificationType::dontSendNotification);
    }
  }

  // Add the controls
  currentControls_ = brushCollection_.getCurrentBrush()->getBrushControls();
  currentControls_->setBounds(controlsArea_);
  currentControls_->addListener(this);
  addAndMakeVisible(currentControls_);

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

  g.drawText(currentCompleteBrush->getName(), mainPreviewArea_.getX() + margin,
             mainPreviewArea_.getY() + margin, mainPreviewArea_.getWidth() - 2 * margin, 40,
             Justification::topLeft);
  DFMSLookAndFeel::drawOutline(g, mainPreviewArea_);
  g.restoreState();

  // Controls
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
    sidePreviewButtons_[i]->setBounds(smallPreviewX, margin + i * (margin + smallPreviewSide),
                                      smallPreviewSide, smallPreviewSide);
  }

  currentControls_->setBounds(controlsArea_);
}