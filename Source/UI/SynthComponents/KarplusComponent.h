/*
  ==============================================================================

    KarplusComponent.h
    Created: 31 Mar 2022 4:24:03am
    Author:  User

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

    enum styleEnum {
        isKnob = 0,
        isSlider = 1
    };

    KarplusComponent(juce::AudioProcessorValueTreeState& vts);
    ~KarplusComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    juce::Colour setCustomColour(const std::array<juce::uint8, 3> colourArray);

private:

    void sliderParams(juce::Slider& slider, styleEnum style, juce::Label& label, const std::string& name);

    std::array<juce::uint8, 3> pink{ 240, 107, 242 };
    std::array<juce::uint8, 3> dark{ 83, 36, 115 };
    std::array<juce::uint8, 3> purp{ 118, 48, 217 };
    std::array<juce::uint8, 3> blue{ 4, 88, 140 };
    std::array<juce::uint8, 3> teal{ 121, 242, 230 };

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    juce::Slider kAttSlider;
    juce::Slider kRelSlider;
    juce::Slider kFeedSlider;
    juce::Slider kSwitchSlider;
    juce::Slider fmDepthSlider;
    juce::Slider fmIndexSlider;

    juce::Label kAttLabel;
    juce::Label kRelLabel;
    juce::Label kFeedLabel;
    juce::Label kSwitchLabel;
    juce::Label fmDepthLabel;
    juce::Label fmIndexLabel;

    std::unique_ptr<SliderAttachment> kAttAttachment;
    std::unique_ptr<SliderAttachment> kRelAttachment;
    std::unique_ptr<SliderAttachment> kFeedAttachment;
    std::unique_ptr<SliderAttachment> kSwitchAttachment;
    std::unique_ptr<SliderAttachment> fmDepthAttachment;
    std::unique_ptr<SliderAttachment> fmIndexAttachment;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KarplusComponent)
};
