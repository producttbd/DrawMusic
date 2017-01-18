#ifndef BRUSHCOLLECTION_H_INCLUDED
#define BRUSHCOLLECTION_H_INCLUDED

#include "JuceHeader.h"

#include "AbstractCompleteBrush.h"

class BrushCollection : public ChangeBroadcaster
{
public:
    BrushCollection();
    
    void add(const AbstractCompleteBrush* newBrush);
    
    int getCurrentBrushIndex() const ;
    void setCurrentBrush(int index);
    
    int size() const;
    const AbstractCompleteBrush* getCurrentBrush() const;
    const AbstractCompleteBrush* getBrush(int index) const;
    
private:
    OwnedArray<const AbstractCompleteBrush> brushes_;
    int currentBrush_;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BrushCollection);
};

#endif // BRUSHCOLLECTION_H_INCLUDED