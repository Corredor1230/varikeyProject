/*
  ==============================================================================

    KarplusComponent.cpp
    Created: 8 Apr 2022 11:36:06am
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "KarplusComponent.h"

//==============================================================================
KarplusComponent::KarplusComponent()
{
    setSliderParams(kAttSlider, kAttLabel, "Atk", vertical);
    setSliderParams(kRelSlider, kRelLabel, "Rel", vertical);
    setSliderParams(kFeedSlider, kFeedLabel, "F/B", vertical);
    setSliderParams(kNoiseSlider, kWhiteLabel, "Noise Shape", horizontal);

    addAndMakeVisible(kWhiteLabel);
    addAndMakeVisible(kPinkLabel);
    addAndMakeVisible(titleLabel);
    kWhiteLabel.setText("White", juce::sendNotification);
    kWhiteLabel.setJustificationType(juce::Justification::centred);
    kPinkLabel.setText("Pink", juce::sendNotification);
    kPinkLabel.setJustificationType(juce::Justification::centred);

    kAttSlider.setRange(1.0, 48000.0, 1.0);
    kAttSlider.setValue(1000.0);
    kAttSlider.setSkewFactor(0.5);
    kRelSlider.setRange(1.0, 48000.0, 1.0);
    kRelSlider.setValue(48000.0);
    kRelSlider.setSkewFactor(0.5);
    kFeedSlider.setRange(0.0, 1.0, 0.01);
    kFeedSlider.setValue(0.95);
    kFeedSlider.setSkewFactor(2.0);
    kNoiseSlider.setRange(0.0, 1.0, 1.0);
    kNoiseSlider.setValue(0.0);


}

KarplusComponent::~KarplusComponent()
{
}

void KarplusComponent::paint (juce::Graphics& g)
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

    int horizontalHeight = 25;
    int sliderWidth = (width / 5) - padding;
    int sliderHeight = height - title - sliderLabel;
    int sliderStartX = padding;
    int sliderStartY = title + sliderLabel;
    int labelStartX = (padding * 2) / 1.1;
    int labelStartY = title + sliderLabel + padding;
    int topStartY = 3;
    int horizontalStartY = (height / 2) - horizontalHeight;

    noiseShapeValue = kNoiseSlider.getValue();

    titleLabel.setText(regionTitle + componentTitle, juce::dontSendNotification);
    titleLabel.setBounds(padding * 1.5, padding / 1.5, width, title);
    kAttSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    kRelSlider.setBounds(kAttSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    kFeedSlider.setBounds(kRelSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

    switch (noiseShapeValue)
    {
    case 0:
        kWhiteLabel.setBounds(kFeedSlider.getRight() + padding, horizontalStartY, sliderLabelWidth, horizontalHeight);
        kPinkLabel.setBounds(0, 0, 0, 0);
        break;
    case 1:
        kPinkLabel.setBounds(kFeedSlider.getRight() + padding, horizontalStartY, sliderLabelWidth, horizontalHeight);
        kWhiteLabel.setBounds(0, 0, 0, 0);
        break;
    default:
        kPinkLabel.setBounds(kFeedSlider.getRight() + padding, horizontalStartY, sliderLabelWidth, horizontalHeight);
        kWhiteLabel.setBounds(0, 0, 0, 0);
        break;
    }
    kNoiseSlider.setBounds(kFeedSlider.getRight() + padding, horizontalStartY + horizontalHeight, sliderLabelWidth, horizontalHeight);

}

void KarplusComponent::resized()
{


}

void KarplusComponent::setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(&slider, false);

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

void KarplusComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}

void KarplusComponent::setRegionTitle(juce::String& region)
{
    regionTitle = region;
}