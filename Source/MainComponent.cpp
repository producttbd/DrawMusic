#include "MainComponent.h"

#include "AudioSettingsWindow.h"
#include "BrushPaletteWindow.h"
#include "Configuration.h"
#include "DFMSLookAndFeel.h"

MainComponent::MainComponent ()
  : gridData_(new GridData(Configuration::getGridWidth(), Configuration::getGridHeight())),
    colourScheme_(),
    brushPalette_("brushPalette", colourScheme_),
    drawGrid_(nullptr),
    deviceManager_(),
    audioSourcePlayer_(),
    transportSource_(),
    gridAudioSource_(nullptr),
    playbackTimeline_("playbackTimeline"),
    playbackTimer_(playbackTimeline_),
    thread_("audio file preview"),
    waveformView_("waveform view"),
    playStopButton_("playStopButton"),
    clearButton_("clearButton"),
    exportButton_("exportButton"),
    settingsButton_("settingsButton"),
    gridSmallerButton_("gridSmallerButton"),
    gridLargerButton_("gridBiggerButton"),
    allButtons_({&playStopButton_, &clearButton_, &exportButton_,
                 &settingsButton_, &gridSmallerButton_, &gridLargerButton_})
{
    // Buttons
    playStopButton_.setButtonText (TRANS("play"));
    playStopButton_.setConnectedEdges (Button::ConnectedOnRight);
    clearButton_.setButtonText(TRANS("clear"));
    clearButton_.setConnectedEdges(Button::ConnectedOnLeft & Button::ConnectedOnRight);
    exportButton_.setButtonText(TRANS("export"));
    exportButton_.setConnectedEdges(Button::ConnectedOnLeft & Button::ConnectedOnRight);
    settingsButton_.setButtonText(TRANS("settings"));
    settingsButton_.setConnectedEdges(Button::ConnectedOnLeft & Button::ConnectedOnRight);
    gridSmallerButton_.setButtonText(TRANS("smaller"));
    gridSmallerButton_.setConnectedEdges(Button::ConnectedOnLeft & Button::ConnectedOnRight);
    gridLargerButton_.setButtonText(TRANS("bigger"));
    gridLargerButton_.setConnectedEdges(Button::ConnectedOnLeft);

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
    deviceManager_.initialise (0, 2, 0, true, String::empty, 0); // TODO channels?
    thread_.startThread(3);
    deviceManager_.addAudioCallback(&audioSourcePlayer_);
    audioSourcePlayer_.setSource(&transportSource_);

    // Grid-size dependent things
    recreateEverything();

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

void MainComponent::paint (Graphics& g)
{
    g.fillAll(DFMSLookAndFeel::getDefaultBackgroundColour());
}

void MainComponent::resized()
{
    const int gridWidth = Configuration::getGridWidth();
    const int gridHeight = Configuration::getGridHeight();

    const int outsideMargin = Configuration::getGuiMargin();
    drawGrid_->setBounds(outsideMargin, outsideMargin, gridWidth, gridHeight);

    waveformView_.setBounds(outsideMargin, 2 * outsideMargin + gridHeight,
                            gridWidth, Configuration::getWaveformViewHeight());
    
    playbackTimeline_.setBounds(outsideMargin, outsideMargin,
                                gridWidth, gridHeight + outsideMargin + Configuration::getWaveformViewHeight());
    auto clickBoundsForWaveformView = playbackTimeline_.getLocalArea(this, waveformView_.getBounds());
    playbackTimeline_.setToControlAudioSource(clickBoundsForWaveformView, gridAudioSource_);

    const int buttonWidth = Configuration::getButtonWidth();
    const int buttonHeight = Configuration::getButtonHeight();
    const int buttonY = getHeight() - buttonHeight - outsideMargin;

    int buttonNum = 0;
    for (Button* button : allButtons_) {
        button->setBounds(outsideMargin + buttonNum * buttonWidth, buttonY, buttonWidth, buttonHeight);
        ++buttonNum;
    }

    const int paletteSide = Configuration::getPaletteSide();
    brushPalette_.setBounds(getWidth() - paletteSide - outsideMargin, getHeight() - paletteSide - outsideMargin,
                            paletteSide, paletteSide);
}

void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == &playStopButton_)
    {
        togglePlayback();
    }
    else if (buttonThatWasClicked == &clearButton_)
    {
        if (AlertWindow::showOkCancelBox(
                AlertWindow::AlertIconType::WarningIcon, TRANS("Clear"), TRANS("Clear the whole piece?"),
                TRANS("CLEAR"), TRANS("Cancel"), this))
        {
            stopPlayback();
            transportSource_.setPosition(0);
            gridData_->clear();
            drawGrid_->refreshAll();
        }
    }
    else if (buttonThatWasClicked == &exportButton_)
    {
        AudioFormatManager afManager;
        afManager.registerBasicFormats();
        AudioFormat* format = afManager.getDefaultFormat();
        
        FileChooser fileChooser(TRANS("Select output file"),
                                File::nonexistent,
                                format->getFileExtensions().joinIntoString(";"));
        if (fileChooser.browseForFileToSave(true))
        {
            File file(fileChooser.getResult());
            auto buffer = gridAudioSource_->getOutputBuffer();
            ScopedPointer<AudioFormatWriter> writer =
                    format->createWriterFor(file.createOutputStream(), 44100, buffer.getNumChannels(), 16, NULL, 0);
            writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
        }
        
    }
    else if (buttonThatWasClicked == &settingsButton_)
    {
        openAudioSettingsWindow();
    }
    else if (buttonThatWasClicked == &gridSmallerButton_)
    {
        if (Configuration::decreaseGridSize())
        {
            recreateEverything();
            setSize(Configuration::getMainWindowWidth(), Configuration::getMainWindowHeight());
        }
    }
    else if (buttonThatWasClicked == &gridLargerButton_)
    {
        if (Configuration::increaseGridSize())
        {
            recreateEverything();
            setSize(Configuration::getMainWindowWidth(), Configuration::getMainWindowHeight());
        }
    }
}

void MainComponent::recreateEverything()
{
    transportSource_.setSource(nullptr);
    gridData_ = new GridData(Configuration::getGridWidth(), Configuration::getGridHeight());
    drawGrid_ = new DrawGrid(*gridData_, colourScheme_, brushPalette_);
    addAndMakeVisible(drawGrid_);
    drawGrid_->toBack();
    gridAudioSource_ = new GridAudioRendererAudioSource(gridData_.get());
    drawGrid_->addChangeListener(gridAudioSource_);
    gridAudioSource_->addNewAudioListener(&waveformView_);
    gridAudioSource_->addNewPositionListener(&playbackTimeline_);
    transportSource_.setSource(gridAudioSource_);
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
    playStopButton_.setButtonText (TRANS("stop"));
    playStopButton_.setToggleState(true, NotificationType::dontSendNotification);
    playbackTimer_.startTimer(Configuration::getPlaybackTimerInterval());
    transportSource_.start();
}

void MainComponent::stopPlayback()
{
    transportSource_.stop();
    playbackTimer_.stopTimer();
    playStopButton_.setButtonText (TRANS("play"));
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