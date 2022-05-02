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
        , vts(vts) {}
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
    void updateLeftAdditive(std::array<float, 8> additiveLeft);
    void updateRightAdditive(std::array<float, 8> additiveRight);
    void updateLeftKarplus(float karpAttack, float karpRelease, float karpFeedback, int karpNoise);
    void updateRightKarplus(float karpAttack, float karpRelease, float karpFeedback, int karpNoise);
    void updateLeftNoise(float synthTone);
    void updateRightNoise(float synthTone);
    void updateChoice(int leftChoice, int rightChoice, float synthMix);

    //Process updaters
    void updateLeftFm(float ratio, float depth);
    void updateLeftDist(float input, float output, bool isOn);
    void updateRightDist(float input, float output, bool isOn);
    void updateRightFm(float ratio, float depth);
    void updateLopFilter(bool isEnabled, float cutoff, float q);
    void updateHipFilter(bool isEnabled, float cutoff, float q);
    void updateAmpAdsr(float attack, float decay, float sustain, float release);
    void updateModAdsr(float attack, float decay, float sustain, float release, int route);
    void updateLfo1(float freq, float depth, float shape, int route);
    void updateLfo2(float freq, float depth, float shape, int route);
    void updateLfo3(float freq, float depth, float shape, int route);
    void updateLfo4(float freq, float depth, float shape, int route);
    void updateGlobal(float detune, float vibFreq, float vibDepth, float volume, bool isGlobalFilter);
    void updateTuner(std::array<float, 12> tuningSliders, bool bassTuning, int keyboardBreak, int scaleCenter);
    float freqToMidi(float freq);

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

    Oscillator fmLeft;
    Oscillator fmRight;
    Distortion distLeft;
    Distortion distRight;

    HipLopFilter filter;
    juce::IIRFilter juceFilt;
    juce::IIRCoefficients filtCoefs;
    MapUI filtCtrl;

    AdsrData adsr;
    AdsrData modAdsr;
    Oscillator lfo1Mod;
    Oscillator lfo2Mod;
    Oscillator lfo3Mod;
    Oscillator lfo4Mod;
    Oscillator vibrato;


    juce::AudioBuffer<float> synthBuffer;
    juce::AudioBuffer<float> rightBuffer;

    NoteTuning& tuningRef;
    juce::AudioProcessorValueTreeState& vts;

    bool isPrepared{ false };

    //FILTER
    float lopCutoff = 0;
    float lopMid = 0;
    float hipCutoff = 0;
    float hipMid = 0;
    float lopQ;
    float hipQ;

    //CHOICE VARIABLES
    int leftSynthChoice = 0;
    int rightSynthChoice = 1;

    float leftRightMix = -1.f;
    float leftMixGain = 1.f;
    float rightMixGain = 1.f;

    //FM VARIABLES
    float leftFmRatio = 1.f;
    float leftFmDepth = 0.f;
    float rightFmRatio = 1.f;
    float rightFmDepth = 0.f;

    //DIST
    float leftDistInput = 0.f;
    float leftDistOutput = 0.f;
    float rightDistInput = 0.f;
    float rightDistOutput = 0.f;
    bool leftDistIsOn = false;
    bool rightDistIsOn = false;

    //LFO
    float lfo1Freq = 0.0f;
    float lfo1Depth = 0.0f;
    float lfo1Shape = 1.0f;

    float lfo2Freq = 0.0f;
    float lfo2Depth = 0.0f;
    float lfo2Shape = 1.0f;

    float lfo3Freq = 0.0f;
    float lfo3Depth = 0.0f;
    float lfo3Shape = 1.0f;

    float lfo4Freq = 0.0f;
    float lfo4Depth = 0.0f;
    float lfo4Shape = 1.0f;

    //ROUTE
    int modAdsrRoute = 1;
    int lfo1Route = 1;
    int lfo2Route = 1;
    int lfo3Route = 1;
    int lfo4Route = 1;

    //GLOBAL
    float synthDetune = 0;
    float vibratoFrequency = 0;
    float vibratoDepth = 0;
    float dbVolume = -20;
    float linVolume = 0.7;
    float volLfoCtrl = 0;
    bool isVoiceFilt = false;

    //Local

    //Process samples
    float synthStartSample = 0;
    float vibratoSample = 0;
    float fmLeftSample = 0;
    float modAdsrSample = 0;
    float lfo1Sample = 0;
    float lfo2Sample = 0;
    float lfo3Sample = 0;
    float lfo4Sample = 0;

    //Tuning
    float tunedMidi = 0;
    float vibratoMidi = 0;
    float processedMidi = 0;
    float oscMidi = 0;
    float oscFreq = 0;
    float leftFmFreq = 0;

    float tempVelocity = 0;
    float finalGain = 0;
    int synthSelector = 0;
    float oscModShape = 0;
    float oscModDepth = 0;
    float modOscSample = 0;
    float lfoSample = 0;
};