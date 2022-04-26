/*
  ==============================================================================

    FilterComponent.cpp
    Created: 8 Apr 2022 11:36:45am
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent()
{
    addAndMakeVisible(titleLabel);
    titleLabel.setText("Filter", juce::dontSendNotification);

    setSliderParams(lopCutoffSlider, lopCutoffLabel, "Cutoff", rotary);
    lopCutoffSlider.setRange(20.0, 20000.0f, 1.0f);
    lopCutoffSlider.setSkewFactorFromMidPoint(1000.0f);
    setSliderParams(hipCutoffSlider, hipCutoffLabel, "Cutoff", rotary);
    hipCutoffSlider.setRange(20.0f, 20000.0f, 1.0f);

    addAndMakeVisible(lopToggle);
    addAndMakeVisible(hipToggle);
    addAndMakeVisible(lopToggleLabel);
    addAndMakeVisible(hipToggleLabel);
    addAndMakeVisible(lopLabel);
    addAndMakeVisible(hipLabel);
    lopLabel.setText("Low-Pass", juce::dontSendNotification);
    hipLabel.setText("Hi-Pass", juce::dontSendNotification);
    lopToggleLabel.setText("On/Off", juce::sendNotification);
    hipToggleLabel.setText("On/Off", juce::sendNotification);

    lopToggle.setToggleState(true, juce::sendNotification);
    hipToggle.setToggleState(false, juce::sendNotification);

    hipCutoffSlider.setSkewFactorFromMidPoint(1000.0f);
    setSliderParams(lopQSlider, lopQLabel, "Q", rotary);
    lopQSlider.setRange(1.0f, 10.0f, 0.1f);
    setSliderParams(hipQSlider, hipQLabel, "Q", rotary);
    hipQSlider.setRange(1.0f, 10.0f, 0.1f);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
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
    int topStartY = 3;
    int title = 18;
    int sliderLabelWidth = width / 5;
    int sliderLabelHeight = height / 4;

    int sliderWidth = (width / 3) - padding;
    int sliderHeight = (height / 2.5) - title;
    int sliderDiameter = std::min(sliderWidth, sliderHeight);

    int sliderStartX = padding * 1.5;
    int sliderStartY = title + sliderLabelHeight;


    titleLabel.setBounds(sliderStartX, padding / 1.5, width, title);

    lopLabel.setBounds(sliderStartX, titleLabel.getBottom() - padding, 2 * sliderLabelWidth, sliderLabelHeight);
    lopToggle.setBounds(lopLabel.getRight(), titleLabel.getBottom() - padding, sliderLabelWidth, sliderLabelHeight);
    lopToggleLabel.setBounds(lopToggle.getRight() - padding, titleLabel.getBottom() - padding, sliderLabelWidth + padding, sliderLabelHeight);

    int lopStartY = lopLabel.getBottom() - 2 * padding;
    lopCutoffSlider.setBounds(sliderStartX + sliderLabelWidth, lopStartY, sliderWidth, sliderHeight);
    lopQSlider.setBounds(lopCutoffSlider.getRight() + 3 * padding, lopStartY, sliderWidth, sliderHeight);


    hipLabel.setBounds(sliderStartX, lopCutoffSlider.getBottom() - padding, 2 * sliderLabelWidth, sliderLabelHeight);
    hipToggle.setBounds(hipLabel.getRight(), lopCutoffSlider.getBottom() - padding, sliderLabelWidth, sliderLabelHeight);
    hipToggleLabel.setBounds(hipToggle.getRight() - padding, lopCutoffSlider.getBottom() - padding, sliderLabelWidth + padding, sliderLabelHeight);

    int hipStartY = hipLabel.getBottom() - 2 * padding;
    hipCutoffSlider.setBounds(sliderStartX + sliderLabelWidth, hipStartY, sliderWidth, sliderHeight);
    hipQSlider.setBounds(hipCutoffSlider.getRight() + 3 * padding, hipStartY, sliderWidth, sliderHeight);


    juce::Colour toggleOff = getLookAndFeel().findColour(juce::ToggleButton::ColourIds::tickDisabledColourId);
    juce::Colour toggleOn = getLookAndFeel().findColour(juce::Slider::ColourIds::textBoxTextColourId);
    //juce::Colour toggleOn = getLookAndFeel().findColour(juce::ToggleButton::ColourIds::tickColourId);

    switch (lopToggle.getToggleState())
    {
    case 0:
        lopCutoffSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, toggleOff);
        lopCutoffLabel.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        lopQSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, toggleOff);
        lopQLabel.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        lopLabel.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        lopToggle.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, toggleOff);
        lopToggleLabel.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        break;
    case 1:
        lopCutoffSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, toggleOn);
        lopCutoffLabel.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        lopQSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, toggleOn);
        lopQLabel.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        lopLabel.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        lopToggle.setColour(juce::ToggleButton::ColourIds::tickColourId, toggleOn);
        lopToggle.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, toggleOn);
        lopToggleLabel.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        break;
    }

    switch (hipToggle.getToggleState())
    {
    case 0:
        hipCutoffSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, toggleOff);
        hipCutoffLabel.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        hipQSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, toggleOff);
        hipQLabel.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        hipLabel.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        hipToggle.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, toggleOff);
        hipToggleLabel.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        break;
    case 1:
        hipCutoffSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, toggleOn);
        hipCutoffLabel.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        hipQSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, toggleOn);
        hipQLabel.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        hipLabel.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        hipToggle.setColour(juce::ToggleButton::ColourIds::tickColourId, toggleOn);
        hipToggle.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, toggleOn);
        hipToggleLabel.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        break;
    }

    //lopCutoffLabel.setBounds(sliderStartX, lopLabel.getBottom() - 3 * padding, sliderLabelWidth, sliderLabelHeight);



    
}

void FilterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void FilterComponent::setSliderParams(juce::Slider& slider, juce::Label& label, juce::String name, int style)
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
        label.setJustificationType(juce::Justification::centred);
        label.attachToComponent(&slider, true);
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

void FilterComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}
