/*
  ==============================================================================

    SynthVoice.cpp
    Created: 22 Mar 2022 10:48:04pm
    Author:  User

  ==============================================================================
*/

#include "SynthVoice.h"

int SynthVoice::controlMidi = 0;

SynthVoice::SynthVoice(NoteTuning& someTuner, juce::AudioProcessorValueTreeState& vts, ModRouting& modRouting)
    : tuningRef(someTuner)
    , vts(vts) 
    , modRouting(modRouting)
{
    adsrRouting.setRoutingState(modRouting.getRoutingState());
}

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    voicePan = (rand.nextFloat() * 2.f) - 1.f;

    //Note on for all synths
    //By passing a 'note on' msg to all of them at the same time,
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


    //lfo1Mod.init(sampleRate);
    //lfo2Mod.init(sampleRate);
    //lfo3Mod.init(sampleRate);
    //lfo4Mod.init(sampleRate);
    vibrato.init(sampleRate);


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

}

void SynthVoice::updateLeftGenerator(int genShape, float noiseLevel, int noiseShape)
{
    genCtrl.setParamValue("shape", genShape);
    //genCtrl.setParamValue("noiseLevel", noiseLevel);
    leftNoiseLevel = noiseLevel;
    genCtrl.setParamValue("noiseShape", noiseShape);
}

void SynthVoice::updateRightGenerator(int genShape, float noiseLevel, int noiseShape)
{
    genCtrlRight.setParamValue("shape", genShape);
    //genCtrlRight.setParamValue("noiseLevel", noiseLevel);
    rightNoiseLevel = noiseLevel;
    genCtrlRight.setParamValue("noiseShape", noiseShape);
}

void SynthVoice::updateLeftAdditive(std::array<float, 8> &additiveLeft)
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

void SynthVoice::updateRightAdditive(std::array<float, 8> &additiveRight)
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
    //noiseCtrl.setParamValue("tone", synthTone);
    leftNoiseTone = synthTone;
}

void SynthVoice::updateRightNoise(float synthTone)
{
    //noiseCtrlRight.setParamValue("tone", synthTone);
    rightNoiseTone = synthTone;
}

void SynthVoice::updateChoice(int leftChoice, int rightChoice, float synthMix)
{
    leftSynthChoice = leftChoice;
    rightSynthChoice = rightChoice;
    leftRightMix = synthMix;
    //leftRightMix = modRouting.modulateValue(mixMod, synthMix);
    //leftMixGain = ((leftRightMix - 1) / 2) * (-1);
    //rightMixGain = ((leftRightMix + 1) / 2);
}

void SynthVoice::updateLeftDist(float input, float output, bool isOn)
{
    leftDistInput = input;
    leftDistOutput = output;
    distLeft.updateDistortion(modRouting.modulateValue(distLeftMod, leftDistInput),
            modRouting.modulateValue(distOutLMod, leftDistOutput));
    leftDistIsOn = isOn;
}

void SynthVoice::updateRightDist(float input, float output, bool isOn)
{
    rightDistInput = input;
    rightDistOutput = output;
    distRight.updateDistortion(modRouting.modulateValue(distRightMod, rightDistInput),
            modRouting.modulateValue(distOutRMod, rightDistOutput));
    rightDistIsOn = isOn;
}

void SynthVoice::updateLopFilter(bool isEnabled, float cutoff, float q)
{
    lopEnabled = isEnabled;
    lopCutoff = cutoff;
    lopQ = q;
}

