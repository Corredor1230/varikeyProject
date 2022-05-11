/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <faust/misc.h>
#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>
#include "Data/Voice/SynthVoice.h"
#include "Data/Voice/SynthSound.h"
#include"Data/Process/HipLopFilter.h"
#include "Data/Process/Oscillator.h"

//==============================================================================
/**
*/
class VarikeyProjectAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    VarikeyProjectAudioProcessor();
    ~VarikeyProjectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    juce::AudioProcessorValueTreeState vts;

    void createFloatParameter(std::vector < std::unique_ptr<juce::RangedAudioParameter>>& params,
        const juce::String& paramID, const juce::String& paramName, float minValue, float maxValue, float interval,
        float initValue, float skewValue = 1.0f);
    void createIntParameter(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& params,
        const juce::String& paramID, const juce::String& paramName, int minVal, int maxVal, int defaultVal);

    bool isGlobalFilter(int modAdsrRoute);
    bool hasTremolo(int lfo1Route, int lfo2Route, int lfo3Route, int lfo4Route);

private:



    juce::AudioProcessorValueTreeState::ParameterLayout buildParams();
    juce::Synthesiser synth;
    std::array<float, 12> tuning;
    std::array<int, 5> integers;

    float lfo1FreqCtrl = 0;
    float lfo1DepthCtrl = 0;
    float lfo1WaveCtrl = 0;
    
    float lfo2FreqCtrl = 0;
    float lfo2DepthCtrl = 0;
    float lfo2WaveCtrl = 0;

    float lfo3FreqCtrl = 0;
    float lfo3DepthCtrl = 0;
    float lfo3WaveCtrl = 0;

    float lfo4FreqCtrl = 0;
    float lfo4DepthCtrl = 0;
    float lfo4WaveCtrl = 0;

    int lfo1RouteCtrl = 0;
    int lfo2RouteCtrl = 0;
    int lfo3RouteCtrl = 0;
    int lfo4RouteCtrl = 0;

    float loCut = 0;
    float loQ = 0;
    bool loSwitch = false;
    float hiCut = 0;
    float hiQ = 0;
    bool hiSwitch = false;
    int modAdsrR = 0;

    float lfo1Sample = 0;
    float lfo2Sample = 0;
    float lfo3Sample = 0;
    float lfo4Sample = 0;

    NoteTuning noteTuning;
    HipLopFilter filter;
    MapUI filtCtrl;
    Oscillator lfo1Mod;
    Oscillator lfo2Mod;
    Oscillator lfo3Mod;
    Oscillator lfo4Mod;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VarikeyProjectAudioProcessor)
};
