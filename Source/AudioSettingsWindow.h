/*
  ==============================================================================

    AudioSettingsWindow.h
    Created: 2 Jan 2016 4:35:10pm
    Author:  trevork

  ==============================================================================
*/

#ifndef AUDIOSETTINGSWINDOW_H_INCLUDED
#define AUDIOSETTINGSWINDOW_H_INCLUDED

#include "JuceHeader.h"

class AudioSettingsWindow : public DocumentWindow
{
public:
    AudioSettingsWindow(String name, AudioDeviceManager& audioDeviceManager);
    
    void closeButtonPressed() override;
    
private:
    AudioDeviceSelectorComponent audioDeviceSelector_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioSettingsWindow);
};


#endif  // AUDIOSETTINGSWINDOW_H_INCLUDED
