/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceSynthAudioProcessorEditor::JuceSynthAudioProcessorEditor (JuceSynthAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , audioProcessor (p)
    , adsr("AmpAdsr", audioProcessor.vts, "Att", "Dec", "Sus", "Rel")
    , tuning(audioProcessor.vts)
    , karplus(audioProcessor.vts)
    , global(audioProcessor.vts) // el orden de inicialización de esto no corresponde con lo q está en el header
    , modAdsr("ModAdsr", audioProcessor.vts, "modAtt", "modDec", "modSus", "modRel")
    , filter(audioProcessor.vts)
    , lfo(audioProcessor.vts)
{
    setSize (600, 600);

    addAndMakeVisible(adsr);
    addAndMakeVisible(tuning);
    addAndMakeVisible(karplus);
    addAndMakeVisible(global);
    addAndMakeVisible(modAdsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(lfo);

}

JuceSynthAudioProcessorEditor::~JuceSynthAudioProcessorEditor()
{
}

//==============================================================================
void JuceSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setFont(josefinSans.getJosefinSans());
    g.fillAll (juce::Colour(0,0,0));

}

void JuceSynthAudioProcessorEditor::resized()
{
    // mira esto
    // https://www.youtube.com/watch?v=xsCZoE1s_uw
    
    filter.setBounds(0, 0, getWidth() / 4, getHeight() / 3);
    lfo.setBounds(filter.getRight(), 0, getWidth() / 4, getHeight() / 3);
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight() / 3);
    tuning.setBounds(10, (getHeight() / 3) * 2, getWidth(), getHeight() / 3);
    karplus.setBounds(10, (getHeight() / 3), getWidth() / 2, getHeight() / 3);
    global.setBounds(karplus.getWidth() + 10, getHeight() / 3, getWidth() / 4, getHeight() / 3);
    modAdsr.setBounds(global.getRight(), getHeight() / 3, getWidth() / 4, getHeight() / 3);
}

