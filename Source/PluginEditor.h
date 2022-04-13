/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/ProcessComponents/AdsrComponent.h"
#include "UI/SynthComponents/TuningComponent.h"
#include "UI/SynthComponents/KarplusComponent.h"
#include "UI/GlobalComponents.h"
#include "UI/ProcessComponents/FilterComponent.h"
#include "UI/LookAndFeel/EmbeddedFonts.h"
#include "UI/ProcessComponents/LfoComponent.h"

//==============================================================================
/**
*/
class JuceSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JuceSynthAudioProcessorEditor (JuceSynthAudioProcessor&);
    ~JuceSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    JuceSynthAudioProcessor& audioProcessor;
    AdsrComponent adsr;
    AdsrComponent modAdsr;
    TuningComponent tuning;
    KarplusComponent karplus;
    GlobalComponents global;
    FilterComponent filter;
    EmbeddedFonts josefinSans;
    LfoComponent lfo;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthAudioProcessorEditor)
};
