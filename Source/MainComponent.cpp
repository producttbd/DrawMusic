#include "MainComponent.h"

#include "AudioFileWriter.h"
#include "AudioSettingsWindow.h"
#include "BrushPaletteWindow.h"
#include "Configuration.h"
#include "DrawMusicLookAndFeel.h"
#include "GridDataChangedNotifier.h"

MainComponent::MainComponent()
    : gridData_(Configuration::getGridWidth(), Configuration::getGridHeight()),
      brushPalette_("brushPalette", gridColourScheme_),
      gridDataChangedNotifier_(),
      gridActionManager_(brushPalette_, gridData_, gridDataChangedNotifier_),
      gridColourScheme_(),
      drawGrid_(gridActionManager_, gridData_, gridColourScheme_),
      deviceManager_(),
      audioSourcePlayer_(),
      transportSource_(),
      gridAudioSource_(gridData_),
      playbackTimeline_("playbackTimeline"),
      playbackTimer_(playbackTimeline_),
      waveformView_("waveform view"),
      playStopButton_("playStopButton"),
      clearButton_("clearButton"),
      exportButton_("exportButton"),
      saveButton_("saveButton"),
      loadButton_("loadButton"),
      gridSmallerButton_("gridSmallerButton"),
      gridLargerButton_("gridBiggerButton"),
      undoButton_("undoButton"),
      redoButton_("redoButton"),
      settingsButton_("settingsButton"),
      allButtons_({
          &playStopButton_, &clearButton_, &exportButton_, &saveButton_, &loadButton_,
          &gridSmallerButton_, &gridLargerButton_, &undoButton_, &redoButton_, &settingsButton_,
      })
{
  // Buttons
  playStopButton_.setButtonText(TRANS("play"));
  playStopButton_.setConnectedEdges(Button::ConnectedOnRight);
  clearButton_.setButtonText(TRANS("clear"));
  clearButton_.setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
  exportButton_.setButtonText(TRANS("save audio"));
  exportButton_.setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
  saveButton_.setButtonText(TRANS("save drawing")),
      saveButton_.setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
  loadButton_.setButtonText(TRANS("load drawing")),
      loadButton_.setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
  gridSmallerButton_.setButtonText(TRANS("smaller"));
  gridSmallerButton_.setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
  gridLargerButton_.setButtonText(TRANS("bigger"));
  gridLargerButton_.setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
  undoButton_.setButtonText(TRANS("undo"));
  undoButton_.setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
  redoButton_.setButtonText(TRANS("redo"));
  redoButton_.setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
  settingsButton_.setButtonText(TRANS("settings"));
  settingsButton_.setConnectedEdges(Button::ConnectedOnLeft);

  for (Button* button : allButtons_)
  {
    addAndMakeVisible(button);
    button->addListener(this);
  }

  // Non-buttons UI
  addAndMakeVisible(&brushPalette_);
  addAndMakeVisible(&waveformView_);
  addAndMakeVisible(drawGrid_);
  addAndMakeVisible(&playbackTimeline_);

  // Audio
  // TODO channels?
  deviceManager_.initialise(0 /* numInputChannelsNeeded */, 2 /* numOutputChannelsNeeded */,
                            0 /* savedState */, true /* selectDefaultDeviceOnFailure */);
  deviceManager_.addAudioCallback(&audioSourcePlayer_);
  audioSourcePlayer_.setSource(&transportSource_);
  transportSource_.setSource(&gridAudioSource_);

  // The WavefromView should know when new audio is available to redraw and the timeline should know
  // when the current position has changed.
  gridAudioSource_.addNewAudioListener(&waveformView_);
  gridAudioSource_.addNewPositionListener(&playbackTimeline_);

  // The actual UI Component, DrawGrid, should know when the underlying data is changed or resized.
  // The Grid...AudioSource should know when new data is available for turning into sound.
  gridDataChangedNotifier_.addGridDataResizedListener(&drawGrid_);
  gridDataChangedNotifier_.addGridDataResizedListener(&gridAudioSource_);
  gridDataChangedNotifier_.addGridDataUpdatedListener(&drawGrid_);
  gridDataChangedNotifier_.addGridDataUpdatedListener(&gridAudioSource_);

  // Finally set size
  setSize(Configuration::getMainWindowWidth(), Configuration::getMainWindowHeight());
}

