/*
  ==============================================================================

    PitchwheelComponent.h
    Created: 25 Apr 2022 11:36:32pm
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../VarikeyLookAndFeel.h"

//==============================================================================
/*
*/

class PitchwheelLookAndFeel : public VarikeyLookAndFeel
{
    VarikeyLookAndFeel::palette customPalette;
    PitchwheelLookAndFeel();
    ~PitchwheelLookAndFeel() override;

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos,
        float rotaryStartAngle,
        const float rotaryEndAngle,
        Slider& slider) override;
};

class PitchwheelComponent  : public juce::Component
{
public:

    enum sliderStyle {
        vertical = 0,
        rotary,
        horizontal
    };

    PitchwheelComponent();
    ~PitchwheelComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style);
    void setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel);

private:

    juce::Slider pitchwheelSlider;
    juce::Label pitchwheelLabel;

    juce::Slider vibFreqSlider;
    juce::Label vibFreqLabel;
    
    juce::Slider vibDepthSlider;
    juce::Label vibDepthLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PitchwheelComponent)
};
