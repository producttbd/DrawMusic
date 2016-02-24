#include "WindowBoundsManager.h"

HashMap<String, Rectangle<int>> storedBounds_;

void WindowBoundsManager::saveBounds(juce::String windowName, Rectangle<int> bounds)
{
    storedBounds_.set(windowName, bounds);
}

Rectangle<int> WindowBoundsManager::getBounds(juce::String windowName)
{
    return storedBounds_[windowName];
}
