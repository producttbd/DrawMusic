#include "MainComponent.h"

#include "Brushes/BrushPaletteWindow.h"
#include "CommandIds.h"
#include "Configuration.h"
#include "DrawMusicApplication.h"
#include "GridData/GridDataChangedNotifier.h"
#include "UI/DrawMusicLookAndFeel.h"

MainComponent::MainComponent()
    : gridData_(Configuration::getGridWidth(), Configuration::getGridHeight()),
      brushPalette_("brushPalette", gridColourScheme_),
      gridDataChangedNotifier_(),
      gridActionManager_(brushPalette_, gridData_, gridDataChangedNotifier_),
      gridColourScheme_(),
      drawGrid_(gridActionManager_, gridData_, gridColourScheme_),
      audioDataChangedNotifier_(),
      audioSystem_(gridData_, audioDataChangedNotifier_),
      playbackTimeline_("playbackTimeline"),
      playbackTimer_(playbackTimeline_),
      waveformView_("waveform view"),
      playStopButton_("playStopButton"),
      undoButton_("undoButton"),
      redoButton_("redoButton"),
      allButtons_({&playStopButton_, &undoButton_, &redoButton_})
{
  auto commandManager = DrawMusicApplication::getCommandManager();

  // Buttons
  playStopButton_.setButtonText(TRANS("play"));
  playStopButton_.setConnectedEdges(Button::ConnectedOnRight);
  playStopButton_.setCommandToTrigger(commandManager, DrawMusicCommandID::play_pause,
                                      true /* generateToolTip */);

  undoButton_.setButtonText(TRANS("undo"));
  undoButton_.setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
  undoButton_.setCommandToTrigger(commandManager, StandardApplicationCommandIDs::undo, true);

  redoButton_.setButtonText(TRANS("redo"));
  redoButton_.setConnectedEdges(Button::ConnectedOnLeft);
  redoButton_.setCommandToTrigger(commandManager, StandardApplicationCommandIDs::redo, true);

  DrawMusicApplication::getCommandManager()->registerAllCommandsForTarget(this);

  for (Button* button : allButtons_)
  {
    addAndMakeVisible(button);
  }

  // Non-buttons UI
  addAndMakeVisible(&brushPalette_);
  addAndMakeVisible(&waveformView_);
  addAndMakeVisible(drawGrid_);
  addAndMakeVisible(&playbackTimeline_);

  // The WavefromView should know when new audio is available to redraw and the timeline should know
  // when the current position has changed.
  audioDataChangedNotifier_.addNewAudioListener(&waveformView_);
  audioDataChangedNotifier_.addNewPositionListener(&playbackTimeline_);

  // The actual UI Component, DrawGrid, should know when the underlying data is changed or resized.
  gridDataChangedNotifier_.addGridDataResizedListener(&drawGrid_);
  gridDataChangedNotifier_.addGridDataUpdatedListener(&drawGrid_);

  // The AudioSystem should know when new data is available for turning into sound.
  gridDataChangedNotifier_.addGridDataResizedListener(&audioSystem_);
  gridDataChangedNotifier_.addGridDataUpdatedListener(&audioSystem_);

  // Finally set size
  setSize(Configuration::getMainWindowWidth(), Configuration::getMainWindowHeight());
}

MainComponent::~MainComponent()
{
}

// ===== Component overrides =====

void MainComponent::paint(Graphics& g)
{
  g.fillAll(DrawMusicLookAndFeel::getDefaultBackgroundColour());
}

void MainComponent::resized()
{
  const int gridWidth = Configuration::getGridWidth();
  const int gridHeight = Configuration::getGridHeight();

  const int outsideMargin = Configuration::getGuiMargin();
  drawGrid_.setBounds(outsideMargin, outsideMargin, gridWidth, gridHeight);

  waveformView_.setBounds(outsideMargin, 2 * outsideMargin + gridHeight, gridWidth,
                          Configuration::getWaveformViewHeight());

  playbackTimeline_.setBounds(outsideMargin, outsideMargin, gridWidth,
                              gridHeight + outsideMargin + Configuration::getWaveformViewHeight());
  auto clickBoundsForWaveformView = playbackTimeline_.getLocalArea(this, waveformView_.getBounds());
  playbackTimeline_.setToControlAudioSystem(clickBoundsForWaveformView, &audioSystem_);

  const int buttonWidth = Configuration::getButtonWidth();
  const int buttonHeight = Configuration::getButtonHeight();
  const int buttonY = getHeight() - buttonHeight - outsideMargin;

  int buttonNum = 0;
  for (Button* button : allButtons_)
  {
    button->setBounds(outsideMargin + buttonNum * buttonWidth, buttonY, buttonWidth, buttonHeight);
    ++buttonNum;
  }

  const int paletteSide = Configuration::getPaletteSide();
  brushPalette_.setBounds(getWidth() - paletteSide - outsideMargin,
                          getHeight() - paletteSide - outsideMargin, paletteSide, paletteSide);
}

