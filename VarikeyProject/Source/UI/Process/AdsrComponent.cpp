/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 8 Apr 2022 11:36:36am
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent()
{
    setSliderParams(attackSlider, attackLabel, "A", vertical);
    setSliderParams(decaySlider, decayLabel, "D", vertical);
    setSliderParams(sustainSlider, sustainLabel, "S", vertical);
    setSliderParams(releaseSlider, releaseLabel, "R", vertical);
    addAndMakeVisible(titleLabel);

    titleLabel.setText("Amp ADSR", juce::dontSendNotification);
    attackSlider.setRange(0.0, maximumSliderValue, sliderInterval);
    attackSlider.setSkewFactorFromMidPoint(sliderSkewFromMid);
    decaySlider.setRange(0.0, maximumSliderValue, sliderInterval);
    decaySlider.setSkewFactorFromMidPoint(sliderSkewFromMid);
    sustainSlider.setRange(0.0, 1.0, 0.1);
    releaseSlider.setRange(0.0, maximumSliderValue, sliderInterval);
    releaseSlider.setSkewFactorFromMidPoint(sliderSkewFromMid);


}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
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
    int titleHeight = height / 6;
    int sliderLabelHeight = height / 6;
    int sliderLabelWidth = 50;

    int sliderWidth = (width / 4) - padding;
    int sliderHeight = height - titleHeight - sliderLabelHeight;

    int sliderStartX = padding;

    titleLabel.setBounds(padding * 1.5, padding / 1.5, width, titleHeight);

    int labelStartY = titleLabel.getBottom();
    attackLabel.setBounds(sliderStartX, labelStartY, sliderWidth, titleHeight);
    decayLabel.setBounds(attackLabel.getRight() + padding, labelStartY, sliderWidth, titleHeight);
    sustainLabel.setBounds(decayLabel.getRight() + padding, labelStartY, sliderWidth, titleHeight);
    releaseLabel.setBounds(sustainLabel.getRight() + padding, labelStartY, sliderWidth, titleHeight);


    int sliderStartY = attackLabel.getBottom() - padding / 2;
    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

}

void AdsrComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void AdsrComponent::setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    switch (style)
    {
    case vertical:
        label.attachToComponent(&slider, false);
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        break;
    case rotary:
        label.attachToComponent(&slider, false);
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
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

void AdsrComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}