/*
  ==============================================================================

    NoiseComponent.h
    Created: 16 Apr 2022 12:40:25am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class NoiseComponent  : public juce::Component
{
public:
    NoiseComponent();
    ~NoiseComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel);
    void setRegionTitle(juce::String& region);

private:

    juce::Label titleLabel;
    juce::String regionTitle = "Osc 1: ";
    juce::String componentTitle = "Noise Synth";

    juce::Slider toneSlider;

    juce::Label toneLabel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseComponent)
};
