/*
  ==============================================================================

    SynthVoice.cpp
    Created: 22 Mar 2022 10:48:04pm
    Author:  User

  ==============================================================================
*/

#include "SynthVoice.h"



bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    // recuerda los problemas de imprimir en el process block, creo q acá esta bien sin embargo

    //Note on for all synths
    //By passing a note on to all of them at the same time,
    //it's possible to switch between synths in real time.
    genCtrl.setParamValue("gate", true);
    additiveCtrl.setParamValue("gate", true);
    karpCtrl.setParamValue("gate", true);
    noiseCtrl.setParamValue("gate", true);

    genCtrlRight.setParamValue("gate", true);
    additiveCtrlRight.setParamValue("gate", true);
    karpCtrlRight.setParamValue("gate", true);
    noiseCtrlRight.setParamValue("gate", true);

    adsr.noteOn();
    modAdsr.noteOn();

    //Copies velocity to global tempVelocity variable for real time control
    tempVelocity = velocity;
    
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    modAdsr.noteOff();
    karpCtrl.setParamValue("gate", false);
    karpCtrlRight.setParamValue("gate", false);


    if (!allowTailOff || !adsr.isActive())
    {
        clearCurrentNote();
    }
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{


}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{


}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    genSynth.init(sampleRate);
    genSynth.buildUserInterface(&genCtrl);

    additiveSynth.init(sampleRate);
    additiveSynth.buildUserInterface(&additiveCtrl);

    noiseSynth.init(sampleRate);
    noiseSynth.buildUserInterface(&noiseCtrl);

    karplusSynth.init(sampleRate);
    karplusSynth.buildUserInterface(&karpCtrl);

    genSynthRight.init(sampleRate);
    genSynthRight.buildUserInterface(&genCtrlRight);

    additiveSynthRight.init(sampleRate);
    additiveSynthRight.buildUserInterface(&additiveCtrlRight);

    noiseSynthRight.init(sampleRate);
    noiseSynthRight.buildUserInterface(&noiseCtrlRight);

    karplusSynthRight.init(sampleRate);
    karplusSynthRight.buildUserInterface(&karpCtrlRight);

    fmLeft.init(sampleRate);
    fmRight.init(sampleRate);
    lfo1Mod.init(sampleRate);
    lfo2Mod.init(sampleRate);
    lfo3Mod.init(sampleRate);
    lfo4Mod.init(sampleRate);
    vibrato.init(sampleRate);

    filter.init(sampleRate);
    filter.buildUserInterface(&filtCtrl);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    juceLopFilt.prepare(spec);
    juceLopFilt.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    juceHipFilt.prepare(spec);
    juceHipFilt.setType(juce::dsp::StateVariableTPTFilterType::highpass);

    adsr.setSampleRate(sampleRate);
    modAdsr.setSampleRate(sampleRate);
    lfo1Mod.init(sampleRate);

}

void SynthVoice::updateLeftGenerator(int genShape, float noiseLevel, int noiseShape)
{
    genCtrl.setParamValue("shape", genShape);
    genCtrl.setParamValue("noiseLevel", noiseLevel);
    genCtrl.setParamValue("noiseShape", noiseShape);
}

void SynthVoice::updateRightGenerator(int genShape, float noiseLevel, int noiseShape)
{
    genCtrlRight.setParamValue("shape", genShape);
    genCtrlRight.setParamValue("noiseLevel", noiseLevel);
    genCtrlRight.setParamValue("noiseShape", noiseShape);
}

void SynthVoice::updateLeftAdditive(std::array<float, 8> additiveLeft)
{
    additiveCtrl.setParamValue("first", additiveLeft[0]);
    additiveCtrl.setParamValue("second", additiveLeft[1]);
    additiveCtrl.setParamValue("third", additiveLeft[2]);
    additiveCtrl.setParamValue("fourth", additiveLeft[3]);
    additiveCtrl.setParamValue("fifth", additiveLeft[4]);
    additiveCtrl.setParamValue("sixth", additiveLeft[5]);
    additiveCtrl.setParamValue("seventh", additiveLeft[6]);
    additiveCtrl.setParamValue("eigth", additiveLeft[7]);

}

