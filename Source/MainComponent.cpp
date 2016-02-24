#include "MainComponent.h"

#include "AudioSettingsWindow.h"
#include "BrushPaletteWindow.h"
#include "Configuration.h"
#include "DFMSLookAndFeel.h"

MainComponent::MainComponent ()
  : gridData_(Configuration::getGridWidth(), Configuration::getGridHeight()), //TODO This janky dependency chain
    colourScheme_(),
    brushPalette_("brushPalette", colourScheme_),
    drawGrid_(gridData_, colourScheme_, brushPalette_),
    deviceManager_(),
    audioSourcePlayer_(),
    transportSource_(),
    gridAudioSource_(gridData_),
    playbackTimeline_("playbackTimeline"),
    playbackTimer_(playbackTimeline_),
    thread_("audio file preview"),
    waveformView_("waveform view"),
    playStopButton_("playStopButton"),
    clearButton_("clearButton"),
    exportButton_("exportButton"),
    settingsButton_("settingsButton"),
    reconstructionSlider_("reconstructionSlider")
{
    addAndMakeVisible(&brushPalette_);

    addAndMakeVisible(&playStopButton_);
    playStopButton_.setButtonText (TRANS("play"));
    playStopButton_.setConnectedEdges (Button::ConnectedOnRight);
    playStopButton_.addListener (this);

    addAndMakeVisible(&clearButton_);
    clearButton_.setButtonText(TRANS("clear"));
    clearButton_.setConnectedEdges(Button::ConnectedOnLeft & Button::ConnectedOnRight);
    clearButton_.addListener(this);
    
    addAndMakeVisible(&exportButton_);
    exportButton_.setButtonText(TRANS("export"));
    exportButton_.setConnectedEdges(Button::ConnectedOnLeft & Button::ConnectedOnRight);
    exportButton_.addListener(this);
    
    addAndMakeVisible(&settingsButton_);
    settingsButton_.setButtonText(TRANS("settings"));
    settingsButton_.setConnectedEdges(Button::ConnectedOnLeft);
    settingsButton_.addListener(this);

    addAndMakeVisible(&waveformView_);

    addAndMakeVisible(&reconstructionSlider_);
    reconstructionSlider_.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    reconstructionSlider_.setTextBoxStyle(Slider::TextBoxLeft, false, 30, 30); // TODO magic number
    reconstructionSlider_.setRange(0, 10, 1);
    reconstructionSlider_.addListener(&gridAudioSource_);

    addAndMakeVisible(&drawGrid_);
    
    addAndMakeVisible(&playbackTimeline_);

    setSize(Configuration::getMainWindowWidth(), Configuration::getMainWindowHeight());

    // Listener registration
    drawGrid_.addChangeListener(&gridAudioSource_);
    gridAudioSource_.addNewAudioListener(&waveformView_);
    gridAudioSource_.addNewPositionListener(&playbackTimeline_);

    // Audio
    deviceManager_.initialise (0, 2, 0, true, String::empty, 0); // TODO channels?
    thread_.startThread(3);
    deviceManager_.addAudioCallback(&audioSourcePlayer_);
    audioSourcePlayer_.setSource(&transportSource_);
    transportSource_.setSource(nullptr);
}

MainComponent::~MainComponent()
{
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
    drawGrid_.setBounds(outsideMargin, outsideMargin, gridWidth, gridHeight);

    waveformView_.setBounds(outsideMargin, 2 * outsideMargin + gridHeight,
                            gridWidth, Configuration::getWaveformViewHeight());
    
    playbackTimeline_.setBounds(outsideMargin, 2 * outsideMargin + gridHeight,
                                gridWidth, Configuration::getWaveformViewHeight());

    const int buttonWidth = 80;
    const int buttonHeight = 24;
    const int buttonY = getHeight() - buttonHeight - outsideMargin;
    playStopButton_.setBounds(outsideMargin, buttonY, buttonWidth, buttonHeight);
    clearButton_.setBounds(outsideMargin + buttonWidth, buttonY, buttonWidth, buttonHeight);
    exportButton_.setBounds(outsideMargin + 2 * buttonWidth, buttonY, buttonWidth, buttonHeight);
    settingsButton_.setBounds(outsideMargin + 3 * buttonWidth, buttonY, buttonWidth, buttonHeight);
    reconstructionSlider_.setBounds(outsideMargin + 4 * buttonWidth, buttonY, 2 * buttonWidth, buttonHeight);

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
        stopPlayback();
        gridData_.clear();
        drawGrid_.refreshAll();
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
            auto buffer = gridAudioSource_.getOutputBuffer();
            ScopedPointer<AudioFormatWriter> writer = format->createWriterFor(file.createOutputStream(), 44100, buffer.getNumChannels(), 16, NULL, 0);
            writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
        }
        
    }
    else if (buttonThatWasClicked == &settingsButton_)
    {
        openAudioSettingsWindow();
    }
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
    transportSource_.setSource(&gridAudioSource_);
    transportSource_.setPosition (0);
    playStopButton_.setButtonText (TRANS("stop"));
    playStopButton_.setToggleState(true, NotificationType::dontSendNotification);
    playbackTimer_.startTimer(Configuration::getPlaybackTimerInterval());
    transportSource_.start();
}

void MainComponent::stopPlayback()
{
    transportSource_.stop();
    playbackTimer_.stopTimer();
    transportSource_.setSource(nullptr);
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