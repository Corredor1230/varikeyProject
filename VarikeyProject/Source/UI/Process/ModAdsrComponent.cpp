/*
  ==============================================================================

    ModAdsrComponent.cpp
    Created: 21 Apr 2022 4:08:07am
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ModAdsrComponent.h"

//==============================================================================
ModAdsrComponent::ModAdsrComponent()
{
    setSliderParams(attackSlider, attackLabel, "A", vertical);
    setSliderParams(decaySlider, decayLabel, "D", vertical);
    setSliderParams(sustainSlider, sustainLabel, "S", vertical);
    setSliderParams(releaseSlider, releaseLabel, "R", vertical);
    addAndMakeVisible(titleLabel);
    addAndMakeVisible(routeBox);
    addAndMakeVisible(routeLabel);
    routeBox.setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour());


    titleLabel.setText("Mod", juce::dontSendNotification);
    routeLabel.setText("Route", juce::dontSendNotification);
    attackSlider.setRange(0.0, maximumSliderValue, sliderInterval);
    attackSlider.setSkewFactorFromMidPoint(sliderSkewFromMid);
    decaySlider.setRange(0.0, maximumSliderValue, sliderInterval);
    decaySlider.setSkewFactorFromMidPoint(sliderSkewFromMid);
    sustainSlider.setRange(0.0, 1.0, 0.1);
    releaseSlider.setRange(0.0, maximumSliderValue, sliderInterval);
    releaseSlider.setSkewFactorFromMidPoint(sliderSkewFromMid);

    std::initializer_list<const char*> synthList
    {
        "none",
        "gen1Noise", "gen2Noise",
        "noise1Tone", "noise2Tone",
        "mix",
        "fm1Ratio", "fm1Depth",
        "fm2Ratio", "fm2Depth",
        "lopCutoff", "lopQ",
        "hipCutoff", "hipQ",
        "detune", "vibFreq", "vibDepth",
        "volume"
    };
    routeBox.addItemList(juce::StringArray(synthList), 1);


}

ModAdsrComponent::~ModAdsrComponent()
{
}

void ModAdsrComponent::paint(juce::Graphics& g)
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
    int titleHeight = height / 5.5;
    int sliderLabelHeight = height / 6;
    int sliderLabelWidth = 50;

    int sliderWidth = (width / 4) - padding;
    int sliderHeight = height - titleHeight - sliderLabelHeight;

    int sliderStartX = padding;

    titleLabel.setBounds(padding * 1.5, padding / 1.5, width / 2, titleHeight);
    routeLabel.setBounds(width / 2, padding / 1.5, width / 4, titleHeight);
    routeBox.setBounds(routeLabel.getRight() + padding / 2, padding, width / 5, titleHeight - padding / 2);

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

void ModAdsrComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void ModAdsrComponent::setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style)
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

void ModAdsrComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}