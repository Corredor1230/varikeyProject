/*
  ==============================================================================

    DistComponent.cpp
    Created: 30 Apr 2022 2:32:30pm
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistComponent.h"

//==============================================================================
DistComponent::DistComponent(juce::AudioProcessorValueTreeState& vts, juce::String inputID,
    juce::String outputID, juce::String toggleID) : vts(vts)
    , inputAttachment(vts, inputID, inputSlider)
    , outputAttachment(vts, outputID, outputSlider)
    , distToggleAttachment(vts, toggleID, distToggle)

{
    addAndMakeVisible(distToggle);
    addAndMakeVisible(distToggleLabel);

    setSliderParams(inputSlider, inputLabel, "Input", rotary);
    setSliderParams(outputSlider, outputLabel, "Output", rotary);
    distToggleLabel.setText("On/Off", juce::sendNotification);

    addAndMakeVisible(titleLabel);
}

DistComponent::~DistComponent()
{
}

void DistComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour());
    //juce::Rectangle<float> border;
    //border.setBounds(5, 5, getWidth() - 10, getHeight() - 10);
    //g.setColour(getLookAndFeel().findColour(juce::ToggleButton::ColourIds::tickDisabledColourId));
    //g.drawRect(border, 1.0f);

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

    titleLabel.setText("Distortion", juce::dontSendNotification);
    titleLabel.setBounds(padding * 1.5, padding / 1.5, sliderLabelWidth + padding * 2, titleHeight);
    distToggle.setBounds(titleLabel.getRight(), padding / 1.5, sliderLabelWidth, titleHeight);
    distToggleLabel.setBounds(distToggle.getRight() - padding, padding / 1.5, sliderLabelWidth + padding, titleHeight);
    inputLabel.setBounds(padding, height / 2, sliderLabelWidth, sliderLabelHeight);
    inputSlider.setBounds(inputLabel.getRight() - padding, titleLabel.getBottom() - padding / 2, sliderDiameter, sliderDiameter);
    outputLabel.setBounds(inputSlider.getRight() + 10, height / 2, sliderLabelWidth, sliderLabelHeight);
    outputSlider.setBounds(outputLabel.getRight() - padding, titleLabel.getBottom() - padding / 2, sliderDiameter, sliderDiameter);

    juce::Colour toggleOff = getLookAndFeel().findColour(juce::ToggleButton::ColourIds::tickDisabledColourId);
    juce::Colour toggleOn = getLookAndFeel().findColour(juce::Slider::ColourIds::textBoxTextColourId);

    switch (distToggle.getToggleState())
    {
    case 0:
        inputSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, toggleOff);
        inputLabel.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        outputSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, toggleOff);
        outputLabel.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        titleLabel.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        distToggle.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, toggleOff);
        distToggleLabel.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        break;
    case 1:
        inputSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, toggleOn);
        inputLabel.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        outputSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, toggleOn);
        outputLabel.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        titleLabel.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        distToggle.setColour(juce::ToggleButton::ColourIds::tickColourId, toggleOn);
        distToggle.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, toggleOn);
        distToggleLabel.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        break;
    }

}

void DistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void DistComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}

void DistComponent::setSliderParams(juce::Slider& slider, juce::Label& label, juce::String name, int style = rotary)
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
