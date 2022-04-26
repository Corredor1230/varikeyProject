/*
  ==============================================================================

    LfoComponent.h
    Created: 8 Apr 2022 11:36:54am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../VarikeyLookAndFeel.h"

//==============================================================================
/*
*/

class LfoLookAndFeel : public VarikeyLookAndFeel
{
public:
    VarikeyLookAndFeel::palette customPalette;
    LfoLookAndFeel();
    ~LfoLookAndFeel() override;

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos,
        float rotaryStartAngle,
        const float rotaryEndAngle,
        Slider& slider) override;

private:
};

class LfoComponent  : public juce::Component
{
public:

    enum sliderStyle {
        vertical = 0,
        rotary,
        horizontal
    };

    LfoComponent();
    ~LfoComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setSliderParams(juce::Slider& slider, juce::Label& label, juce::String name, int style);
    void setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel);
    void setRegionTitle(juce::String& region1, juce::String& region2);


private:

    LfoLookAndFeel lfoLookAndFeel;

    juce::Label titleLabel;
    juce::Label lfo1Label;
    juce::Label lfo2Label;
    juce::String lfoString = "LFO";
    juce::String region1Index = "1";
    juce::String region2Index = "2";

    juce::ComboBox routeBox;
    juce::ComboBox routeBox2;
    juce::Label routeLabel;
    juce::Label routeLabel2;

    juce::Slider freq1Slider;
    juce::Slider depth1Slider;
    juce::Slider shape1Slider;
    juce::Label freq1Label;
    juce::Label depth1Label;
    juce::Label shape1Label;

    juce::Slider freq2Slider;
    juce::Slider depth2Slider;
    juce::Slider shape2Slider;
    juce::Label freq2Label;
    juce::Label depth2Label;
    juce::Label shape2Label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LfoComponent)
};

