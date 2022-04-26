/*
  ==============================================================================

    AdditiveComponent.h
    Created: 8 Apr 2022 11:36:19am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdditiveComponent  : public juce::Component
{
public:

    enum sliderStyle {
        vertical = 0,
        rotary,
        horizontal
    };

    AdditiveComponent();
    ~AdditiveComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style);
    void setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel);
    void setRegionTitle(juce::String& region);


private:

    juce::Label titleLabel;
    juce::String regionTitle = "Osc 1: ";
    juce::String componentTitle = "Additive Synth";

    juce::Slider slider0;
    juce::Slider slider1;
    juce::Slider slider2;
    juce::Slider slider3;
    juce::Slider slider4;
    juce::Slider slider5;
    juce::Slider slider6;
    juce::Slider slider7;

    juce::Label label0;
    juce::Label label1;
    juce::Label label2;
    juce::Label label3;
    juce::Label label4;
    juce::Label label5;
    juce::Label label6;
    juce::Label label7;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdditiveComponent)
};
