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
    g.fillAll(juce::Colour());
}

void TuningComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 5;
    const auto vertOffset = bounds.getHeight() / 8;
    const auto labelWidth = bounds.getWidth() / 12 - padding;
    const auto labelHeight = bounds.getHeight() / 8;
    const auto sliderWidth = bounds.getWidth() / 12 - padding;
    const auto sliderHeight = bounds.getHeight() - labelHeight - vertOffset;
    const auto sliderStartX = 0;
    const auto whiteStartY = 0 + labelHeight;
    const auto blackStartY = 0 + labelHeight;
    const auto labelStartY = 0;

    cSlider.setBounds(sliderStartX, whiteStartY, sliderWidth, sliderHeight);
    cesSlider.setBounds(cSlider.getRight() + padding, blackStartY, sliderWidth, sliderHeight);
    dSlider.setBounds(cesSlider.getRight() + padding, whiteStartY, sliderWidth, sliderHeight);
    desSlider.setBounds(dSlider.getRight() + padding, blackStartY, sliderWidth, sliderHeight);
    eSlider.setBounds(desSlider.getRight() + padding, whiteStartY, sliderWidth, sliderHeight);
    fSlider.setBounds(eSlider.getRight() + padding, whiteStartY, sliderWidth, sliderHeight);
    fesSlider.setBounds(fSlider.getRight() + padding, blackStartY, sliderWidth, sliderHeight);
    gSlider.setBounds(fesSlider.getRight() + padding, whiteStartY, sliderWidth, sliderHeight);
    gesSlider.setBounds(gSlider.getRight() + padding, blackStartY, sliderWidth, sliderHeight);
    aSlider.setBounds(gesSlider.getRight() + padding, whiteStartY, sliderWidth, sliderHeight);
    aesSlider.setBounds(aSlider.getRight() + padding, blackStartY, sliderWidth, sliderHeight);
    bSlider.setBounds(aesSlider.getRight() + padding, whiteStartY, sliderWidth, sliderHeight);

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
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setRange(-1.0, 1.0, 0.01);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 55, 15);
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour());
    switch (color)
    {
    case 0:
        slider.setColour(juce::Slider::backgroundColourId, setCustomColour(dark));
        slider.setColour(juce::Slider::trackColourId, setCustomColour(dark));
        slider.setColour(juce::Slider::thumbColourId, juce::Colours::white);
        slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::white);
        break;
    case 1:
        slider.setColour(juce::Slider::backgroundColourId, setCustomColour(teal));
        slider.setColour(juce::Slider::trackColourId, setCustomColour(teal));
        slider.setColour(juce::Slider::thumbColourId, juce::Colours::white);
        slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::white);
        break;
    }

    label.setText(name, juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::centredTop);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.attachToComponent(&slider, false);

}

juce::Colour TuningComponent::setCustomColour(const std::array<juce::uint8, 3> colourArray)
{
    return juce::Colour(colourArray[0], colourArray[1], colourArray[2]);
}

juce::Colour TuningComponent::setCustomColourAlpha(std::array<juce::uint8, 3> colourArray, float alpha)
{
    return juce::Colour(colourArray[0], colourArray[1], colourArray[2], alpha);
}
