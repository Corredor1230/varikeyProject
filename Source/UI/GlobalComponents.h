/*
  ==============================================================================

    GlobalComponents.h
    Created: 31 Mar 2022 9:03:17pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GlobalComponents  : public juce::Component
{
public:

    enum sliderType {
        typeSlider = 0,
        typeKnob = 1
    };

    GlobalComponents(juce::AudioProcessorValueTreeState& vts);
    ~GlobalComponents() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buildSlider(juce::Slider& thisSlider, sliderType type);
    juce::Colour setCustomColour(const std::array<juce::uint8, 3> colourArray);
    juce::Colour setCustomColourAlpha(std::array<juce::uint8, 3> colour, float alpha);


private:

    std::array<juce::uint8, 3> pink{ 240, 107, 242 };
    std::array<juce::uint8, 3> dark{ 83, 36, 115 };
    std::array<juce::uint8, 3> purp{ 118, 48, 217 };
    std::array<juce::uint8, 3> blue{ 4, 88, 140 };
    std::array<juce::uint8, 3> teal{ 121, 242, 230 };

    juce::Slider gainSlider;
    juce::Slider synthSelect;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> gainAttachment;
    std::unique_ptr<SliderAttachment> selectAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlobalComponents)
};
