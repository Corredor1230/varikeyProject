/*
  ==============================================================================

    FilterComponent.h
    Created: 2 Apr 2022 1:55:21am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& vts);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setSliderParams(juce::Slider& slider, juce::Label& label, std::string name);
    juce::Colour setCustomColour(const std::array<int, 3> colourArray);


private:

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    std::array<int, 3> pink{ 240, 107, 242 };
    std::array<int, 3> dark{ 83, 36, 115 };
    std::array<int, 3> purp{ 118, 48, 217 };
    std::array<int, 3> blue{ 4, 88, 140 };
    std::array<int, 3> teal{ 121, 242, 230 };

    juce::Slider cutoffSlider;
    juce::Slider qSlider;
    juce::ToggleButton filterOnOff;

    juce::Label cutoffLabel;
    juce::Label qLabel;

    std::unique_ptr<SliderAttachment> cutoffAttachment;
    std::unique_ptr<SliderAttachment> qAttachment;
    std::unique_ptr<ButtonAttachment> filterOnOffAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