MainComponent::~MainComponent()
{
  transportSource_.setSource(nullptr);
  if (audioSettingsWindow_ != nullptr)
  {
    audioSettingsWindow_.deleteAndZero();
  }
}

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
  playbackTimeline_.setToControlAudioSource(clickBoundsForWaveformView, &gridAudioSource_);

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

  gridSmallerButton_.setEnabled(Configuration::canDecreaseGridSize());
  gridLargerButton_.setEnabled(Configuration::canIncreaseGridSize());
}

void MainComponent::buttonClicked(Button* buttonThatWasClicked)
{
  if (buttonThatWasClicked == &playStopButton_)
  {
    togglePlayback();
  }
  else if (buttonThatWasClicked == &clearButton_)
  {
    if (AlertWindow::showOkCancelBox(AlertWindow::AlertIconType::WarningIcon, TRANS("Clear"),
                                     TRANS("Clear the whole piece?"), TRANS("CLEAR"),
                                     TRANS("Cancel"), this))
    {
      stopPlayback();
      transportSource_.setPosition(0);
      gridActionManager_.clearGrid();
    }
  }
  else if (buttonThatWasClicked == &exportButton_)
  {
    AudioFileWriter::saveToFileWithDialogBox(gridAudioSource_.getOutputBuffer());
  }
  else if (buttonThatWasClicked == &settingsButton_)
  {
    openAudioSettingsWindow();
  }
  else if (buttonThatWasClicked == &gridSmallerButton_)
  {
    if (Configuration::canDecreaseGridSize() &&
        AlertWindow::showOkCancelBox(
            AlertWindow::AlertIconType::WarningIcon, TRANS("Resize?"),
            TRANS("Resizing the grid will clear the whole piece. Clear the whole piece?"),
            TRANS("CLEAR"), TRANS("Cancel"), this))
    {
      if (Configuration::decreaseGridSize())
      {
        stopPlayback();
        resizeGrid();
        setSize(Configuration::getMainWindowWidth(), Configuration::getMainWindowHeight());
      }
    }
  }
  else if (buttonThatWasClicked == &gridLargerButton_)
  {
    if (Configuration::canIncreaseGridSize() &&
        AlertWindow::showOkCancelBox(
            AlertWindow::AlertIconType::WarningIcon, TRANS("Resize?"),
            TRANS("Resizing the grid will clear the whole piece. Clear the whole piece?"),
            TRANS("CLEAR"), TRANS("Cancel"), this))
    {
      if (Configuration::increaseGridSize())
      {
        stopPlayback();
        resizeGrid();
        setSize(Configuration::getMainWindowWidth(), Configuration::getMainWindowHeight());
      }
    }
  }
  else if (buttonThatWasClicked == &undoButton_)
  {
    gridActionManager_.undo();
  }
  else if (buttonThatWasClicked == &redoButton_)
  {
    gridActionManager_.redo();
  }
  else if (buttonThatWasClicked == &saveButton_)
  {
    gridActionManager_.save();
  }
  else if (buttonThatWasClicked == &loadButton_)
  {
    gridActionManager_.load();
  }
}

void MainComponent::resizeGrid()
{
  gridActionManager_.resize(Configuration::getGridWidth(), Configuration::getGridHeight());
}

void MainComponent::togglePlayback()
{
  if (transportSource_.isPlaying())
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
  transportSource_.start();
}

void MainComponent::stopPlayback()
{
  transportSource_.stop();
  playbackTimer_.stopTimer();
  playStopButton_.setButtonText(TRANS("play"));
  playStopButton_.setToggleState(false, NotificationType::dontSendNotification);
}

void MainComponent::openAudioSettingsWindow()
{
  if (audioSettingsWindow_ != nullptr)
  {
    return;
  }
  audioSettingsWindow_ = new AudioSettingsWindow(TRANS("audio settings window"), deviceManager_);
}