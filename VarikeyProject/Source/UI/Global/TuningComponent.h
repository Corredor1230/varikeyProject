/*
  ==============================================================================

    TuningComponent.h
    Created: 8 Apr 2022 11:35:01am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Source/LookAndFeelElements/Fonts/EmbeddedFonts.h"
#include "../VarikeyLookAndFeel.h"

//==============================================================================
/*
*/
class TuningComponent  : public juce::Component
{
public:

    enum sliderStyle {
        vertical = 0,
        rotary,
        horizontal
    };

    TuningComponent();
    ~TuningComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel);
    void setFont(juce::Font& font);


private:

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
    juce::Label breakLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TuningComponent)
};
