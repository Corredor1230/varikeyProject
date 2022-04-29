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
    noiseCtrlRight.setParamValue("gate", false);

    adsr.noteOn();
    modAdsr.noteOn();

    //Copies velocity to global tempVelocity variable for real time control
    tempVelocity = velocity;
    
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    modAdsr.noteOff();
        genCtrl.setParamValue("gate", false);
        additiveCtrl.setParamValue("gate", false);
        karpCtrl.setParamValue("gate", false);
        noiseCtrl.setParamValue("gate", false);

        genCtrlRight.setParamValue("gate", false);
        additiveCtrlRight.setParamValue("gate", false);
        karpCtrlRight.setParamValue("gate", false);
        noiseCtrlRight.setParamValue("gate", false);


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
    //synthBuffer.setSize(outputChannels, samplesPerBlock, false, false, true);

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



    adsr.setSampleRate(sampleRate);
    modAdsr.setSampleRate(sampleRate);
    lfo1Mod.init(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

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
    additiveCtrl.setParamValue("eighth", additiveLeft[7]);

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
}



void SynthVoice::updateLeftFm(float ratio, float depth)
{

}

void SynthVoice::updateRightFm(float ratio, float depth)
{

}

void SynthVoice::updateLopFilter(bool isEnabled, float cutoff, float q)
{
    filtCtrl.setParamValue("lopOnOff", isEnabled);
    filtCtrl.setParamValue("lopCutoff", cutoff);
    filtCtrl.setParamValue("lopQ", q);
}

void SynthVoice::updateHipFilter(bool isEnabled, float cutoff, float q)
{
    filtCtrl.setParamValue("hipOnOff", isEnabled);
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
}

void SynthVoice::updateLfo2(float freq, float depth, float shape, int route)
{
    lfo2Freq = freq;
    lfo2Depth = depth;
    lfo2Shape = shape;
    lfo2Route = route;
}

void SynthVoice::updateLfo3(float freq, float depth, float shape, int route)
{
    lfo3Freq = freq;
    lfo3Depth = depth;
    lfo3Shape = shape;
    lfo3Route = route;
}

void SynthVoice::updateLfo4(float freq, float depth, float shape, int route)
{
    lfo4Freq = freq;
    lfo4Depth = depth;
    lfo4Shape = shape;
    lfo4Route = route;
}

void SynthVoice::updateGlobal(float detune, float vibFreq, float vibDepth, float volume)
{
    synthDetune = detune;
    vibratoFrequency = vibFreq;
    vibratoDepth = vibDepth;
    synthVolume = volume;
}

void SynthVoice::updateTuner(std::array<float, 12> tuningSliders, bool bassTuning, int keyboardBreak, int scaleCenter)
{
    tuningRef.setTuning(tuningSliders);
}

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

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{

    //SETUP
    //-------------------------------------------------------------
    // muy bien esto!
    if (!isVoiceActive())
        return;

    // esto aun no me convence XD
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    //lfoBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);

    ////We need to include our modAdsr in the buffer for it to work
    ////but at this stage of the buffer, it does no processing!
    modAdsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    ////Gets modAdsr next value to control other parameters in real time
    modAdsrSample = modAdsr.getNextSample();


    ////Gets modOsc next value to control other parameters in real time

    ////Gets modOsc next value to control other parameters in real time
    ////Just like with modAdsr we need to pass it our buffer for it to work
    for (int i = 0; i < lfoBuffer.getNumSamples(); i++)
    {
        lfoSample = lfo1Mod.getNextSample();
    }

    synthBuffer.clear();

    float** synthData = synthBuffer.getArrayOfWritePointers();
    int sampNumber = synthBuffer.getNumSamples();

    //Creating an AudioBlock type object to use the dsp::gain.process function
    // No se necesita la sintaxis con brackets {, obvio no hace diferencia pero
    // estas diciendo q vas a hacer un list initializer con el audio block cuando
    // en realidad hay un constructor dedicado para un AudioBuffer
    //    juce::dsp::AudioBlock<float> audioBlock( synthBuffer );

    //Updating our tuning in real time
    float newMidi = tuningRef.alterMidiPitch(getCurrentlyPlayingNote());
    float oscFreq = tuningRef.midiToHertz(newMidi);
    //-------------------------------------------------------------

    //float oscFreq = tuningRef.midiToHertz(getCurrentlyPlayingNote());


    //OSCILLATORS
    //-------------------------------------------------------------
    //Selector for different synthesizers
    switch (0)
    {
    case 0:
        genCtrl.setParamValue("freq", oscFreq);
        // creo q en varias partes estás llamando getArrayOfWritePointers() pero
        // sería más facil de leer si arriba de todo esto hubiera un
        // float** synthData = synthBuffer.getArrayOfWritePoints();
        // int numSamples = synthBuffer.getNumSamples();
        genSynth.compute(sampNumber, nullptr, synthBuffer.getArrayOfWritePointers());
        break;
    case 1:
        additiveCtrl.setParamValue("freq", oscFreq);
        additiveSynth.compute(sampNumber, nullptr, synthBuffer.getArrayOfWritePointers());
        break;
    case 2:
        karpCtrl.setParamValue("freq", oscFreq);
        karplusSynth.compute(sampNumber, nullptr, synthBuffer.getArrayOfWritePointers());
        break;
    case 3:
        noiseCtrl.setParamValue("freq", oscFreq);
        noiseSynth.compute(sampNumber, nullptr, synthBuffer.getArrayOfWritePointers());
        break;
    }

    //genCtrl.setParamValue("freq", oscFreq);
    //genSynth.compute(synthBuffer.getNumSamples(), nullptr, synthBuffer.getArrayOfWritePointers());


    //PROCESS
    //-------------------------------------------------------------
    //Filter with distortion
    filter.compute(synthBuffer.getNumSamples(), synthBuffer.getArrayOfWritePointers(), synthBuffer.getArrayOfWritePointers());

    //Gain control
    // otra vez innecesario existiendo buffer.applyGain()
    synthBuffer.applyGain(1.0);

    //Amp adsr control
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    //-------------------------------------------------------------


    //CLEAR
    //-------------------------------------------------------------

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        //if (!adsr.isActive())
        //{
        //    clearCurrentNote();
        //}

        //clearCurrentNote();
    }
}