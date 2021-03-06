/*
  ==============================================================================

    KarplusComponent.h
    Created: 8 Apr 2022 11:36:06am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class KarplusComponent  : public juce::Component
{
public:

    enum sliderStyle {
        vertical = 0,
        rotary,
        horizontal
    };

    KarplusComponent(juce::AudioProcessorValueTreeState& vts, juce::String attID, 
        juce::String relID, juce::String feedID, juce::String noiseID);
    ~KarplusComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style);
    void setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel);
    void setRegionTitle(juce::String& region);

private:

    juce::AudioProcessorValueTreeState& vts;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    juce::Label titleLabel;
    juce::String regionTitle = "Osc 1: ";
    juce::String componentTitle = "Karplus Synth";
    int noiseShapeValue = 0;

    juce::Slider kAttSlider;
    juce::Slider kRelSlider;
    juce::Slider kFeedSlider;
    juce::Slider kNoiseSlider;

    juce::Label kAttLabel;
    juce::Label kRelLabel;
    juce::Label kFeedLabel;
    juce::Label kWhiteLabel;
    juce::Label kPinkLabel;

    SliderAttachment kAttAttachment;
    SliderAttachment kRelAttachment;
    SliderAttachment kFeedAttachment;
    SliderAttachment kNoiseAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KarplusComponent)
};
