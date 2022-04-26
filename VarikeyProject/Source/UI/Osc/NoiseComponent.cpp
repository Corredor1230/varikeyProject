/*
  ==============================================================================

    NoiseComponent.cpp
    Created: 16 Apr 2022 12:40:25am
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "NoiseComponent.h"

//==============================================================================
NoiseComponent::NoiseComponent()
{
    addAndMakeVisible(titleLabel);
    addAndMakeVisible(toneSlider);
    addAndMakeVisible(toneLabel);
    toneSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    toneSlider.setRange(0.00, 1.00, 0.01);
    toneLabel.setText("Tone", juce::dontSendNotification);
    toneLabel.setJustificationType(juce::Justification::centred);
    toneLabel.attachToComponent(&toneSlider, false);
    toneSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
}

NoiseComponent::~NoiseComponent()
{
}

void NoiseComponent::paint (juce::Graphics& g)
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
    int sliderLabel = height / 6;
    int sliderLabelWidth = 50;
    int title = height / 6;

    int sliderWidth = width;
    int sliderHeight = height - title - sliderLabel - padding;
    int sliderDiameter = std::min(sliderWidth, sliderHeight);
    int sliderStartX = border.getCentreX() - (sliderDiameter / 2);
    int sliderStartY = title + sliderLabel + padding;

    titleLabel.setText(regionTitle + componentTitle, juce::dontSendNotification);
    titleLabel.setBounds(padding * 1.5, padding / 1.5, width, title);

    toneSlider.setBounds(sliderStartX, sliderStartY, sliderDiameter, sliderDiameter);



}

void NoiseComponent::resized()
{

}

void NoiseComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}

void NoiseComponent::setRegionTitle(juce::String& region)
{
    regionTitle = region;
}
