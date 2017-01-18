#ifndef BRUSHPREVIEWBUTTON_H_INCLUDED
#define BRUSHPREVIEWBUTTON_H_INCLUDED

#include "JuceHeader.h"

#include "AbstractCompleteBrush.h"

class BrushPreviewButton : public Button
{
public:
    explicit BrushPreviewButton(const AbstractCompleteBrush* brush);
    void paintButton(Graphics& g,
                     bool isMouseOverButton,
                     bool isButtonDown) override;
    
private:
    const AbstractCompleteBrush* brush_;
};

#endif // BRUSHPREVIEWBUTTON_H_INCLUDED