/*
  ==============================================================================

    LfoComponent.h
    Created: 12 Apr 2022 7:33:47pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LfoComponent  : public juce::Component
{
public:
    LfoComponent(juce::AudioProcessorValueTreeState& vts);
    ~LfoComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::AudioProcessorValueTreeState& vts;

    juce::Slider lfoFreqSlider;
    juce::Slider lfoDepthSlider;
    juce::Slider lfoWaveSlider;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    SliderAttachment lfoFreqAttachment;
    SliderAttachment lfoDepthAttachment;
    SliderAttachment lfoWaveAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LfoComponent)
};
