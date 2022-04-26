/*
  ==============================================================================

    GenComponent.cpp
    Created: 16 Apr 2022 12:40:43am
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GenComponent.h"

//==============================================================================
GenComponent::GenComponent()
{
    setSliderParams(waveShape, waveLabel, "Wave Shape", rotary);
    setSliderParams(noiseLevel, noiseLabel, "Noise Level", vertical);
    setSliderParams(noiseShape, noiseShapeLabel, "Noise Shape", horizontal);

    addAndMakeVisible(titleLabel);
    addAndMakeVisible(whiteLabel);
    addAndMakeVisible(pinkLabel);
    whiteLabel.setText("White", juce::NotificationType::sendNotification);
    whiteLabel.setJustificationType(juce::Justification::centred);
    pinkLabel.setText("Pink", juce::NotificationType::sendNotification);
    pinkLabel.setJustificationType(juce::Justification::centred);

    waveShape.setRange(0, 3, 1);
    noiseLevel.setRange(0.00, 1.00, 0.01);
    noiseShape.setRange(0, 1, 1);
}

GenComponent::~GenComponent()
{
}

void GenComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour());
    juce::Rectangle<float> border;
    border.setBounds(5, 5, getWidth() - 10, getHeight() - 10);
    g.setColour(noiseLevel.findColour(juce::ToggleButton::ColourIds::tickDisabledColourId));
    g.drawRect(border, 1.0f);

    noiseShapeValue = noiseShape.getValue();


    auto bounds = getBounds().reduced(5, 5);
    int height = bounds.getHeight();
    int width = bounds.getWidth();

    int padding = 10;
    int sliderLabel = height / 6;
    int sliderLabelWidth = 50;
    int title = height / 6;

    int rotaryWidth = (width / 2) - padding;
    int rotaryHeight = height - sliderLabel - title;
    int rotaryDiameter = std::min(rotaryWidth, rotaryHeight) - padding;

    int horizontalHeight = 25;
    int sliderWidth = (width / 2) - padding;
    int sliderHeight = height - horizontalHeight - title - sliderLabel;
    int rotaryStartX = padding;
    int sliderStartX = width / 2;
    int labelStartX = (padding * 2) / 1.1;
    int labelStartY = title + sliderLabel + padding;
    int topStartY = 3;

    titleLabel.setText(regionTitle + componentTitle, juce::dontSendNotification);
    titleLabel.setBounds(padding * 1.5, padding / 1.5, width, title);
    waveShape.setBounds(rotaryStartX, labelStartY, rotaryDiameter, rotaryDiameter);
    noiseLevel.setBounds(waveShape.getRight() + padding, labelStartY, sliderWidth, sliderHeight);
    switch (noiseShapeValue)
    {
    case 0:
        whiteLabel.setBounds(waveShape.getRight() + padding, noiseLevel.getBottom() - padding / 1.5, sliderLabelWidth, horizontalHeight);
        pinkLabel.setBounds(0, 0, 0, 0);
        break;
    case 1:
        pinkLabel.setBounds(waveShape.getRight() + padding, noiseLevel.getBottom() - padding / 1.5, sliderLabelWidth, horizontalHeight);
        whiteLabel.setBounds(0, 0, 0, 0);
        break;
    default:
        pinkLabel.setBounds(waveShape.getRight() + padding, noiseLevel.getBottom() - padding / 1.5, sliderLabelWidth, horizontalHeight);
        whiteLabel.setBounds(0, 0, 0, 0);
        break;
    }
    noiseShape.setBounds(waveShape.getRight() + sliderLabelWidth, noiseLevel.getBottom() - padding / 2, sliderWidth - sliderLabelWidth, horizontalHeight);
}

void GenComponent::resized()
{
    //auto bounds = getBounds().reduced(5, 5);
    //int height = bounds.getHeight();
    //int width = bounds.getWidth();

    //int padding = 10;
    //int sliderLabel = height / 6;
    //int sliderLabelWidth = 50;
    //int title = height / 6;

    //int rotaryWidth = (width / 2) - padding ;
    //int rotaryHeight = height - sliderLabel - title;
    //int rotaryDiameter = std::min(rotaryWidth, rotaryHeight) - padding;

    //int horizontalHeight = 25;
    //int sliderWidth = (width / 2) - padding;
    //int sliderHeight = height - horizontalHeight - title - sliderLabel;
    //int rotaryStartX = padding;
    //int sliderStartX = width / 2;
    //int labelStartX = (padding * 2) / 1.1;
    //int labelStartY = title + sliderLabel + padding;
    //int topStartY = 3;

    //titleLabel.setText(regionTitle + componentTitle, juce::dontSendNotification);
    //titleLabel.setBounds(padding * 1.5, padding / 1.5, width, title);
    //waveShape.setBounds(rotaryStartX, labelStartY, rotaryDiameter, rotaryDiameter);
    //noiseLevel.setBounds(waveShape.getRight() + padding, labelStartY, sliderWidth, sliderHeight);
    //switch (noiseShapeValue)
    //{
    //case 0:
    //    whiteLabel.setBounds(waveShape.getRight() + padding, noiseLevel.getBottom() - padding / 1.5, sliderLabelWidth, horizontalHeight);
    //    pinkLabel.setBounds(0, 0, 0, 0);
    //    break;
    //case 1:
    //    pinkLabel.setBounds(waveShape.getRight() + padding, noiseLevel.getBottom() - padding / 1.5, sliderLabelWidth, horizontalHeight);
    //    whiteLabel.setBounds(0, 0, 0, 0);
    //    break;
    //default:
    //    pinkLabel.setBounds(waveShape.getRight() + padding, noiseLevel.getBottom() - padding / 1.5, sliderLabelWidth, horizontalHeight);
    //    whiteLabel.setBounds(0, 0, 0, 0);
    //    break;
    //}
    //pinkLabel.setBounds(waveShape.getRight() + padding, noiseLevel.getBottom() - padding / 1.5, sliderLabelWidth, horizontalHeight);
    //whiteLabel.setBounds(waveShape.getRight() + padding, noiseLevel.getBottom() - padding / 1.5, sliderLabelWidth, horizontalHeight);
    //noiseShape.setBounds(waveShape.getRight() + sliderLabelWidth, noiseLevel.getBottom() - padding / 2, sliderWidth - sliderLabelWidth, horizontalHeight);

}

void GenComponent::setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    //label.attachToComponent(&slider, false);

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

void GenComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}

void GenComponent::setRegionTitle(juce::String& region)
{
    regionTitle = region;
}