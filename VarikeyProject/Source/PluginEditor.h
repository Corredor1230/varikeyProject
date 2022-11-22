/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/LookAndFeelElements/Fonts/EmbeddedFonts.h"
#include "UI/Global/TuningComponent.h"
#include "UI/VarikeyLookAndFeel.h"
#include "UI/Osc/AdditiveComponent.h"
#include "UI/Osc/GenComponent.h"
#include "UI/Osc/KarplusComponent.h"
#include "UI/Osc/NoiseComponent.h"
#include "UI/Process/FmComponent.h"
#include "UI/Process/FilterComponent.h"
#include "UI/Process/AdsrComponent.h"
#include "UI/Process/ModAdsrComponent.h"
#include "UI/Process/LfoComponent.h"
#include "UI/Global/PitchwheelComponent.h"
#include "UI/Process/DistComponent.h"

//==============================================================================
/**
*/
class VarikeyProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    VarikeyProjectAudioProcessorEditor (VarikeyProjectAudioProcessor&);
    ~VarikeyProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;
    int getComboBoxIndex(const juce::String& string);

private:

    
    VarikeyLookAndFeel varikeyLookAndFeel;


    //GUI VALUES
    int height = 0;
    int width = 0;

    int padding = 0;
    int firstRowStartX = 0;
    int firstRowStartY = 0;
    int firstRowHeight = 0;
    int secondRowHeight = 0;
    int firstColumnWidth = 0;
    int filterWidth = 0;
    int adsrWidth = 0;
    int secondColumnWidth = 0;

    int distRowHeight = 0;
    int lfoHeight = 0;
    int pitchwheelHeight = 0;
    int labelHeight = 0;
    int labelWidth = 0;
    int labelStartX = 0;
    int crossHeight = 0;

    int secondRowStartX = 0;
    int secondRowStartY = 0;
    int thirdRowStartX = 0;
    int thirdRowStartY = 0;
    int thirdRowHeight = 0;
    int volumeWidth = 0;
    
    int tunerWidth = 0;

    int volumeStartX = 0;
    int topStartY = 0;
    int volumeHeight = 0;
    int panHeight = 0;


    int oscChoiceWidth = 0;
    int oscChoiceHeight = 0;


    juce::String leftString{ "additiveLeft" };
    juce::StringArray leftAdditiveIDs
    {
        leftString + "0", 
        leftString + "1", 
        leftString + "2",
        leftString + "3", 
        leftString + "4", 
        leftString + "5",
        leftString + "6", 
        leftString + "7"
    };
    juce::String rightString{ "additiveRight" };
    juce::StringArray rightAdditiveIDs
    {
        rightString + "0",
        rightString + "1",
        rightString + "2",
        rightString + "3",
        rightString + "4",
        rightString + "5",
        rightString + "6",
        rightString + "7"
    };

    //==============================================================================
    // Your private member variables go here...

    VarikeyProjectAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& vts = audioProcessor.vts;

    //Colours
    float alphaValue = 0.8;
    int sliderAlpha = 0.8;
    std::array<int, 3> teal{ 109, 237, 230 };
    std::array<int, 3> cyan{ 174, 235, 254 };
    std::array<int, 3> purp{ 105, 98, 212 };
    std::array<int, 3> pink{ 253, 169, 247 };
    std::array<int, 3> pale{ 234, 246, 242 };


    juce::ComboBox leftOscChoice;
    juce::ComboBox rightOscChoice;
    juce::Slider crossSlider;
    juce::Label crossLabel;

    std::unique_ptr<Drawable> varikeyLogo;

    int leftOscValue = 1;
    int rightOscValue = 1;

    EmbeddedFonts josefinSans;

    //First Row
    AdditiveComponent additiveLeft;
    AdditiveComponent additiveRight;
    GenComponent genLeft;
    GenComponent genRight;
    KarplusComponent karpLeft;
    KarplusComponent karpRight;
    NoiseComponent noiseLeft;
    NoiseComponent noiseRight;

    //FM Row
    DistComponent distLeft;
    DistComponent distRight;

    //Second Row
    FilterComponent filters;
    AdsrComponent ampAdsr;
    ModAdsrComponent modAdsr;
    LfoComponent lfo1;
    LfoComponent lfo2;
    PitchwheelComponent pitchwheel;

    //Third Row
    TuningComponent tuner;
    juce::Slider volumeSlider;
    juce::Label volumeLabel;
    juce::Slider panSlider;
    juce::Label panLabel;

    


    VarikeyLookAndFeel::palette currentPalette = VarikeyLookAndFeel::palette::vaporwave;
    VarikeyLookAndFeel::palette oldPalette;


    juce::AudioProcessorValueTreeState::ComboBoxAttachment leftOscAttachment;
    juce::AudioProcessorValueTreeState::ComboBoxAttachment rightOscAttachment;
    juce::AudioProcessorValueTreeState::SliderAttachment mixAttachment;
    juce::AudioProcessorValueTreeState::SliderAttachment volumeAttachment;
    juce::AudioProcessorValueTreeState::SliderAttachment panAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VarikeyProjectAudioProcessorEditor)
};
