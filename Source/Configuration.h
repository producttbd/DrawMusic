/*
 ==============================================================================
 
 Configuration.h
 Created: 3 Jul 2015 10:34:23pm
 Author:  Trevor Knight
 
 ==============================================================================
*/

#ifndef DFMS2_Configuration_h

#include "../JuceLibraryCode/JuceHeader.h"

class Configuration
{
public:
    static constexpr int getMainWindowHeight() { return 582; }
    static constexpr int getMainWindowWidth() { return totalNumberWindows + 2 * guiMargin; }
    
    static constexpr int getGuiMargin() { return guiMargin; }

    static constexpr int getNumberChannels() { return 1; }
    static constexpr int getFftOrder() { return fftOrder; }
    static constexpr int getFftLength() { return windowLength; }

    static constexpr int getGridHeight() { return windowLength / 2 + 1; }
    static constexpr int getGridWidth() { return totalNumberWindows; }
    
    static constexpr int getTotalAudioSampleLength()
    {
        return (totalNumberWindows + 1) * (windowLength / 2);
    }

private:
    static constexpr int guiMargin = 10;
    static constexpr int fftOrder = 10;
    static constexpr int windowLength = 1 << fftOrder;
    static constexpr int totalNumberWindows = 1000;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Configuration);
};

#define DFMS2_Configuration_h


#endif
