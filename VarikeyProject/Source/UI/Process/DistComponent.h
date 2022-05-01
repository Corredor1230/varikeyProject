/*
  ==============================================================================

    DistComponent.h
    Created: 30 Apr 2022 2:32:30pm
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DistComponent  : public juce::Component
{
public:

    enum sliderStyle {
        vertical = 0,
        rotary,
        horizontal
    };

    DistComponent(juce::AudioProcessorValueTreeState& vts, juce::String inputID, juce::String outputID,
        juce::String toggleID);
    ~DistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setSliderParams(juce::Slider& slider, juce::Label& label, juce::String name, int style);
    void setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel);

private:

    juce::AudioProcessorValueTreeState& vts;
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

    juce::Label titleLabel = "Distortion";
    juce::Label inputLabel;
    juce::Label outputLabel;

    juce::ToggleButton distToggle;
    juce::Label distToggleLabel;

    juce::Slider inputSlider;
    juce::Slider outputSlider;

    SliderAttachment inputAttachment;
    SliderAttachment outputAttachment;
    ButtonAttachment distToggleAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistComponent)
};
