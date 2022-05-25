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
ModAdsrComponent::ModAdsrComponent(juce::AudioProcessorValueTreeState& vts) : vts(vts)
, attackAttachment(vts, "modAdsrAtt", attackSlider)
, decayAttachment(vts, "modAdsrDec", decaySlider)
, sustainAttachment(vts, "modAdsrSus", sustainSlider)
, releaseAttachment(vts, "modAdsrRel", releaseSlider)
, routeAttachment(vts, "modAdsrRoute", routeBox)
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
    //attackSlider.setRange(0.0, maximumSliderValue, sliderInterval);
    //attackSlider.setSkewFactorFromMidPoint(sliderSkewFromMid);
    //decaySlider.setRange(0.0, maximumSliderValue, sliderInterval);
    //decaySlider.setSkewFactorFromMidPoint(sliderSkewFromMid);
    //sustainSlider.setRange(0.0, 1.0, 0.1);
    //releaseSlider.setRange(0.0, maximumSliderValue, sliderInterval);
    //releaseSlider.setSkewFactorFromMidPoint(sliderSkewFromMid);

    std::initializer_list<const char*> synthList
    {
        "none",
        "gen1Noise", "gen2Noise",
        "noise1Tone", "noise2Tone",
        "mix",
        "distInLeft", "distOutLeft",
        "distOutLeft", "distOutRight",
        "lopCutoff", "lopQ",
        "hipCutoff", "hipQ",
        "detune", "vibFreq", "vibDepth",
        "volume"
    };
    routeBox.addItemList(juce::StringArray(synthList), 1);

    //routeBox.setSelectedId(-1, juce::NotificationType::sendNotification);
}

ModAdsrComponent::~ModAdsrComponent()
{
}

void ModAdsrComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour());
    //juce::Rectangle<float> border;
    //border.setBounds(5, 5, getWidth() - 10, getHeight() - 10);
    //g.setColour(getLookAndFeel().findColour(juce::ToggleButton::ColourIds::tickDisabledColourId));
    //g.drawRect(border, 1.0f);

    auto bounds = getBounds().reduced(5, 5);
    int height = bounds.getHeight();
    int width = bounds.getWidth();
    int padding = 10;
    int titleHeight = height / 5.5;
    int sliderLabelHeight = height / 6;

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

    setUsedRoutes();
    setDisabledRoutes(routeBox);

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

void ModAdsrComponent::updateRoutes(int lfo1Route, int lfo2Route, int lfo3Route, int lfo4Route, int modAdsrRoute)
{
    lfo1R = lfo1Route + 1;
    lfo2R = lfo2Route + 1;
    lfo3R = lfo3Route + 1;
    lfo4R = lfo4Route + 1;
    modAR = modAdsrRoute + 1;
    routeBox.setSelectedId(modAR);
}

void ModAdsrComponent::setUsedRoutes()
{
    if(usedRoutes[0] != lfo1R) routeBox.setItemEnabled(usedRoutes[0], true);
    if(usedRoutes[1] != lfo2R) routeBox.setItemEnabled(usedRoutes[1], true);
    if(usedRoutes[2] != lfo3R) routeBox.setItemEnabled(usedRoutes[2], true);
    if(usedRoutes[3] != lfo4R) routeBox.setItemEnabled(usedRoutes[3], true);
    usedRoutes[0] = lfo1R;
    usedRoutes[1] = lfo2R;
    usedRoutes[2] = lfo3R;
    usedRoutes[3] = lfo4R;
}

void ModAdsrComponent::setDisabledRoutes(juce::ComboBox& box)
{
    for(int i = 0; i < 4; i++)
    {
        if(usedRoutes[i] != 0) box.setItemEnabled(usedRoutes[i], false);
    }

}
