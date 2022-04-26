/*
  ==============================================================================

    GenComponent.h
    Created: 16 Apr 2022 12:40:43am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GenComponent  : public juce::Component
{
public:

    enum sliderStyle {
        vertical = 0,
        rotary,
        horizontal
    };

    GenComponent();
    ~GenComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style);
    void setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel);
    void setRegionTitle(juce::String& region);

private:

    juce::Label titleLabel;
    juce::String regionTitle = "Osc 1: ";
    juce::String componentTitle = "Generator Synth";
    int noiseShapeValue = 1;


    juce::Slider waveShape;
    juce::Slider noiseLevel;
    juce::Slider noiseShape;

    juce::Label waveLabel;
    juce::Label noiseLabel;
    juce::Label noiseShapeLabel;
    juce::Label pinkLabel;
    juce::Label whiteLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenComponent)
};
