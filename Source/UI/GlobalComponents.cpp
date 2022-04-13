/*
  ==============================================================================

    GlobalComponents.cpp
    Created: 31 Mar 2022 9:03:17pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GlobalComponents.h"

//==============================================================================
GlobalComponents::GlobalComponents(juce::AudioProcessorValueTreeState& vts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    gainAttachment = std::make_unique<SliderAttachment>(vts, "gain", gainSlider);
    selectAttachment = std::make_unique<SliderAttachment>(vts, "selector", synthSelect);

    buildSlider(gainSlider, typeSlider);
    buildSlider(synthSelect, typeKnob);

}

GlobalComponents::~GlobalComponents()
{
}

void GlobalComponents::paint (juce::Graphics& g)
{

    g.fillAll (juce::Colour());
}

void GlobalComponents::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 2 - padding;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;

    gainSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    synthSelect.setBounds(gainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

}

void GlobalComponents::buildSlider(juce::Slider& thisSlider, sliderType type)
{
    addAndMakeVisible(thisSlider);
    switch (type)
    {
    case 0:
        thisSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        thisSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
        thisSlider.setColour(juce::Slider::ColourIds::backgroundColourId, setCustomColour(dark));
        thisSlider.setColour(juce::Slider::ColourIds::trackColourId, setCustomColour(purp));
        thisSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
        break;
    case 1:
        thisSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        thisSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 25);
        thisSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, setCustomColour(pink));
        thisSlider.setColour(juce::Slider::ColourIds::trackColourId, setCustomColour(dark));
        thisSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
    }
}

juce::Colour GlobalComponents::setCustomColour(const std::array<juce::uint8, 3> colourArray)
{
    return juce::Colour(colourArray[0], colourArray[1], colourArray[2]);
}

juce::Colour GlobalComponents::setCustomColourAlpha(std::array<juce::uint8, 3> colourArray, float alpha)
{
    return juce::Colour(colourArray[0], colourArray[1], colourArray[2], alpha);
}
