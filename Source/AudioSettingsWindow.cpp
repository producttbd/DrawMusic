/*
  ==============================================================================

    AudioSettingsWindow.cpp
    Created: 2 Jan 2016 4:35:10pm
    Author:  trevork

  ==============================================================================
*/

#include "AudioSettingsWindow.h"

#include "Configuration.h"
#include "DFMSLookAndFeel.h"

AudioSettingsWindow::AudioSettingsWindow(String name, AudioDeviceManager& audioDeviceManager)
: DocumentWindow(name, DFMSLookAndFeel::getDefaultBackgroundColour(), DocumentWindow::closeButton),
audioDeviceSelector_(/*AudioDeviceManager&*/ audioDeviceManager,
                     /*int minAudioInputChannels*/ 0,
                     /*int maxAudioInputChannels*/ 256,
                     /*int minAudioOutputChannels*/ 0,
                     /*int maxAudioOutputChannels*/ 256,
                     /*bool showMidiInputOptions*/ false,
                     /*bool showMidiOutputSelector*/ false,
                     /*bool showChannelsAsStereoPairs*/ true,
                     /*bool hideAdvancedOptionsWithButton*/ true)
{
    setResizable(true, true);
    
    setContentOwned(&audioDeviceSelector_, false);
}

void AudioSettingsWindow::closeButtonPressed()
{
    delete this;
}