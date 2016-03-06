#include "BasicBrushControls.h"

#include "Configuration.h"

BasicBrushControls::BasicBrushControls()
{
}

void BasicBrushControls::addControl(ControlSpec spec)
{
    Slider* newSlider = new Slider(spec.name);
    
    newSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    newSlider->setRange(spec.minValue, spec.maxValue);
    newSlider->setValue(spec.currentValue);
    newSlider->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    newSlider->setPopupDisplayEnabled(true, this);
    newSlider->addListener(this);
    sliders_.add(newSlider);

    Label* label = new Label(spec.name, spec.name);
    label->setEditable(false);
    label->setJustificationType(Justification::left);
    labels_.add(label);
    addAndMakeVisible(label);

    addAndMakeVisible(newSlider);
}

void BasicBrushControls::addControls(Array<ControlSpec> specs)
{
    for (auto spec : specs)
    {
        addControl(spec);
    }
}

void BasicBrushControls::sliderValueChanged(juce::Slider* slider)
{
    ControlSpec spec;
    spec.name = slider->getName();
    spec.currentValue = slider->getValue();
    spec.minValue = slider->getMinimum();
    spec.maxValue = slider->getMaximum();
    listeners_.call(&AbstractBrushControls::Listener::controlChanged, spec);
}

void BasicBrushControls::resized()
{
    const int margin = Configuration::getGuiMargin();
    const int labelHeight = 30;
    const int sliderHeight = 50;
    const int totalHeight = labelHeight + sliderHeight;
    const int width = getWidth() - 2 * margin;

    
    for (int i = 0; i < sliders_.size(); ++i)
    {
        labels_[i]->setBounds(margin, margin + i * totalHeight, width, labelHeight);
        sliders_[i]->setBounds(margin, margin + i * totalHeight + labelHeight,
                               width, sliderHeight);
    }
}