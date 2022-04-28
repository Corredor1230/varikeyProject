/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Data/Voice/SynthVoice.h"
#include "Data/Voice/SynthSound.h"

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

private:



    juce::AudioProcessorValueTreeState::ParameterLayout buildParams();
    juce::Synthesiser synth;
    std::array<float, 12> tuning;
    std::array<int, 5> integers;

    float lfoFreq = 0;
    float lfoDepth = 0;
    float lfoWave = 0;

    NoteTuning noteTuning;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VarikeyProjectAudioProcessor)
};
