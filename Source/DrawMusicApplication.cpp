#include "DrawMusicApplication.h"

#include "CommandIds.h"

DrawMusicApplication::DrawMusicApplication()
{
}

DrawMusicApplication* DrawMusicApplication::getApp()
{
  DrawMusicApplication* const app =
      dynamic_cast<DrawMusicApplication*>(JUCEApplication::getInstance());
  jassert(app != nullptr);
  return app;
}

ApplicationCommandManager* DrawMusicApplication::getCommandManager()
{
  ApplicationCommandManager* cm = getApp()->commandManager;
  jassert(cm != nullptr);
  return cm;
}

void DrawMusicApplication::initialise(const String& commandLine)
{
  initCommandManager();
  menuModel = new MainMenuModel;
  lookAndFeel = new DrawMusicLookAndFeel;
  LookAndFeel::setDefaultLookAndFeel(lookAndFeel);
  mainWindow = new MainWindow(getApplicationName());

#if JUCE_MAC
  MenuBarModel::setMacMainMenu(menuModel);
#endif
}

void DrawMusicApplication::shutdown()
{
  mainWindow = nullptr;
#if JUCE_MAC
  MenuBarModel::setMacMainMenu(nullptr);
#endif
  menuModel = nullptr;
  commandManager = nullptr;

  LookAndFeel::setDefaultLookAndFeel(nullptr);
}

void DrawMusicApplication::systemRequestedQuit()
{
  // This is called when the app is being asked to quit: you can ignore this
  // request and let the app carry on running, or call quit() to allow the app to close.
  quit();
}

void DrawMusicApplication::anotherInstanceStarted(const String& commandLine)
{
  // When another instance of the app is launched while this one is running,
  // this method is invoked, and the commandLine parameter tells you what
  // the other instance's command-line arguments were.
}

MenuBarModel* DrawMusicApplication::getMenuModel()
{
  return menuModel.get();
}

StringArray DrawMusicApplication::getMenuNames()
{
  const String names[] = {TRANS("File"), TRANS("Edit"), TRANS("Canvas")};
  return StringArray(names, 3);
}

void DrawMusicApplication::createMenu(PopupMenu& menu, int menuIndex)
{
  if (menuIndex == 0 /* "File" */)
    createFileMenu(menu);
  else if (menuIndex == 1 /* "Edit" */)
    createEditMenu(menu);
  else if (menuIndex == 2 /* "Canvas" */)
    createCanvasMenu(menu);
  else
    jassertfalse;  // names have changed?
}

void DrawMusicApplication::createFileMenu(PopupMenu& menu)
{
  menu.addCommandItem(commandManager, DrawMusicCommandID::newDrawing);
  menu.addSeparator();
  menu.addCommandItem(commandManager, DrawMusicCommandID::open);
  menu.addSeparator();
  menu.addCommandItem(commandManager, DrawMusicCommandID::saveDrawing);
  menu.addCommandItem(commandManager, DrawMusicCommandID::saveDrawingAs);
  menu.addSeparator();
  menu.addCommandItem(commandManager, DrawMusicCommandID::exportAudio);
  menu.addSeparator();
  menu.addCommandItem(commandManager, DrawMusicCommandID::openSettings);
  menu.addSeparator();
#if !JUCE_MAC
  menu.addCommandItem(commandManager, CommandIDs::showGlobalPreferences);
  menu.addSeparator();
  menu.addCommandItem(commandManager, StandardApplicationCommandIDs::quit);
#endif
}

void DrawMusicApplication::createEditMenu(PopupMenu& menu)
{
  menu.addCommandItem(commandManager, StandardApplicationCommandIDs::undo);
  menu.addCommandItem(commandManager, StandardApplicationCommandIDs::redo);
}

void DrawMusicApplication::createCanvasMenu(PopupMenu& menu)
{
  menu.addCommandItem(commandManager, StandardApplicationCommandIDs::del);
  menu.addSeparator();
  menu.addCommandItem(commandManager, DrawMusicCommandID::gridSmaller);
  menu.addCommandItem(commandManager, DrawMusicCommandID::gridLarger);
}

void DrawMusicApplication::initCommandManager()
{
  commandManager = new ApplicationCommandManager;
  commandManager->registerAllCommandsForTarget(this);
}