void SynthVoice::updateRightAdditive(std::array<float, 8> additiveRight)
{
    additiveCtrlRight.setParamValue("first", additiveRight[0]);
    additiveCtrlRight.setParamValue("second", additiveRight[1]);
    additiveCtrlRight.setParamValue("third", additiveRight[2]);
    additiveCtrlRight.setParamValue("fourth", additiveRight[3]);
    additiveCtrlRight.setParamValue("fifth", additiveRight[4]);
    additiveCtrlRight.setParamValue("sixth", additiveRight[5]);
    additiveCtrlRight.setParamValue("seventh", additiveRight[6]);
    additiveCtrlRight.setParamValue("eighth", additiveRight[7]);
}

void SynthVoice::updateLeftKarplus(float karpAttack, float karpRelease, float karpFeedback, int karpNoise)
{
    karpCtrl.setParamValue("kAtt", karpAttack);
    karpCtrl.setParamValue("kRel", karpRelease);
    karpCtrl.setParamValue("kFeed", karpFeedback);
    karpCtrl.setParamValue("kSwitch", karpNoise);
}

void SynthVoice::updateRightKarplus(float karpAttack, float karpRelease, float karpFeedback, int karpNoise)
{
    karpCtrlRight.setParamValue("kAtt", karpAttack);
    karpCtrlRight.setParamValue("kRel", karpRelease);
    karpCtrlRight.setParamValue("kFeed", karpFeedback);
    karpCtrlRight.setParamValue("kSwitch", karpNoise);
}

void SynthVoice::updateLeftNoise(float synthTone)
{
    noiseCtrl.setParamValue("tone", synthTone);
}

void SynthVoice::updateRightNoise(float synthTone)
{
    noiseCtrlRight.setParamValue("tone", synthTone);
}

void SynthVoice::updateChoice(int leftChoice, int rightChoice, float synthMix)
{
    leftSynthChoice = leftChoice;
    rightSynthChoice = rightChoice;
    leftRightMix = synthMix;
    leftMixGain = ((leftRightMix - 1) / 2) * (-1);
    rightMixGain = ((leftRightMix + 1) / 2);
}



void SynthVoice::updateLeftFm(float ratio, float depth)
{
    leftFmRatio = ratio;
    leftFmDepth = depth;
}

void SynthVoice::updateRightFm(float ratio, float depth)
{

}

void SynthVoice::updateLeftDist(float input, float output, bool isOn)
{
    leftDistInput = input;
    leftDistOutput = output;
    distLeft.updateDistortion(leftDistInput, leftDistOutput);
    leftDistIsOn = isOn;
}

void SynthVoice::updateRightDist(float input, float output, bool isOn)
{
    rightDistInput = input;
    rightDistOutput = output;
    distRight.updateDistortion(rightDistInput, rightDistOutput);
    rightDistIsOn = isOn;
}

void SynthVoice::updateLopFilter(bool isEnabled, float cutoff, float q)
{
    lopEnabled = isEnabled;
    filtCtrl.setParamValue("lopOnOff", isEnabled);
    lopMid = freqToMidi(cutoff);
    //modAdsrSample = modAdsr.getNextSample();
    lopCutoff = std::fmin(20000,
        std::fmax(100,
            (tuningRef.midiToHertz(lopMid * (modAdsrSample * 0.5 + 0.5) * (modAdsrRoute == 10)))));
    (modAdsrRoute == 11) ? updateQ = std::fmax(0.1, q * modAdsrSample) : updateQ = q;
    juceLopFilt.setCutoffFrequency(lopCutoff);
    juceLopFilt.setResonance(updateQ);
    filtCtrl.setParamValue("lopCutoff", lopCutoff);
    filtCtrl.setParamValue("lopQ", q);
}

void SynthVoice::updateHipFilter(bool isEnabled, float cutoff, float q)
{
    hipEnabled = isEnabled;
    filtCtrl.setParamValue("hipOnOff", isEnabled);
    hipMid = freqToMidi(cutoff);
    hipCutoff = std::fmin(20000, std::fmax(20,
        (tuningRef.midiToHertz(hipMid * (modAdsrSample * 0.5 + 0.5) * (modAdsrRoute == 12)))));
    (modAdsrRoute == 13) ? updateHipQ = std::fmax(0.1, q * modAdsrSample) : updateHipQ = q;
    filtCtrl.setParamValue("hipCutoff", cutoff);
    filtCtrl.setParamValue("hipQ", q);
}

