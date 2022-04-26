/*
  ==============================================================================

    FmComponent.cpp
    Created: 20 Apr 2022 12:59:36pm
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FmComponent.h"

//==============================================================================
FmComponent::FmComponent()
{
    setSliderParams(ratioSlider, ratioLabel, "Ratio", rotary);
    setSliderParams(depthSlider, depthLabel, "Depth", rotary);
    addAndMakeVisible(titleLabel);
    ratioSlider.setRange(1.0, 8.0, 0.1);
    depthSlider.setRange(0.0, 24.0, 0.1);

}

FmComponent::~FmComponent()
{
}

void FmComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour());
    juce::Rectangle<float> border;
    border.setBounds(5, 5, getWidth() - 10, getHeight() - 10);
    g.setColour(getLookAndFeel().findColour(juce::ToggleButton::ColourIds::tickDisabledColourId));
    g.drawRect(border, 1.0f);

    auto bounds = getBounds().reduced(5, 5);
    int height = bounds.getHeight();
    int width = bounds.getWidth();
    int padding = 10;
    int titleHeight = 18;
    int title = height / 6;
    int sliderLabelWidth = width / 5;
    int sliderLabelHeight = height / 4;

    int sliderWidth = (width / 2) - padding;
    int sliderHeight = height - titleHeight + padding / 2;
    int sliderDiameter = std::min(sliderWidth, sliderHeight);
    int titleStartX = padding;
    int titleStartY = 3;
    int sliderStartX = padding;

    titleLabel.setText("FM Mod", juce::dontSendNotification);
    titleLabel.setBounds(padding * 1.5, padding / 1.5, width, titleHeight);
    ratioLabel.setBounds(padding, height / 2, sliderLabelWidth, sliderLabelHeight);
    ratioSlider.setBounds(ratioLabel.getRight() - padding, titleLabel.getBottom() - padding / 2, sliderDiameter, sliderDiameter);
    depthLabel.setBounds(ratioSlider.getRight(), height / 2, sliderLabelWidth, sliderLabelHeight);
    depthSlider.setBounds(depthLabel.getRight() - padding, titleLabel.getBottom() - padding / 2, sliderDiameter, sliderDiameter);
}

void FmComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void FmComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}

void FmComponent::setSliderParams(juce::Slider& slider, juce::Label& label, juce::String name, int style = rotary)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    label.setText(name, juce::dontSendNotification);

    switch (style)
    {
    case vertical:
        label.attachToComponent(&slider, false);
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        break;
    case rotary:
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        label.setJustificationType(juce::Justification::centredRight);
        break;
    case horizontal:
        slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 25);
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
        break;
    default:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
        break;
    }
}
