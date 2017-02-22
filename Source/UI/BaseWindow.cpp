#include "BaseWindow.h"

#include "Configuration.h"
#include "DrawMusicLookAndFeel.h"
#include "WindowBoundsManager.h"

BaseWindow::BaseWindow(String name)
    : DocumentWindow(name, DrawMusicLookAndFeel::getDefaultBackgroundColour(),
                     DocumentWindow::closeButton)
{
  setResizable(true, true);
  auto bounds = WindowBoundsManager::getBounds(name);
  if (bounds.getWidth() == 0 || bounds.getHeight() == 0)
  {
    centreWithSize(Configuration::getNewWindowWidth(), Configuration::getNewWindowHeight());
  }
  else
  {
    setBounds(bounds);
  }

  setUsingNativeTitleBar(true);
  setVisible(true);
}

BaseWindow::~BaseWindow()
{
}

void BaseWindow::closeButtonPressed()
{
  WindowBoundsManager::saveBounds(getName(), getBounds());
  delete this;
}
