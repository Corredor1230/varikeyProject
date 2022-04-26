/*
  ==============================================================================

    PitchwheelComponent.cpp
    Created: 25 Apr 2022 11:36:32pm
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PitchwheelComponent.h"

//==============================================================================

PitchwheelLookAndFeel::PitchwheelLookAndFeel()
{
}

PitchwheelLookAndFeel::~PitchwheelLookAndFeel()
{
}

void PitchwheelLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
    auto fill = slider.findColour(Slider::rotarySliderFillColourId);

    auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(3);

    auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = jmin(8.0f, radius * 0.3f);
    auto arcRadius = radius - lineW * 0.5f;
    auto centreX = width / 2;
    auto centreY = height / 2;

    Path backgroundArc;
    backgroundArc.addCentredArc(bounds.getCentreX(),
        bounds.getCentreY(),
        arcRadius,
        arcRadius,
        0.0f,
        rotaryStartAngle,
        rotaryEndAngle,
        true);

    g.setColour(outline);
    g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));

    if (slider.isEnabled())
    {
        Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            toAngle,
            true);

        g.setColour(fill);
        g.strokePath(valueArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));
    }

    auto thumbWidth = lineW * 2.4;
    auto thumbHeight = lineW;

    g.setColour(slider.findColour(Slider::ColourIds::thumbColourId));
    Path thumbTick;
    thumbTick.addRectangle(-thumbHeight / 2, -radius - lineW / 2, thumbHeight, thumbWidth);
    g.fillPath(thumbTick, AffineTransform::rotation(toAngle).translated(bounds.getCentreX(), bounds.getCentreY()));
}

PitchwheelComponent::PitchwheelComponent()
{
    setSliderParams(pitchwheelSlider, pitchwheelLabel, "Detune", horizontal);
    pitchwheelSlider.setRange(-1.0, 1.0, 0.01);

    setSliderParams(vibFreqSlider, vibFreqLabel, "Vibrato Frequency", rotary);
    vibFreqSlider.setRange(0.0, 20.0, 0.1);
    setSliderParams(vibDepthSlider, vibDepthLabel, "Depth", rotary);
    vibDepthSlider.setRange(0.0, 1.0, 0.01);
}

PitchwheelComponent::~PitchwheelComponent()
{
}

void PitchwheelComponent::paint (juce::Graphics& g)
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
    int sliderLabelHeight = height / 3;
    int sliderLabelWidth = 50;
    int labelStartY = padding / 2;

    int sliderWidth = width / 3;
    int sliderHeight = height;

    int sliderStartX = padding;

    pitchwheelLabel.setBounds(sliderStartX, labelStartY, sliderWidth, sliderLabelHeight);
    pitchwheelSlider.setBounds(sliderStartX, pitchwheelLabel.getBottom() + padding / 2, sliderWidth, sliderHeight / 2);

    vibFreqLabel.setBounds(pitchwheelLabel.getRight(), labelStartY, sliderWidth, sliderLabelHeight);
    vibFreqSlider.setBounds(pitchwheelSlider.getRight(), pitchwheelLabel.getBottom() - padding, sliderWidth, sliderHeight);

    vibDepthLabel.setBounds(vibFreqLabel.getRight(), labelStartY, sliderWidth, sliderLabelHeight);
    vibDepthSlider.setBounds(vibFreqSlider.getRight(), pitchwheelLabel.getBottom() - padding, sliderWidth, sliderHeight);
}

void PitchwheelComponent::resized()
{

}

void PitchwheelComponent::setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 70, 20);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    switch (style)
    {
    case vertical:
        label.attachToComponent(&slider, false);
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        break;
    case rotary:
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        break;
    case horizontal:
        slider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 25);
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
        break;
    default:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
        break;
    }
}

void PitchwheelComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}