void SynthVoice::updateHipFilter(bool isEnabled, float cutoff, float q)
{
    hipEnabled = isEnabled;
    hipCutoff = cutoff;
    hipQ = q;
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


void SynthVoice::updateGlobal(float detune, float vibFreq, float vibDepth, float volume, bool isGlobalFilter, bool isGlobalHip)
{
    synthDetune = detune;
    //vibrato.setFreq(modRouting.modulateValue(vibFreqMod, vibFreq));
    //vibrato.updateLfo(1, modRouting.modulateValue(vibDepthMod, vibDepth));
    vibratoFrequency = vibFreq;
    vibratoDepth = vibDepth;
    isGlobalFilter ? isVoiceFilt = false : isVoiceFilt = true;
    isGlobalHip ? isVoiceHip = false : isVoiceHip = true;
}

void SynthVoice::updateTuner(std::array<float, 12> &tuningSliders, bool inputBassTuning, int inputKeyboardBreak, int scaleCenter)
{
    tuningRef.setTuning(tuningSliders);
    keyboardBreak = inputKeyboardBreak;
    scaleCenterSetPitch = scaleCenter;
    bassTuning = inputBassTuning;

}

void SynthVoice::updatePan(float width)
{
    panWidth = width / 100;
    panGain = voicePan * panWidth;
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{

    //SETUP
    //-------------------------------------------------------------
    if (!isVoiceActive())
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    rightBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    adsrBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    adsrRouting.setRoutingState(modRouting.getRoutingState());

    int sampNumber = synthBuffer.getNumSamples();

    //We need to include our modAdsr in the buffer for it to work
    //but at this stage of the buffer, it does no processing!

    synthBuffer.clear();
    rightBuffer.clear();

    for (int i = 0; i < sampNumber; i++)
    {
        adsrRouting.updateModValues(modAdsr.getNextSample());
        modRouting.updateModValues(modAdsr.getNextSample());
        vibrato.setFreq(modRouting.modulateValue(vibFreqMod, vibratoFrequency));
        vibrato.updateLfo(1, modRouting.modulateValue(vibDepthMod, vibratoDepth));
        vibratoSample = vibrato.getNextSample();

    }
    genCtrl.setParamValue("noiseLevel", modRouting.modulateValue(gen1NoiseMod, leftNoiseLevel));
    genCtrlRight.setParamValue("noiseLevel", modRouting.modulateValue(gen2NoiseMod, rightNoiseLevel));
    noiseCtrl.setParamValue("tone", modRouting.modulateValue(noise1ToneMod, leftNoiseTone));
    noiseCtrlRight.setParamValue("tone", modRouting.modulateValue(noise2ToneMod, rightNoiseTone));

    modAdsr.applyEnvelopeToBuffer(adsrBuffer, 0, sampNumber);

    //Updating our tuning in real time
    tunedMidi = tuningRef.alterMidiPitch(getCurrentlyPlayingNote());
    vibratoMidi = vibratoDepth * vibratoSample;
    processedMidi = tunedMidi + vibratoMidi + modRouting.modulateValue(detuneMod, synthDetune);

    oscMidi = processedMidi;


    oscFreq = std::fmax(std::fmin(tuningRef.midiToHertz(oscMidi), 20000.f), 22.f);

    //-------------------------------------------------------------

    float** synthData = (float**)synthBuffer.getArrayOfWritePointers();
    float** rightData = (float**)rightBuffer.getArrayOfWritePointers();

    auto audioBlock = juce::dsp::AudioBlock<float>{ synthBuffer };
    auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);

    //OSCILLATORS
    //-------------------------------------------------------------
    //Selector for different synthesizers
    if (!bassTuning)
    {
        tuningRef.updateScaleCenter(scaleCenterSetPitch);
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
    }
    else if (getCurrentlyPlayingNote() > keyboardBreak)
    {
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
    }
    else
    {
        tuningRef.updateScaleCenter(getCurrentlyPlayingNote() % 12);
        controlMidi = getCurrentlyPlayingNote() % 12;
    }

    //PROCESS
    //-------------------------------------------------------------
    //Filter with distortion

    synthBuffer.applyGain(tempVelocity);
    rightBuffer.applyGain(tempVelocity);

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
        endMix = modRouting.modulateValue(mixMod, leftRightMix);
        leftMixGain = ((endMix - 1) / 2) * (-1);
        rightMixGain = (endMix + 1) / 2;
    }

    synthBuffer.applyGainRamp(0, sampNumber, startMixL, leftMixGain);
    rightBuffer.applyGainRamp(0, sampNumber, startMixR, rightMixGain);

    startMixL = leftMixGain;
    startMixR = rightMixGain;


    for (int i = 0; i < sampNumber; i++)
    {
        for (int ch = 0; ch < synthBuffer.getNumChannels(); ch++)
        {
            synthBuffer.addSample(ch, i, rightBuffer.getSample(ch, i));
        }
    }

    for (int ch = 0; ch < synthBuffer.getNumChannels(); ch++)
    {
        if (ch == 0)
        {
            synthBuffer.applyGainRamp(ch, 0, sampNumber, (-oldPanGainL / 2) + 0.5, (-panGain / 2) + 0.5);
            oldPanGainL = panGain;
        }
        if (ch == 1)
        {
            synthBuffer.applyGainRamp(ch, 0, sampNumber, (oldPanGainR / 2) + 0.5, (panGain / 2) + 0.5);
            //synthBuffer.applyGainRamp(ch, 0, sampNumber, 0, 0);
            oldPanGainR = panGain;
        }
        
    }

    if (isVoiceFilt)
    {
        for (int samp = 0; samp < sampNumber; samp++)
        {
            juceLopFilt.setCutoffFrequency(tuningRef.midiToHertz(
                adsrRouting.modulateValue(lopCutoffMod, tuningRef.hertzToMidi(lopCutoff))));
            juceLopFilt.setResonance(adsrRouting.modulateValue(lopQMod, lopQ));
        }

        if (lopEnabled) juceLopFilt.process(context);
    }

    if (isVoiceHip)
    {
        for (int samp = 0; samp < sampNumber; samp++)
        {
            juceHipFilt.setCutoffFrequency(tuningRef.midiToHertz(
                adsrRouting.modulateValue(hipCutoffMod, tuningRef.hertzToMidi(hipCutoff))));
            juceHipFilt.setResonance(adsrRouting.modulateValue(hipQMod, hipQ));
        }

        if (hipEnabled) juceHipFilt.process(context);
    }

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

int SynthVoice::getMidiNote()
{
    int controlMod = controlNote % 12;
    if (controlNote != 0)
        return controlMod;
}