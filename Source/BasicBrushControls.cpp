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
    const int sliderHeight = 50;
    const int margin = Configuration::getGuiMargin();
    
    for (int i = 0; i < sliders_.size(); ++i)
    {
        sliders_[i]->setBounds(margin, margin + i * sliderHeight, getWidth() - 2 * margin, sliderHeight);
    }
}