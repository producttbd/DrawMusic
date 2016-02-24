#include "AudioSettingsWindow.h"

#include "Configuration.h"
#include "DFMSLookAndFeel.h"

AudioSettingsWindow::AudioSettingsWindow(String name, AudioDeviceManager& audioDeviceManager)
: BaseWindow(name),
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
    setContentOwned(&audioDeviceSelector_, false);
}
