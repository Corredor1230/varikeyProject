/*
  ==============================================================================

    KarplusComponent.cpp
    Created: 31 Mar 2022 4:24:03am
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "KarplusComponent.h"

//==============================================================================
KarplusComponent::KarplusComponent(juce::AudioProcessorValueTreeState& vts)
{

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    kAttAttachment = std::make_unique<SliderAttachment>(vts, "kAtt", kAttSlider);
    kRelAttachment = std::make_unique<SliderAttachment>(vts, "kRel", kRelSlider);
    kSwitchAttachment = std::make_unique<SliderAttachment>(vts, "kSwitch", kSwitchSlider);
    kFeedAttachment = std::make_unique<SliderAttachment>(vts, "kFeed", kFeedSlider);
    fmDepthAttachment = std::make_unique<SliderAttachment>(vts, "fmDepth", fmDepthSlider);
    fmIndexAttachment = std::make_unique<SliderAttachment>(vts, "fmIndex", fmIndexSlider);

    sliderParams(kAttSlider, isSlider, kAttLabel, "A");
    sliderParams(kRelSlider, isSlider, kRelLabel, "R");
    sliderParams(kFeedSlider, isSlider, kFeedLabel, "FB");
    sliderParams(kSwitchSlider, isKnob, kSwitchLabel, "Osc");
    sliderParams(fmDepthSlider, isKnob, fmDepthLabel, "Depth");
    sliderParams(fmIndexSlider, isKnob, fmIndexLabel, "Ratio");


}

KarplusComponent::~KarplusComponent()
{
}

void KarplusComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour());
}

void KarplusComponent::resized()
{
    //Component variables
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto regionWidth = bounds.getWidth() / 2;
    const auto regionHeight = bounds.getHeight();


    const auto labelHeight = regionHeight / 8;
    const auto sliderWidth = regionWidth / 3 - padding;
    const auto sliderHeight = regionHeight - labelHeight;
    const auto knobWidth = regionWidth / 2;
    const auto knobHeight = regionHeight / 2;
    const auto knobRadius = std::min(knobWidth, knobHeight);
    const auto sliderStartX = 0;
    const auto sliderStartY = labelHeight;
    const auto knobStartX = regionWidth;
    const auto knobStartY = labelHeight;

    kAttSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    kRelSlider.setBounds(kAttSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    kFeedSlider.setBounds(kRelSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    kSwitchSlider.setBounds(knobStartX, knobStartY + regionHeight / 3, knobRadius, knobRadius);
    fmDepthSlider.setBounds(kSwitchSlider.getRight(), knobStartY, knobRadius, knobRadius);
    fmIndexSlider.setBounds(kSwitchSlider.getRight(), 2 * (regionHeight / 3), knobRadius, knobRadius);
    kAttLabel.setSize(sliderWidth, labelHeight);
    kFeedLabel.setSize(sliderWidth, labelHeight);
    kRelLabel.setSize(sliderWidth, labelHeight);
    kSwitchLabel.setSize(knobRadius, labelHeight);
    fmDepthLabel.setSize(knobRadius, labelHeight);
    fmIndexLabel.setSize(knobRadius, labelHeight);
}

void KarplusComponent::sliderParams(juce::Slider& slider, styleEnum style, juce::Label& label, const std::string& name)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    switch (style)
    {
    case KarplusComponent::isKnob:
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, setCustomColour(blue));
        slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, setCustomColour(teal));
        slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
        slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, setCustomColour(pink));
        slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

        break;
    case KarplusComponent::isSlider:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        slider.setColour(juce::Slider::ColourIds::backgroundColourId, setCustomColour(blue));
        slider.setColour(juce::Slider::ColourIds::trackColourId, setCustomColour(teal));
        slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
        slider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
        slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, setCustomColour(pink));
        break;
    }

    label.attachToComponent(&slider, false);
    label.setText(name, juce::NotificationType::dontSendNotification);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setJustificationType(juce::Justification::centred);

}

juce::Colour KarplusComponent::setCustomColour(const std::array<juce::uint8, 3> colourArray)
{
    return juce::Colour(colourArray[0], colourArray[1], colourArray[2]); 
}