// ===== ApplicationCommandTarget overrides =====
ApplicationCommandTarget* MainComponent::getNextCommandTarget()
{
  // To keep things simple, this is the only ApplicationCommandTarget in DrawMusic code.
  return nullptr;
}

void MainComponent::getAllCommands(Array<CommandID>& commands)
{
  const CommandID ids[] = {DrawMusicCommandID::newDrawing,      DrawMusicCommandID::open,
                           DrawMusicCommandID::saveDrawing,     DrawMusicCommandID::saveDrawingAs,
                           DrawMusicCommandID::exportAudio,     DrawMusicCommandID::openSettings,
                           DrawMusicCommandID::play_pause,      StandardApplicationCommandIDs::undo,
                           StandardApplicationCommandIDs::redo, StandardApplicationCommandIDs::del,
                           DrawMusicCommandID::gridSmaller,     DrawMusicCommandID::gridLarger};
  commands.addArray(ids, numElementsInArray(ids));
}

void MainComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
  switch (commandID)
  {
    case DrawMusicCommandID::newDrawing:
      result.setInfo(TRANS("New"), TRANS("Creates a new drawing"), CommandCategories::general, 0);
      result.addDefaultKeypress('n', ModifierKeys::commandModifier);
      break;

    case DrawMusicCommandID::open:
      result.setInfo(TRANS("Open"), TRANS("Opens a previously saved drawing"),
                     CommandCategories::general, 0);
      result.addDefaultKeypress('o', ModifierKeys::commandModifier);
      break;

    case DrawMusicCommandID::saveDrawing:
      result.setInfo(TRANS("Save"), TRANS("Saves the current drawing"), CommandCategories::general,
                     0);
      result.addDefaultKeypress('s', ModifierKeys::commandModifier);
      break;

    case DrawMusicCommandID::saveDrawingAs:
      result.setInfo(TRANS("Save as..."), TRANS("Saves the current drawing to a new location"),
                     CommandCategories::general, 0);
      result.addDefaultKeypress('s', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
      break;

    case DrawMusicCommandID::exportAudio:
      result.setInfo(TRANS("Export audio..."), TRANS("Saves the audio for the current drawing"),
                     CommandCategories::general, 0);
      break;

    case DrawMusicCommandID::openSettings:
      result.setInfo(TRANS("Settings..."), TRANS("Opens application settings"),
                     CommandCategories::general, 0);
      break;

    case DrawMusicCommandID::play_pause:
      result.setInfo(TRANS("Play/Pause"), TRANS("Plays or pauses the audio playback"),
                     CommandCategories::general, 0);
      result.addDefaultKeypress(' ', 0);
      break;

    case StandardApplicationCommandIDs::undo:
      result.setInfo(TRANS("Undo"), TRANS("Undo brush stroke"), CommandCategories::editing, 0);
      result.addDefaultKeypress('z', ModifierKeys::commandModifier);
      result.setActive(gridActionManager_.canUndo());
      break;

    case StandardApplicationCommandIDs::redo:
      result.setInfo(TRANS("Redo"), TRANS("Redo brush stroke"), CommandCategories::editing, 0);
      result.addDefaultKeypress('z', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
      result.setActive(gridActionManager_.canRedo());
      break;

    case DrawMusicCommandID::gridSmaller:
      result.setInfo(TRANS("Smaller canvas"), TRANS("Reduces the size of the drawing canvas"),
                     CommandCategories::canvas, 0);
      result.setActive(Configuration::canDecreaseGridSize());
      break;

    case DrawMusicCommandID::gridLarger:
      result.setInfo(TRANS("Larger canvas"), TRANS("Increases the size of the drawing canvas"),
                     CommandCategories::canvas, 0);
      result.setActive(Configuration::canIncreaseGridSize());
      break;

    case StandardApplicationCommandIDs::del:
      result.setInfo(TRANS("Clear"), TRANS("Clears the current drawing"), CommandCategories::canvas,
                     0);
      break;

    default:
      break;
  }
}

bool MainComponent::perform(const InvocationInfo& info)
{
  switch (info.commandID)
  {
    case DrawMusicCommandID::newDrawing:
        /* TODO */;
      break;
    case DrawMusicCommandID::open:
      gridActionManager_.load();
      break;
    case DrawMusicCommandID::saveDrawing:
      gridActionManager_.save();
      break;
    case DrawMusicCommandID::saveDrawingAs:
      gridActionManager_.saveAs();
      break;
    case DrawMusicCommandID::exportAudio:
      audioSystem_.saveAudioToFile();
      break;
    case DrawMusicCommandID::openSettings:
      audioSystem_.openSettingsWindow();
      break;
    case DrawMusicCommandID::play_pause:
      togglePlayback();
      break;
    case StandardApplicationCommandIDs::undo:
      gridActionManager_.undo();
      break;
    case StandardApplicationCommandIDs::redo:
      gridActionManager_.redo();
      break;
    case StandardApplicationCommandIDs::del:
      clearGrid();
      break;
    case DrawMusicCommandID::gridSmaller:
      gridSmaller();
      break;
    case DrawMusicCommandID::gridLarger:
      gridLarger();
      break;

    default:
      return false;
  }

  return true;
}

// ===== private methods =====

void MainComponent::togglePlayback()
{
  if (audioSystem_.isPlaying())
  {
    stopPlayback();
  }
  else
  {
    startPlayback();
  }
}

void MainComponent::startPlayback()
{
  playStopButton_.setButtonText(TRANS("stop"));
  playStopButton_.setToggleState(true, NotificationType::dontSendNotification);
  playbackTimer_.startTimer(Configuration::getPlaybackTimerInterval());
  audioSystem_.startPlayback();
}

void MainComponent::stopPlayback()
{
  audioSystem_.stopPlayback();
  playbackTimer_.stopTimer();
  playStopButton_.setButtonText(TRANS("play"));
  playStopButton_.setToggleState(false, NotificationType::dontSendNotification);
}

void MainComponent::resizeGrid()
{
  gridActionManager_.resize(Configuration::getGridWidth(), Configuration::getGridHeight());
}

void MainComponent::clearGrid()
{
  if (gridData_.empty() ||
      AlertWindow::showOkCancelBox(AlertWindow::AlertIconType::WarningIcon, TRANS("Clear"),
                                   TRANS("Clear the whole piece?"), TRANS("CLEAR"), TRANS("Cancel"),
                                   this))
  {
    stopPlayback();
    audioSystem_.setNewPlaybackPosition(0.0f);
    gridActionManager_.clearGrid();
  }
}

void MainComponent::gridSmaller()
{
  if (Configuration::canDecreaseGridSize() &&
      (gridData_.empty() ||
       AlertWindow::showOkCancelBox(
           AlertWindow::AlertIconType::WarningIcon, TRANS("Resize?"),
           TRANS("Resizing the grid will clear the whole piece. Clear the whole piece?"),
           TRANS("CLEAR"), TRANS("Cancel"), this)))
  {
    if (Configuration::decreaseGridSize())
    {
      stopPlayback();
      resizeGrid();
      setSize(Configuration::getMainWindowWidth(), Configuration::getMainWindowHeight());
    }
  }
}

void MainComponent::gridLarger()
{
  if (Configuration::canIncreaseGridSize() &&
      (gridData_.empty() ||
       AlertWindow::showOkCancelBox(
           AlertWindow::AlertIconType::WarningIcon, TRANS("Resize?"),
           TRANS("Resizing the grid will clear the whole piece. Clear the whole piece?"),
           TRANS("CLEAR"), TRANS("Cancel"), this)))
  {
    if (Configuration::increaseGridSize())
    {
      stopPlayback();
      resizeGrid();
      setSize(Configuration::getMainWindowWidth(), Configuration::getMainWindowHeight());
    }
  }
}
