/*
  ==============================================================================

    FilterComponent.cpp
    Created: 2 Apr 2022 1:55:21am
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& vts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    cutoffAttachment = std::make_unique<SliderAttachment>(vts, "cutoff", cutoffSlider);
    qAttachment = std::make_unique<SliderAttachment>(vts, "q", qSlider);
    filterOnOffAttachment = std::make_unique<ButtonAttachment>(vts, "filterOnOff", filterOnOff);

    addAndMakeVisible(filterOnOff);
    filterOnOff.setButtonText("Filter On/Off");
    filterOnOff.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, setCustomColour(dark));
    filterOnOff.setColour(juce::ToggleButton::ColourIds::tickColourId, setCustomColour(pink));
    filterOnOff.setColour(juce::ToggleButton::ColourIds::textColourId, juce::Colours::white);
    setSliderParams(cutoffSlider, cutoffLabel, "Cutoff");
    cutoffSlider.setTextValueSuffix("Hz");
    setSliderParams(qSlider, qLabel, "Q");
    //cutoffSlider.setSkewFactorFromMidPoint(1000.f);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{

    g.fillAll (juce::Colour::Colour());   // clear the background

}

void FilterComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto labelHeight = getHeight() / 8;
    const auto filterToggle = getHeight() / 8;
    const auto sliderHeight = (getHeight() / 2) - labelHeight;
    const auto sliderWidth = getWidth() / 4;
    const auto knobRadius = std::min(sliderHeight, sliderWidth);
    const auto toggleStartY = 0;
    const auto toggleStartX = 0;
    const auto sliderStartX = 0;
    const auto labelStartX = 0;
    const auto sliderStartY = 0 + labelHeight + filterToggle;
    const auto labelStartY = 0 + filterToggle;

    cutoffLabel.setBounds(labelStartX, labelStartY, sliderHeight, labelHeight);
    cutoffSlider.setBounds(sliderStartX, sliderStartY, knobRadius, knobRadius);
    filterOnOff.setBounds(toggleStartX, toggleStartY, sliderWidth, filterToggle);
    qLabel.setBounds(labelStartX, labelStartY, sliderHeight, labelHeight);
    qSlider.setBounds(cutoffSlider.getRight(), sliderStartY, knobRadius, knobRadius);
    
}

void FilterComponent::setSliderParams(juce::Slider& slider, juce::Label& label, std::string name)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    label.attachToComponent(&slider, false);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, setCustomColour(pink));
    slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, setCustomColour(dark));
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setText(name, juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::centredTop);
}

juce::Colour FilterComponent::setCustomColour(const std::array<int, 3> colourArray)
{
    return juce::Colour::Colour(colourArray[0], colourArray[1], colourArray[2]);
}