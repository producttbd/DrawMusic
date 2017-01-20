#ifndef BASEWINDOW_H_INCLUDED
#define BASEWINDOW_H_INCLUDED

#include "JuceHeader.h"

class BaseWindow : public DocumentWindow
{
public:
    BaseWindow(String name);
    virtual ~BaseWindow();

    void closeButtonPressed() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BaseWindow);
};

#endif // BASEWINDOW_H_INCLUDED