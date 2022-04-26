/*
  ==============================================================================

    TuningComponent.cpp
    Created: 8 Apr 2022 11:35:01am
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TuningComponent.h"

//==============================================================================
TuningComponent::TuningComponent()
{
    //transposeTextBoxWidth = getWidth() / 12;
    //transposeTextBoxHeight = getHeight() / 6;
    addAndMakeVisible(transposeSlider);
    transposeSlider.setRange(0.0, 11.0, 1.0);
    transposeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    transposeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,
        false, 25, 25);

    addAndMakeVisible(keyBreakToggle);
    keyBreakToggle.setName("Key Break Toggle");

    addAndMakeVisible(transposeLabel);
    transposeLabel.setText("Transpose", juce::dontSendNotification);
    transposeLabel.attachToComponent(&transposeSlider, true);

    addAndMakeVisible(titleLabel);
    titleLabel.setText("Note Tuning", juce::dontSendNotification);

    addAndMakeVisible(keyBreakLabel);
    keyBreakLabel.setText("Bass controls tuning", juce::dontSendNotification);

    addAndMakeVisible(keyBreakValue);
    addAndMakeVisible(valueOutline);
    keyBreakValue.setEditable(true);
    //keyBreakValue.setColour(juce::Label::ColourIds::outlineColourId, 
    //    slider0.findColour(juce::Slider::ColourIds::trackColourId));
    keyBreakValue.setText("48", juce::dontSendNotification);
    keyBreakValue.setJustificationType(juce::Justification::centredLeft);

    setSliderParams(slider0, label0, "0", vertical);
    setSliderParams(slider1, label1, "1", vertical);
    setSliderParams(slider2, label2, "2", vertical);
    setSliderParams(slider3, label3, "3", vertical);
    setSliderParams(slider4, label4, "4", vertical);
    setSliderParams(slider5, label5, "5", vertical);
    setSliderParams(slider6, label6, "6", vertical);
    setSliderParams(slider7, label7, "7", vertical);
    setSliderParams(slider8, label8, "8", vertical);
    setSliderParams(slider9, label9, "9", vertical);
    setSliderParams(slider10, label10, "10", vertical);
    setSliderParams(slider11, label11, "11", vertical);

}

TuningComponent::~TuningComponent()
{
}

void TuningComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour());
    //juce::Rectangle<float> border;
    //border.setBounds(5, 5, getWidth() - 10, getHeight() - 10);
    g.setColour(slider0.findColour(juce::ToggleButton::ColourIds::tickDisabledColourId));
    juce::Line<float> line(juce::Point<float>(5, 0), juce::Point<float>(getRight() - 5, 0));
    g.drawLine(line);
    //g.drawRect(border, 1.0f);

    juce::Colour toggleOff = getLookAndFeel().findColour(juce::ToggleButton::ColourIds::tickDisabledColourId);
    juce::Colour toggleOn = getLookAndFeel().findColour(juce::ToggleButton::ColourIds::tickColourId);

    switch (keyBreakToggle.getToggleState())
    {
    case 0:

        keyBreakLabel.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        keyBreakValue.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        keyBreakToggle.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, toggleOff);
        break;
    case 1:
        keyBreakLabel.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        keyBreakValue.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        keyBreakToggle.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, toggleOn);
        break;
    }
}

void TuningComponent::resized()
{
    auto bounds = getBounds().reduced(5, 5);
    int height = bounds.getHeight();
    int width = bounds.getWidth();
    int padding = 10;
    int sliderLabel = height / 7;
    int title = height / 6;
    int sliderWidth = (width / 12) - padding;
    int sliderStartX = padding;
    int sliderStartY = title + sliderLabel;

    transposeTextBoxWidth = sliderWidth*2;
    transposeTextBoxHeight = height / 6;
    int labelStartX = (padding * 2) / 1.1;
    int topStartY = 3;
    int transposeHeight = height / 6;
    int transposeWidth = width - transposeTextBoxWidth - labelStartX - padding - 1;
    int transposeStartX = sliderStartX + padding + transposeTextBoxWidth;
    int transposeStartY = 3 * (height / 4);

    int sliderHeight = height - title - sliderLabel - transposeHeight;

    slider0.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    slider1.setBounds(slider0.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider2.setBounds(slider1.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider3.setBounds(slider2.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider4.setBounds(slider3.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider5.setBounds(slider4.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider6.setBounds(slider5.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider7.setBounds(slider6.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider8.setBounds(slider7.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider9.setBounds(slider8.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider10.setBounds(slider9.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider11.setBounds(slider10.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    transposeSlider.setBounds(transposeStartX, slider0.getBottom(), transposeWidth, transposeHeight);
    titleLabel.setBounds(labelStartX, topStartY, transposeTextBoxWidth, transposeTextBoxHeight);
    keyBreakToggle.setBounds(titleLabel.getRight() + sliderWidth, topStartY + 2, padding * 3, transposeTextBoxHeight);
    keyBreakLabel.setBounds(keyBreakToggle.getRight(), topStartY, sliderWidth * 3.5, transposeTextBoxHeight);
    keyBreakLabel.setJustificationType(juce::Justification::centredLeft);
    keyBreakValue.setBounds(keyBreakLabel.getRight(), topStartY, sliderWidth, transposeTextBoxHeight);
    transposeLabel.setBounds(labelStartX, slider0.getBottom() - 2, transposeTextBoxWidth, transposeTextBoxHeight);
    transposeLabel.setJustificationType(juce::Justification::centredLeft);
}

void TuningComponent::setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setNormalisableRange(juce::NormalisableRange<double>(-1.0, 1.0, 0.01));
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

void TuningComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}

void TuningComponent::setFont(juce::Font& font)
{
    customFont = font;
}
