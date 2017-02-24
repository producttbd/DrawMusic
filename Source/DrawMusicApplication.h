#ifndef DRAWMUSICAPPLICATION_H_INCLUDED
#define DRAWMUSICAPPLICATION_H_INCLUDED

#include "JuceHeader.h"

#include "MainComponent.h"
#include "UI/DrawMusicLookAndFeel.h"

class DrawMusicApplication : public JUCEApplication
{
 public:
  DrawMusicApplication();

  static ApplicationCommandManager* getCommandManager();
  static DrawMusicApplication* getApp();

  const String getApplicationName() override { return ProjectInfo::projectName; }
  const String getApplicationVersion() override { return ProjectInfo::versionString; }
  bool moreThanOneInstanceAllowed() override { return false; }

  void initialise(const String& commandLine) override;
  void shutdown() override;
  void systemRequestedQuit() override;
  void anotherInstanceStarted(const String& commandLine) override;

  MenuBarModel* getMenuModel();
  StringArray getMenuNames();
  void createMenu(PopupMenu& menu, int menuIndex);
  void createFileMenu(PopupMenu& menu);
  void createEditMenu(PopupMenu& menu);
  void createCanvasMenu(PopupMenu& menu);

  class MainWindow : public DocumentWindow
  {
   public:
    MainWindow(String name) : DocumentWindow(name, Colours::lightgrey, DocumentWindow::allButtons)
    {
      setUsingNativeTitleBar(true);
      setResizable(false, false);
      setContentOwned(new MainComponent(), true);

      centreWithSize(getWidth(), getHeight());
      setVisible(true);
#if !JUCE_MAC
      setMenuBar(DrawMusicApplication::getApp()->getMenuModel());
#endif
      addKeyListener(DrawMusicApplication::getCommandManager()->getKeyMappings());
    }

    ~MainWindow() {}

    void closeButtonPressed() override
    {
      // This is called when the user tries to close this window. Here, we'll just
      // ask the app to quit when this happens, but you can change this to do
      // whatever you need.
      JUCEApplication::getInstance()->systemRequestedQuit();
    }

    /* Note: Be careful if you override any DocumentWindow methods - the base
     class uses a lot of them, so by overriding you might break its functionality.
     It's best to do all your work in your content component instead, but if
     you really have to override any DocumentWindow methods, make sure your
     subclass also calls the superclass's method.
     */

   private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
  };

 private:
  void initCommandManager();

  class MainMenuModel : public MenuBarModel
  {
   public:
    MainMenuModel() { setApplicationCommandManagerToWatch(getCommandManager()); }

    StringArray getMenuBarNames() override { return getApp()->getMenuNames(); }

    PopupMenu getMenuForIndex(int topLevelMenuIndex, const String& /* menuName */) override
    {
      PopupMenu menu;
      getApp()->createMenu(menu, topLevelMenuIndex);
      return menu;
    }

    void menuItemSelected(int menuItemID, int /*topLevelMenuIndex*/) override {}
  };
  ScopedPointer<MainMenuModel> menuModel = nullptr;
  ScopedPointer<MainWindow> mainWindow = nullptr;
  ScopedPointer<LookAndFeel> lookAndFeel = nullptr;
  ScopedPointer<ApplicationCommandManager> commandManager = nullptr;
};

#endif  // DRAWMUSICAPPLICATION_H_INCLUDED
