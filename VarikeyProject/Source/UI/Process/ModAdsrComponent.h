/*
  ==============================================================================

    ModAdsrComponent.h
    Created: 21 Apr 2022 4:08:07am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ModAdsrComponent  : public juce::Component
{
public:

    enum sliderStyle {
        vertical = 0,
        rotary,
        horizontal
    };

    ModAdsrComponent();
    ~ModAdsrComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style);
    void setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel);
private:

    double maximumSliderValue = 5000.0;
    double sliderInterval = 0.1;
    double sliderSkewFromMid = 200.0;

    juce::Label titleLabel;

    juce::ComboBox routeBox;
    juce::Label routeLabel;

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainLabel;
    juce::Label releaseLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModAdsrComponent)
};
