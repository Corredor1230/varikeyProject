/*
  ==============================================================================

    TuningComponent.h
    Created: 24 Mar 2022 5:26:11am
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TuningComponent  : public juce::Component
{
public:

    enum keyColor {
        black = 0,
        white
    };

    TuningComponent(juce::AudioProcessorValueTreeState& vts);

    ~TuningComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void buildSlider(juce::Slider& slider, juce::Label& label, keyColor color, const std::string& name);

private:

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    juce::Slider cSlider;
    juce::Slider cesSlider;
    juce::Slider dSlider;
    juce::Slider desSlider;
    juce::Slider eSlider;
    juce::Slider fSlider;
    juce::Slider fesSlider;
    juce::Slider gSlider;
    juce::Slider gesSlider;
    juce::Slider aSlider;
    juce::Slider aesSlider;
    juce::Slider bSlider;

    juce::Label clabel;
    juce::Label ceslabel;
    juce::Label dlabel;
    juce::Label deslabel;
    juce::Label elabel;
    juce::Label flabel;
    juce::Label feslabel;
    juce::Label glabel;
    juce::Label geslabel;
    juce::Label alabel;
    juce::Label aeslabel;
    juce::Label blabel;

    std::unique_ptr<SliderAttachment> cAttachment;
    std::unique_ptr<SliderAttachment> cesAttachment;
    std::unique_ptr<SliderAttachment> dAttachment;
    std::unique_ptr<SliderAttachment> desAttachment;
    std::unique_ptr<SliderAttachment> eAttachment;
    std::unique_ptr<SliderAttachment> fAttachment;
    std::unique_ptr<SliderAttachment> fesAttachment;
    std::unique_ptr<SliderAttachment> gAttachment;
    std::unique_ptr<SliderAttachment> gesAttachment;
    std::unique_ptr<SliderAttachment> aAttachment;
    std::unique_ptr<SliderAttachment> aesAttachment;
    std::unique_ptr<SliderAttachment> bAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TuningComponent)
};
