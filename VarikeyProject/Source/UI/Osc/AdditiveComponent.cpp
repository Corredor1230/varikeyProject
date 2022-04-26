/*
  ==============================================================================

    AdditiveComponent.cpp
    Created: 8 Apr 2022 11:36:19am
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdditiveComponent.h"

//==============================================================================
AdditiveComponent::AdditiveComponent()
{
    setSliderParams(slider0, label0, "0", vertical);
    setSliderParams(slider1, label1, "1", vertical);
    setSliderParams(slider2, label2, "2", vertical);
    setSliderParams(slider3, label3, "3", vertical);
    setSliderParams(slider4, label4, "4", vertical);
    setSliderParams(slider5, label5, "5", vertical);
    setSliderParams(slider6, label6, "6", vertical);
    setSliderParams(slider7, label7, "7", vertical);
    addAndMakeVisible(titleLabel);
}

AdditiveComponent::~AdditiveComponent()
{
}

void AdditiveComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour());
    juce::Rectangle<float> border;
    border.setBounds(5, 5, getWidth() - 10, getHeight() - 10);
    g.setColour(slider0.findColour(juce::ToggleButton::ColourIds::tickDisabledColourId));
    g.drawRect(border, 1.0f);
}

void AdditiveComponent::resized()
{
    auto bounds = getBounds().reduced(5, 5);
    int height = bounds.getHeight();
    int width = bounds.getWidth();
    int padding = 10;
    int sliderLabel = height / 6;
    int title = height / 6;
    int sliderWidth = (width / 8) - padding;
    int sliderStartX = padding;
    int labelStartX = (padding * 2) / 1.1;
    int topStartY = 3;

    titleLabel.setText(regionTitle + componentTitle, juce::dontSendNotification);
    titleLabel.setBounds(padding * 1.5, padding / 1.5, width, title);
    int sliderStartY = sliderLabel + titleLabel.getBottom();
    int sliderHeight = height - titleLabel.getBottom() - sliderLabel;
    slider0.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    slider1.setBounds(slider0.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider2.setBounds(slider1.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider3.setBounds(slider2.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider4.setBounds(slider3.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider5.setBounds(slider4.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider6.setBounds(slider5.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider7.setBounds(slider6.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

}

void AdditiveComponent::setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setNormalisableRange(juce::NormalisableRange<double>(0.0, 8.0, 1.0));
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(&slider, false);

    switch (style)
    {
    case vertical:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        break;
    case rotary:
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        break;
    case horizontal:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
        break;
    default:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
        break;
    }
}

void AdditiveComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}

void AdditiveComponent::setRegionTitle(juce::String& region)
{
    regionTitle = region;
}