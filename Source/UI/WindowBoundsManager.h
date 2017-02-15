#ifndef WINDOWSBOUNDSMANAGER_H_INCLUDED
#define WINDOWSBOUNDSMANAGER_H_INCLUDED

#include "JuceHeader.h"

class WindowBoundsManager
{
 public:
  static void saveBounds(String windowName, Rectangle<int> bounds);
  static Rectangle<int> getBounds(String windowName);

  // private:
  //    static HashMap<String, Rectangle<int>> storedBounds_;
};

#endif  // WINDOWSBOUNDSMANAGER_H_INCLUDED