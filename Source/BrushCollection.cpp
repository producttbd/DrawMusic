#include "BrushCollection.h"
#include "BrushFactory.h"

BrushCollection::BrushCollection()
: currentBrush_(0)
{
    BrushFactory::getAllBrushes(*this);
}

void BrushCollection::add(const AbstractCompleteBrush* newBrush)
{
    brushes_.add(newBrush);
}

int BrushCollection::getCurrentBrushIndex() const
{
    return currentBrush_;
}

void BrushCollection::setCurrentBrush(int index)
{
    jassert(index >= 0 && index < size());
    currentBrush_ = index;
    sendChangeMessage();
}

int BrushCollection::size() const
{
    return brushes_.size();
}

const AbstractCompleteBrush* BrushCollection::getCurrentBrush() const
{
    return brushes_[currentBrush_];
}

const AbstractCompleteBrush* BrushCollection::getBrush(int index) const
{
    jassert(index >= 0 && index < size());
    return brushes_[index];
}