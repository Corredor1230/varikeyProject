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
    DBG("Start Note Called");

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

    if (!allowTailOff || !adsr.isActive())
    {
        genCtrl.setParamValue("gate", false);
        additiveCtrl.setParamValue("gate", false);
        karpCtrl.setParamValue("gate", false);
        noiseCtrl.setParamValue("gate", false);

        genCtrlRight.setParamValue("gate", false);
        additiveCtrlRight.setParamValue("gate", false);
        karpCtrlRight.setParamValue("gate", false);
        noiseCtrlRight.setParamValue("gate", false);

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
    genCtrl.setParamValue("waveShape", genShape);
}

void SynthVoice::updateRightGenerator(int genShape, float noiseLevel, int noiseShape)
{

}

void SynthVoice::updateLeftAdditive(std::array<float, 9> additiveLeft)
{

}

void SynthVoice::updateRightAdditive(std::array<float, 9> additiveRight)
{

}

void SynthVoice::updateLeftKarplus(float karpAttack, float karpRelease, float karpFeedback, int karpNoise)
{

}

void SynthVoice::updateRightKarplus(float karpAttack, float karpRelease, float karpFeedback, int karpNoise)
{

}

void SynthVoice::updateLeftNoise(float synthTone)
{

}

void SynthVoice::updateRightNoise(float synthTone)
{

}

void SynthVoice::updateChoice(int leftChoice, int rightChoice, float synthMix)
{

}



void SynthVoice::update()
{

}


void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{

    //SETUP
    //-------------------------------------------------------------
    // muy bien esto!
    if (!isVoiceActive())
        return;

    // esto aun no me convence XD
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    lfoBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);

    //We need to include our modAdsr in the buffer for it to work
    //but at this stage of the buffer, it does no processing!
    modAdsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    //Gets modAdsr next value to control other parameters in real time
    modAdsrSample = modAdsr.getNextSample();


    //Gets modOsc next value to control other parameters in real time

    //Gets modOsc next value to control other parameters in real time
    //Just like with modAdsr we need to pass it our buffer for it to work
    for (int i = 0; i < lfoBuffer.getNumSamples(); i++)
    {
        lfoSample = lfo1Mod.getNextSample();
    }

    synthBuffer.clear();


    //Creating an AudioBlock type object to use the dsp::gain.process function
    // No se necesita la sintaxis con brackets {, obvio no hace diferencia pero
    // estas diciendo q vas a hacer un list initializer con el audio block cuando
    // en realidad hay un constructor dedicado para un AudioBuffer
    //    juce::dsp::AudioBlock<float> audioBlock( synthBuffer );
    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };

    //Updating our tuning in real time
    float newMidi = tuningRef.alterMidiPitch(getCurrentlyPlayingNote());
    float oscFreq = tuningRef.midiToHertz(newMidi + (1 * lfoSample));
    //-------------------------------------------------------------


    //OSCILLATORS
    //-------------------------------------------------------------
    //Selector for different synthesizers
    switch (synthSelector)
    {
    case 0:
        karpCtrl.setParamValue("freq", oscFreq);
        // creo q en varias partes estás llamando getArrayOfWritePointers() pero
        // sería más facil de leer si arriba de todo esto hubiera un
        // float** synthData = synthBuffer.getArrayOfWritePoints();
        // int numSamples = synthBuffer.getNumSamples();
        karplusSynth.compute(synthBuffer.getNumSamples(), nullptr, synthBuffer.getArrayOfWritePointers());
        break;
    case 1:
        genCtrl.setParamValue("freq", oscFreq);
        genSynth.compute(synthBuffer.getNumSamples(), nullptr, synthBuffer.getArrayOfWritePointers());
        synthBuffer.applyGain(0.2);
        break;
    }




    //PROCESS
    //-------------------------------------------------------------
    //Filter with distortion
    if (vts.getParameterAsValue("filterOnOff").getValue())
    {
        filter.compute(synthBuffer.getNumSamples(), synthBuffer.getArrayOfWritePointers(), synthBuffer.getArrayOfWritePointers());
    }

    //Gain control
    // otra vez innecesario existiendo buffer.applyGain()
    synthBuffer.applyGain(finalGain);

    //Amp adsr control
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
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