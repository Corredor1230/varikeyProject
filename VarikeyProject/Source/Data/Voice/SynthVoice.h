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
#include <faust/misc.h>
#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>
#include "../Source/Data/Process/AdsrData.h"
#include "../Source/Data/Process/NoteTuning.h"
#include "../Source/Data/Process/Oscillator.h"
#include "../Source/Data/Process/HipLopFilter.h"
#include "../Source/Data/Synth/Additive.h"
#include "../Source/Data/Synth/Generator.h"
#include "../Source/Data/Synth/Karplus.h"
#include "../Source/Data/Synth/NoiseSynth.h"
#include "../Source/Data/Process/Distortion.h"
#include "../Source/Data/Process/ModRouting.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:

    enum parameterList
    {
        none = 0,
        gen1NoiseMod = 1,
        gen2NoiseMod,
        noise1ToneMod,
        noise2ToneMod,
        mixMod,
        distLeftMod,
        distRightMod,
        distOutLMod,
        distOutRMod,
        lopCutoffMod,
        lopQMod,
        hipCutoffMod,
        hipQMod,
        detuneMod,
        vibFreqMod,
        vibDepthMod,
        volumeMod
    };

    SynthVoice(NoteTuning& someTuner, juce::AudioProcessorValueTreeState& vts, ModRouting& modRouting);
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    //Synth updaters
    void updateLeftGenerator(int genShape, float noiseLevel, int noiseShape);
    void updateRightGenerator(int genShape, float noiseLevel, int noiseShape);
    void updateLeftAdditive(std::array<float, 8> &additiveLeft);
    void updateRightAdditive(std::array<float, 8> &additiveRight);
    void updateLeftKarplus(float karpAttack, float karpRelease, float karpFeedback, int karpNoise);
    void updateRightKarplus(float karpAttack, float karpRelease, float karpFeedback, int karpNoise);
    void updateLeftNoise(float synthTone);
    void updateRightNoise(float synthTone);
    void updateChoice(int leftChoice, int rightChoice, float synthMix);

    //Process updaters
    void updateLeftDist(float input, float output, bool isOn);
    void updateRightDist(float input, float output, bool isOn);
    void updateLopFilter(bool isEnabled, float cutoff, float q);
    void updateHipFilter(bool isEnabled, float cutoff, float q);
    void updateAmpAdsr(float attack, float decay, float sustain, float release);
    void updateModAdsr(float attack, float decay, float sustain, float release, int route);
    void updateGlobal(float detune, float vibFreq, float vibDepth, float volume, bool isGlobalFilter, bool isGlobalHip);
    void updateTuner(std::array<float, 12> &tuningSliders, bool bassTuning, int keyboardBreak, int scaleCenter);
    float freqToMidi(float freq);
    float getMidiNote();
    //void updateLfo1(float freq, float depth, float shape, int route);
    //void updateLfo2(float freq, float depth, float shape, int route);
    //void updateLfo3(float freq, float depth, float shape, int route);
    //void updateLfo4(float freq, float depth, float shape, int route);

private:



    Generator genSynth;
    Generator genSynthRight;
    MapUI genCtrl;
    MapUI genCtrlRight;

    Additive additiveSynth;
    Additive additiveSynthRight;
    MapUI additiveCtrl;
    MapUI additiveCtrlRight;

    Karplus karplusSynth;
    Karplus karplusSynthRight;
    MapUI karpCtrl;
    MapUI karpCtrlRight;

    NoiseSynth noiseSynth;
    NoiseSynth noiseSynthRight;
    MapUI noiseCtrl;
    MapUI noiseCtrlRight;

    Distortion distLeft;
    Distortion distRight;

    juce::dsp::StateVariableTPTFilter<float> juceLopFilt;
    juce::dsp::StateVariableTPTFilter<float> juceHipFilt;
    bool lopEnabled = false;
    bool hipEnabled = false;

    AdsrData adsr;
    AdsrData modAdsr;
    Oscillator vibrato;


    juce::AudioBuffer<float> synthBuffer;
    juce::AudioBuffer<float> rightBuffer;
    juce::AudioBuffer<float> adsrBuffer;

    NoteTuning& tuningRef;
    juce::AudioProcessorValueTreeState& vts;
    ModRouting& modRouting;
    ModRouting adsrRouting;
    

    bool isPrepared{ false };

    //SYNTH
    float leftNoiseLevel = 0;
    float rightNoiseLevel = 0;
    float leftNoiseTone = 0;
    float rightNoiseTone = 0;

    //FILTER
    float lopCutoff = 0;
    float lopMid = 0;
    float hipCutoff = 0;
    float hipMid = 0;
    float lopQ = 0.1;
    float hipQ = 0.1;
    float updateQ = 0.1;
    float updateHipQ = 0.1;

    //CHOICE VARIABLES
    int leftSynthChoice = 0;
    int rightSynthChoice = 1;

    float synthMix = 0;
    float leftRightMix = -1.f;
    float startMixL = 0.f;
    float startMixR = 0.f;
    float endMix = 0.f;
    float endMixL = 0.f;
    float endMixR = 0.f;
    float leftMixGain = 1.f;
    float rightMixGain = 1.f;

    //DIST
    float leftDistInput = 0.f;
    float leftDistOutput = 0.f;
    float rightDistInput = 0.f;
    float rightDistOutput = 0.f;
    bool leftDistIsOn = false;
    bool rightDistIsOn = false;

    //ROUTE
    int modAdsrRoute = 1;

    //GLOBAL
    float synthDetune = 0;
    float vibratoFrequency = 0;
    float vibratoDepth = 0;
    bool isVoiceFilt = false;
    bool isVoiceHip = false;


    //Local

    //Process samples
    float synthStartSample = 0;
    float vibratoSample = 0;
    float modAdsrSample = 0;

    //Tuning
    float tunedMidi = 0;
    float vibratoMidi = 0;
    float processedMidi = 0;
    float oscMidi = 0;
    float oscFreq = 0;
    int keyboardBreak = 48;
    int scaleCenterSetPitch = 0;
    bool bassTuning = false;
    int controlNote = 0;

    float tempVelocity = 0;
    float finalGain = 0;
    int synthSelector = 0;
    float oscModShape = 0;
    float oscModDepth = 0;
    float modOscSample = 0;
    float gen1NoiseLfo = 0;
};