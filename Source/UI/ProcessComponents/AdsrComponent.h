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

    AdsrComponent(juce::String name, juce::AudioProcessorValueTreeState& vts, 
        juce::String attackID, juce::String decayID, juce::String sustainID,
        juce::String releaseID);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    juce::Colour setCustomColour(const std::array<int, 3> colourArray);

private:

    std::array<int, 3> pink{ 240, 107, 242 };
    std::array<int, 3> dark{ 83, 36, 115 };
    std::array<int, 3> purp{ 118, 48, 217 };
    std::array<int, 3> blue{ 4, 88, 140 };
    std::array<int, 3> teal{ 121, 242, 230 };

    void setSliderParams(juce::Slider& slider, juce::Label& label, const std::string& name);
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
