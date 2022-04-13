/*
  ==============================================================================

    AdsrComponent.h
    Created: 23 Mar 2022 12:03:15pm
    Author:  User

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

    enum parameter
    {
        att = 0,
        dec,
        sus,
        rel
    };

    AdsrComponent(juce::AudioProcessorValueTreeState& vts);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    void setSliderParams(juce::Slider& slider, juce::Label& label, const std::string& name);
    juce::StringArray nameArray{ "Attack", "Decay", "Sustain", "Release" };
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    juce::Label attLabel;
    juce::Label decLabel;
    juce::Label susLabel;
    juce::Label relLabel;


    std::unique_ptr<SliderAttachment> attAttachment;
    std::unique_ptr<SliderAttachment> decAttachment;
    std::unique_ptr<SliderAttachment> susAttachment;
    std::unique_ptr<SliderAttachment> relAttachment;



    juce::Slider attSlider;
    juce::Slider decSlider;
    juce::Slider susSlider;
    juce::Slider relSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