void SynthVoice::updateAmpAdsr(float attack, float decay, float sustain, float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::updateModAdsr(float attack, float decay, float sustain, float release, int route)
{
    modAdsr.updateADSR(attack, decay, sustain, release);
    modAdsrRoute = route;
}

void SynthVoice::updateLfo1(float freq, float depth, float shape, int route)
{
    lfo1Freq = freq;
    lfo1Depth = depth;
    lfo1Shape = shape;
    lfo1Route = route;
    lfo1Mod.setFreq(freq);
    lfo1Mod.updateLfo(shape, depth);

}

void SynthVoice::updateLfo2(float freq, float depth, float shape, int route)
{
    lfo2Freq = freq;
    lfo2Depth = depth;
    lfo2Shape = shape;
    lfo2Route = route;
    lfo2Mod.setFreq(freq);
    lfo2Mod.updateLfo(shape, depth);

}

void SynthVoice::updateLfo3(float freq, float depth, float shape, int route)
{
    lfo3Freq = freq;
    lfo3Depth = depth;
    lfo3Shape = shape;
    lfo3Route = route;
    lfo3Mod.setFreq(freq);
    lfo3Mod.updateLfo(shape, depth);
}

void SynthVoice::updateLfo4(float freq, float depth, float shape, int route)
{
    lfo4Freq = freq;
    lfo4Depth = depth;
    lfo4Shape = shape;
    lfo4Route = route;
    lfo4Mod.setFreq(freq);
    lfo4Mod.updateLfo(shape, depth);
}

void SynthVoice::updateGlobal(float detune, float vibFreq, float vibDepth, float volume, bool isGlobalFilter)
{
    synthDetune = detune;
    vibrato.setFreq(vibFreq);
    vibrato.updateLfo(1, vibDepth);
    vibratoDepth = vibDepth;
    dbVolume = volume;
    linVolume = juce::Decibels::decibelsToGain(volume, -60.f);
    isGlobalFilter ? isVoiceFilt = false : isVoiceFilt = true;
}

void SynthVoice::updateTuner(std::array<float, 12> tuningSliders, bool bassTuning, int keyboardBreak, int scaleCenter)
{
    tuningRef.setTuning(tuningSliders);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{

    //SETUP
    //-------------------------------------------------------------
    // muy bien esto!
    if (!isVoiceActive())
        return;

    // esto aun no me convence XD
    // ando buscando soluciones para esto
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    rightBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    adsrBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);

    int sampNumber = synthBuffer.getNumSamples();

    //We need to include our modAdsr in the buffer for it to work
    //but at this stage of the buffer, it does no processing!

    synthBuffer.clear();
    rightBuffer.clear();

    for (int i = 0; i < sampNumber; i++)
    {
        vibratoSample = vibrato.getNextSample();
    }

    for (int i = 0; i < sampNumber; i++)
    {
        lfo2Sample = lfo2Mod.getNextSample();
    }
    for (int i = 0; i < sampNumber; i++)
    {
        lfo3Sample = lfo3Mod.getNextSample();
    }
    for (int i = 0; i < sampNumber; i++)
    {
        lfo4Sample = lfo4Mod.getNextSample();
    }

    //Updating our tuning in real time
    tunedMidi = tuningRef.alterMidiPitch(getCurrentlyPlayingNote());
    vibratoMidi = vibratoDepth * vibratoSample;
    processedMidi = tunedMidi + vibratoMidi + synthDetune;

    oscMidi = processedMidi;


    oscFreq = std::fmax(std::fmin(tuningRef.midiToHertz(oscMidi), 20000.f), 22.f);

    //-------------------------------------------------------------

    float** synthData = synthBuffer.getArrayOfWritePointers();
    float** rightData = rightBuffer.getArrayOfWritePointers();

    auto audioBlock = juce::dsp::AudioBlock<float> {synthBuffer};
    auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);

    //OSCILLATORS
    //-------------------------------------------------------------
    //Selector for different synthesizers
    switch (leftSynthChoice)
    {
    case 0:
        genCtrl.setParamValue("freq", oscFreq);
        genSynth.compute(sampNumber, nullptr, synthData);
        break;
    case 1:
        additiveCtrl.setParamValue("freq", oscFreq);
        additiveSynth.compute(sampNumber, nullptr, synthData);
        break;
    case 2:
        karpCtrl.setParamValue("freq", oscFreq);
        karplusSynth.compute(sampNumber, nullptr, synthData);
        break;
    case 3:
        noiseCtrl.setParamValue("freq", oscFreq);
        noiseSynth.compute(sampNumber, nullptr, synthData);
        break;
    }

    switch (rightSynthChoice)
    {
    case 0:
        genCtrlRight.setParamValue("freq", oscFreq);
        genSynthRight.compute(sampNumber, nullptr, rightData);
        break;
    case 1:
        additiveCtrlRight.setParamValue("freq", oscFreq);
        additiveSynthRight.compute(sampNumber, nullptr, rightData);
        break;
    case 2:
        karpCtrlRight.setParamValue("freq", oscFreq);
        karplusSynthRight.compute(sampNumber, nullptr, rightData);
        break;
    case 3:
        noiseCtrlRight.setParamValue("freq", oscFreq);
        noiseSynthRight.compute(sampNumber, nullptr, rightData);
        break;
    }

    //PROCESS
    //-------------------------------------------------------------
    //Filter with distortion

    if (leftDistIsOn)
    {
        for (int i = 0; i < sampNumber; i++)
        {
            for (int ch = 0; ch < synthBuffer.getNumChannels(); ch++)
            {
                distLeft.process(synthBuffer, ch, i);
            }
        }
    }


    if (rightDistIsOn)
    {
        for (int i = 0; i < sampNumber; i++)
        {
            for (int ch = 0; ch < rightBuffer.getNumChannels(); ch++)
            {
                distRight.process(rightBuffer, ch, i);
            }
        }
    }

    for (int i = 0; i < sampNumber; i++)
    {
        for (int ch = 0; ch < synthBuffer.getNumChannels(); ch++)
        {
            synthBuffer.applyGain(ch, i, 1, leftMixGain);
            rightBuffer.applyGain(ch, i, 1, rightMixGain);
            synthBuffer.addSample(ch, i, rightBuffer.getSample(ch, i));
        }
    }


    for (int i = 0; i < sampNumber; i++)
    {
        lfo1Sample = lfo1Mod.getNextSample();
        volLfoCtrl = (lfo1Sample + 1) / 2.2;

        for (int ch = 0; ch < synthBuffer.getNumChannels(); ch++)
        {
            synthBuffer.applyGain(ch, i, 1, 1.0 - (volLfoCtrl * lfo1Depth * (lfo1Route == 17)));
        }
    }

    modAdsr.applyEnvelopeToBuffer(adsrBuffer, 0, sampNumber);

    if (isVoiceFilt)
    {
        for (int ch = 0; ch < synthBuffer.getNumChannels(); ch++)
        {
            for (int samp = 0; samp < sampNumber; samp++)
            {
                modAdsrSample = modAdsr.getNextSample();
            }
        }
        if (lopEnabled) juceLopFilt.process(context);
        if (hipEnabled) juceHipFilt.process(context);
    }



    //if (isVoiceFilt) filter.compute(sampNumber, synthData, synthData);

    //Amp adsr control
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, sampNumber);
    //-------------------------------------------------------------


    //CLEAR
    //-------------------------------------------------------------

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (!adsr.isActive())
        {
            clearCurrentNote();
        }
    }
}

float SynthVoice::freqToMidi(float freq)
{
    return ((12 * log(freq / 220.0) / log(2.0)) + 57.01);
}



////Trying to avoid using a new buffer in Audio Thread
//void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
//{
//
//    //SETUP
//    //-------------------------------------------------------------
//    // muy bien esto!
//    if (!isVoiceActive())
//        return;
//
//    float** synthData = outputBuffer.getArrayOfWritePointers();
//    float newMidi = tuningRef.alterMidiPitch(getCurrentlyPlayingNote());
//    float oscFreq = tuningRef.midiToHertz(newMidi);
//
//    while (--numSamples >= 0)
//    {
//
//        genCtrl.setParamValue("freq", oscFreq);
//        genSynth.compute(numSamples, nullptr, synthData);
//        startSample++;
//    }
//
//    while (--numSamples >= 0)
//    {
//        adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
//        startSample++;
//    }
//
//        for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
//        {    
//            if (!adsr.isActive())
//            {
//                clearCurrentNote();
//            }
//    
//            //clearCurrentNote();
//        }
//
//
//    
//}