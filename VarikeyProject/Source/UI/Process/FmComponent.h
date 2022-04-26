/*
  ==============================================================================

    FmComponent.h
    Created: 20 Apr 2022 12:59:36pm
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FmComponent  : public juce::Component
{
public:

    enum sliderStyle {
        vertical = 0,
        rotary,
        horizontal
    };

    FmComponent();
    ~FmComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setSliderParams(juce::Slider& slider, juce::Label& label, juce::String name, int style);
    void setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel);

private:

    juce::Label titleLabel = "FM Mod";
    juce::Label ratioLabel;
    juce::Label depthLabel;

    juce::Slider ratioSlider;
    juce::Slider depthSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FmComponent)
};
