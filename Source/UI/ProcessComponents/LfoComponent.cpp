/*
  ==============================================================================

    LfoComponent.cpp
    Created: 12 Apr 2022 7:33:47pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LfoComponent.h"

//==============================================================================
LfoComponent::LfoComponent(juce::AudioProcessorValueTreeState& vts) : vts(vts)
, lfoFreqAttachment(vts, "lfoFreq", lfoFreqSlider)
, lfoDepthAttachment(vts, "lfoDepth", lfoDepthSlider)
, lfoWaveAttachment(vts, "lfoWave", lfoWaveSlider)
{
    addAndMakeVisible(lfoFreqSlider);
    addAndMakeVisible(lfoDepthSlider);
    addAndMakeVisible(lfoWaveSlider);

    lfoFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfoDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfoWaveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);


}

LfoComponent::~LfoComponent()
{
}

void LfoComponent::paint (juce::Graphics& g)
{

    g.fillAll(juce::Colour::Colour());
}

void LfoComponent::resized()
{
    getBounds().reduce(10, 10);
    int width = getWidth();
    int height = getHeight();
    int sliderWidth = width;
    int sliderHeight = height / 3;
    int sliderDiameter = std::min(sliderWidth, sliderHeight);
    int sliderStartX = 0;
    int sliderStartY = 0;

    lfoFreqSlider.setBounds(sliderStartX, sliderStartY, sliderDiameter, sliderDiameter);
    lfoWaveSlider.setBounds(sliderStartX, lfoFreqSlider.getBottom(), sliderDiameter, sliderDiameter);
    lfoDepthSlider.setBounds(sliderStartX, lfoWaveSlider .getBottom(), sliderDiameter, sliderDiameter);

}
