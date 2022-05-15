/*
  ==============================================================================

    TuningComponent.h
    Created: 8 Apr 2022 11:35:01am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../LookAndFeelElements/Fonts/EmbeddedFonts.h"
#include "../VarikeyLookAndFeel.h"

//==============================================================================
/*
*/
class TuningComponent : public juce::Component
{
public:

    enum sliderStyle {
        vertical = 0,
        rotary,
        horizontal
    };

    TuningComponent(juce::AudioProcessorValueTreeState& vts);
    ~TuningComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel);
    void setFont(juce::Font& font);


private:

    juce::AudioProcessorValueTreeState& vts;
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    void setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style);
    //juce::Font tuningFont;

    juce::Font customFont;

    juce::Slider slider0;
    juce::Slider slider1;
    juce::Slider slider2;
    juce::Slider slider3;
    juce::Slider slider4;
    juce::Slider slider5;
    juce::Slider slider6;
    juce::Slider slider7;
    juce::Slider slider8;
    juce::Slider slider9;
    juce::Slider slider10;
    juce::Slider slider11;
    juce::Slider transposeSlider;
    juce::Slider keybreakSlider;
    juce::ToggleButton keyBreakToggle;
    int transposeTextBoxWidth;
    int transposeTextBoxHeight;
    juce::DrawableRectangle valueOutline;

    juce::Label label0;
    juce::Label label1;
    juce::Label label2;
    juce::Label label3;
    juce::Label label4;
    juce::Label label5;
    juce::Label label6;
    juce::Label label7;
    juce::Label label8;
    juce::Label label9;
    juce::Label label10;
    juce::Label label11;
    juce::Label transposeLabel;
    juce::Label titleLabel;
    juce::Label keyBreakLabel;
    juce::Label keyBreakValue;
    juce::String breakKeyString;
    int breakKeyValue = 48;
    juce::Label breakLabel;

    SliderAttachment attachment0;
    SliderAttachment attachment1;
    SliderAttachment attachment2;
    SliderAttachment attachment3;
    SliderAttachment attachment4;
    SliderAttachment attachment5;
    SliderAttachment attachment6;
    SliderAttachment attachment7;
    SliderAttachment attachment8;
    SliderAttachment attachment9;
    SliderAttachment attachment10;
    SliderAttachment attachment11;
    SliderAttachment transposeAttachment;
    SliderAttachment breakAttachment;
    juce::AudioProcessorValueTreeState::ButtonAttachment breakToggleAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TuningComponent)
};
