/*
  ==============================================================================

    TuningComponent.cpp
    Created: 24 Mar 2022 5:26:11am
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TuningComponent.h"

//==============================================================================
TuningComponent::TuningComponent(juce::AudioProcessorValueTreeState& vts)
{
    cAttachment = std::make_unique<SliderAttachment>(vts, "c", cSlider);
    cesAttachment = std::make_unique<SliderAttachment>(vts, "ces", cesSlider);
    dAttachment = std::make_unique<SliderAttachment>(vts, "d", dSlider);
    desAttachment = std::make_unique<SliderAttachment>(vts, "des", desSlider);
    eAttachment = std::make_unique<SliderAttachment>(vts, "e", eSlider);
    fAttachment = std::make_unique<SliderAttachment>(vts, "f", fSlider);
    fesAttachment = std::make_unique<SliderAttachment>(vts, "fes", fesSlider);
    gAttachment = std::make_unique<SliderAttachment>(vts, "g", gSlider);
    gesAttachment = std::make_unique<SliderAttachment>(vts, "ges", gesSlider);
    aAttachment = std::make_unique<SliderAttachment>(vts, "a", aSlider);
    aesAttachment = std::make_unique<SliderAttachment>(vts, "aes", aesSlider);
    bAttachment = std::make_unique<SliderAttachment>(vts, "b", bSlider);

    buildSlider(cSlider, clabel, white, "0");
    buildSlider(cesSlider, ceslabel, black, "1");
    buildSlider(dSlider, dlabel, white, "2");
    buildSlider(desSlider, deslabel, black, "3");
    buildSlider(eSlider, elabel, white, "4");
    buildSlider(fSlider, flabel, white, "5");
    buildSlider(fesSlider, feslabel, black, "6");
    buildSlider(gSlider, glabel, white, "7");
    buildSlider(gesSlider, geslabel, black, "8");
    buildSlider(aSlider, alabel, white, "9");
    buildSlider(aesSlider, aeslabel, black, "10");
    buildSlider(bSlider, blabel, white, "11");
}

TuningComponent::~TuningComponent()
{
}



void TuningComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);
}

void TuningComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 5;
    const auto labelWidth = bounds.getWidth() / 12 - padding;
    const auto labelHeight = bounds.getHeight() / 7;
    const auto sliderWidth = bounds.getWidth() / 12 - padding;
    const auto sliderHeight = bounds.getHeight() - labelHeight;
    const auto sliderStartX = 0;
    const auto sliderStartY = 0 + labelHeight;
    const auto labelStartY = 0;

    cSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    cesSlider.setBounds(cSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    dSlider.setBounds(cesSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    desSlider.setBounds(dSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    eSlider.setBounds(desSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    fSlider.setBounds(eSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    fesSlider.setBounds(fSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    gSlider.setBounds(fesSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    gesSlider.setBounds(gSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    aSlider.setBounds(gesSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    aesSlider.setBounds(aSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    bSlider.setBounds(aesSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

    clabel.setBounds(sliderStartX, labelStartY, labelWidth, labelHeight);
    ceslabel.setBounds(clabel.getRight() + padding, labelStartY, labelWidth, labelHeight);
    dlabel.setBounds(ceslabel.getRight() + padding, labelStartY, labelWidth, labelHeight);
    deslabel.setBounds(dlabel.getRight() + padding, labelStartY, labelWidth, labelHeight);
    elabel.setBounds(deslabel.getRight() + padding, labelStartY, labelWidth, labelHeight);
    flabel.setBounds(elabel.getRight() + padding, labelStartY, labelWidth, labelHeight);
    feslabel.setBounds(flabel.getRight() + padding, labelStartY, labelWidth, labelHeight);
    glabel.setBounds(feslabel.getRight() + padding, labelStartY, labelWidth, labelHeight);
    geslabel.setBounds(glabel.getRight() + padding, labelStartY, labelWidth, labelHeight);
    alabel.setBounds(geslabel.getRight() + padding, labelStartY, labelWidth, labelHeight);
    aeslabel.setBounds(alabel.getRight() + padding, labelStartY, labelWidth, labelHeight);
    blabel.setBounds(aeslabel.getRight() + padding, labelStartY, labelWidth, labelHeight);

}

void TuningComponent::buildSlider(juce::Slider& slider, juce::Label& label, keyColor color, const std::string& name)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    slider.setRange(-1.0, 1.0, 0.01);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    switch (color)
    {
    case 0:
        slider.setColour(juce::Slider::backgroundColourId, juce::Colour(0, 0, 0));
        slider.setColour(juce::Slider::trackColourId, juce::Colour(0, 0, 0));
        slider.setColour(juce::Slider::thumbColourId, juce::Colour(255, 255, 255));
        break;
    case 1:
        slider.setColour(juce::Slider::backgroundColourId, juce::Colour(255, 255, 255));
        slider.setColour(juce::Slider::trackColourId, juce::Colour(255, 255, 255));
        slider.setColour(juce::Slider::thumbColourId, juce::Colour(0, 0, 0));
        slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
        break;
    }

    label.setText(name, juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::centredTop);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    label.attachToComponent(&slider, false);

}
