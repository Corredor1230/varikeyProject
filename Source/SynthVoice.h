/*
  ==============================================================================

    SynthVoice.h
    Created: 22 Mar 2022 10:48:04pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/Process/AdsrData.h"
#include "Data/Synth/OscData.h"
#include "Data/Synth/NoteTuning.h"
#include <faust/misc.h>
#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>
#include "Data/Synth/SimpleSynth.h"
#include "Data/Synth/Test.h"
#include "Data/Synth/Karplus.h"
#include "Data/Process/Filter.h"
#include "Data/Process/Oscillator.h"

//class myVector {
//    int numElements;
//    void* memory;
//    ´myVector(5) {
//        memory = new double[2*5];
//    }
//
//    void push(double newElement) {
//        void* temp = new double[6]
//            memcpy(temp, memory, 5);
//        delete memeroy
//            memory = temp;
//    }
//
//};

class SynthVoice : public juce::SynthesiserVoice
{
public:
    SynthVoice(NoteTuning& someTuner, juce::AudioProcessorValueTreeState& vts) : tuningRef(someTuner)
    ,vts(vts){}
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    void updateKarplus(float kFeed, std::array<int, 5> integers);
    void updateAdsr(const float attack, const float decay, const float sustain, const float release);
    void updateModAdsr(const float attack, const float decay, const float sustain, const float release);
    void updateGeneric(std::array<int, 1> integers, std::array<float, 1> floats);
    void updateFilter(int cutoff, float q);
    void updateOscMod(float freq, float shape, float depth);
    void updateLfo(float freq, float wave, float depth);

private:
    Karplus karplusSynth;
    Test test;
    MapUI ctrl;
    MapUI karpCtrl;
    MapUI filtCtrl;

    AdsrData adsr;
    AdsrData modAdsr;
    Filter filter;
    Oscillator lfoMod;


    juce::AudioBuffer<float> synthBuffer;
    juce::AudioBuffer<float> lfoBuffer;

    NoteTuning& tuningRef;
    juce::AudioProcessorValueTreeState& vts;
    juce::dsp::Gain<float> gain;

    bool isPrepared{ false };

    float tempVelocity = 0;
    int synthSelector = 0;
    float modAdsrSample = 0;
    float oscModShape = 0;
    float oscModDepth = 0;
    float modOscSample = 0;
    float lfoSample = 0;
    float test = 0;
    
};