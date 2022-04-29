/*
  ==============================================================================

    AdsrComponent.h
    Created: 8 Apr 2022 11:36:36am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:

    enum sliderStyle {
        vertical = 0,
        rotary,
        horizontal
    };

    AdsrComponent(juce::AudioProcessorValueTreeState& vts);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style);
    void setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel);
private:

    juce::AudioProcessorValueTreeState& vts;
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    double maximumSliderValue = 5000.0;
    double sliderInterval = 0.1;
    double sliderSkewFromMid = 200.0;

    juce::Label titleLabel;

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainLabel;
    juce::Label releaseLabel;

    SliderAttachment attackAttachment;
    SliderAttachment decayAttachment;
    SliderAttachment sustainAttachment;
    SliderAttachment releaseAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
