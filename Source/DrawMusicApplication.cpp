#include "DrawMusicApplication.h"

DrawMusicApplication::DrawMusicApplication()
{
}

ApplicationCommandManager* DrawMusicApplication::getCommandManager()
{
  DrawMusicApplication* const app =
      dynamic_cast<DrawMusicApplication*>(JUCEApplication::getInstance());
  jassert(app != nullptr);
  ApplicationCommandManager* cm = app->commandManager;
  jassert(cm != nullptr);
  return cm;
}

void DrawMusicApplication::initialise(const String& commandLine)
{
  initCommandManager();
  // This method is where you should put your application's initialisation code..
  lookAndFeel = new DrawMusicLookAndFeel;
  LookAndFeel::setDefaultLookAndFeel(lookAndFeel);
  mainWindow = new MainWindow(getApplicationName());
}

void DrawMusicApplication::shutdown()
{
  // Add your application's shutdown code here..

  mainWindow = nullptr;
  lookAndFeel = nullptr;
  commandManager = nullptr;
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

void DrawMusicApplication::initCommandManager()
{
  commandManager = new ApplicationCommandManager;
  commandManager->registerAllCommandsForTarget(this);
}