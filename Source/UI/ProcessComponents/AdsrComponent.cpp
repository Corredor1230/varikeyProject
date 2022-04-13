/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 23 Mar 2022 12:03:15pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::String name, juce::AudioProcessorValueTreeState& vts,
    juce::String attackID, juce::String decayID, juce::String sustainID,
    juce::String releaseID)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    attAttachment = std::make_unique<SliderAttachment>(vts, attackID, attSlider);
    decAttachment = std::make_unique<SliderAttachment>(vts, decayID, decSlider);
    susAttachment = std::make_unique<SliderAttachment>(vts, sustainID, susSlider);
    relAttachment = std::make_unique<SliderAttachment>(vts, releaseID, relSlider);


    setSliderParams(attSlider, attLabel, "A");
    setSliderParams(decSlider, decLabel, "D");
    setSliderParams(susSlider, susLabel, "S");
    setSliderParams(relSlider, relLabel, "R");
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour());
}

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto labelHeight = bounds.getHeight() / 8;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() - labelHeight;
    const auto labelWidth = sliderWidth;
    const auto sliderStartX = 0;
    const auto sliderStartY = 0 + labelHeight;
    const auto labelStartY = 0;


    attSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    attLabel.setBounds(sliderStartX, labelStartY, labelWidth, labelHeight);
    decSlider.setBounds(attSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    decLabel.setBounds(attLabel.getRight() + padding, labelStartY, labelWidth, labelHeight);
    susSlider.setBounds(decSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    susLabel.setBounds(decLabel.getRight() + padding, labelStartY, labelWidth, labelHeight);
    relSlider.setBounds(susSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    relLabel.setBounds(susLabel.getRight() + padding, labelStartY, labelWidth, labelHeight);

}

void AdsrComponent::setSliderParams(juce::Slider& slider, juce::Label& label, const std::string& name)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    slider.setColour(juce::Slider::ColourIds::backgroundColourId, setCustomColour(blue));
    slider.setColour(juce::Slider::ColourIds::trackColourId, setCustomColour(teal));
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
    label.setText(name, juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::centredTop);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.attachToComponent(&slider, false);
}

juce::Colour AdsrComponent::setCustomColour(const std::array<int, 3> colourArray)
{
    return juce::Colour(colourArray[0], colourArray[1], colourArray[2]);
}
