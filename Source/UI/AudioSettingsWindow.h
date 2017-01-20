#ifndef AUDIOSETTINGSWINDOW_H_INCLUDED
#define AUDIOSETTINGSWINDOW_H_INCLUDED

#include "JuceHeader.h"

#include "BaseWindow.h"

class AudioSettingsWindow : public BaseWindow
{
public:
    AudioSettingsWindow(String name, AudioDeviceManager& audioDeviceManager);
    
private:
    AudioDeviceSelectorComponent audioDeviceSelector_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioSettingsWindow);
};


#endif  // AUDIOSETTINGSWINDOW_H_INCLUDED
