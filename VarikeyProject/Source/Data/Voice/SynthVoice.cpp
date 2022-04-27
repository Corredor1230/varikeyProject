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

    //Gate for karplus synth window
    karpCtrl.setParamValue("gate", true);
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

    filter.init(sampleRate);
    filter.buildUserInterface(&filtCtrl);

    adsr.setSampleRate(sampleRate);
    modAdsr.setSampleRate(sampleRate);
    lfoMod.init(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

}

void SynthVoice::updateAdsr(const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::updateModAdsr(const float attack, const float decay, const float sustain, const float release)
{
    modAdsr.updateADSR(attack, decay, sustain, release);
}


/*
    updateGeneric updates general synth control parameters
    this includes gain and synth selector controls.
    Function receives integer and float parameter arrays
    in order to remain viable even if further parameters
    are added in future versions.
*/
void SynthVoice::updateGeneric(std::array<int, 1> integers, std::array<float, 1> floats)
{
    synthSelector = integers[0];
    finalGain = tempVelocity * floats[0];
}


/*
    updateKarplus updates the Karplus synth parameters
    it takes a feedback parameter, as well as an integer array
    containing its window Attack and Release parameters
    as well as its FM Synth depth and index parameters.
*/
void SynthVoice::updateKarplus(float kFeed, std::array<int, 5> integers)
{
    // no me suena q esto sea conceptualmente un array...
    // son los parámetros pero creo q conceptualmente no debería ser un array
    karpCtrl.setParamValue("kFeed", kFeed);
    karpCtrl.setParamValue("kAtt", integers[0]);
    karpCtrl.setParamValue("kRel", integers[1]);
    karpCtrl.setParamValue("kSwitch", integers[2]);
    karpCtrl.setParamValue("fmDepth", integers[3]);
    karpCtrl.setParamValue("fmIndex", integers[4]);
}

/*
    updateFilter takes a cutoff and q argument
    Cutoff controls the filter's cutoff frequency in real time
    Q controls its quality factor in real time
    There are also fixed distGain and distOut parameters
    These can be changed from the code directly but not controlled.
    They shape the sound of the filter and add color
    to the instrument.
*/
void SynthVoice::updateFilter(int cutoff, float q)
{
    // creo q conceptualmente cutoff no deberia ser int
    float tempCutoff = cutoff * modAdsrSample;
    float cutoffFreq = std::max(tempCutoff, 20.f);
    filtCtrl.setParamValue("cutoff", cutoffFreq);
    filtCtrl.setParamValue("q", q);
    filtCtrl.setParamValue("distGain", 0.1);
    filtCtrl.setParamValue("distOut", 0.7);
}

/*
* updateOscMod sets the default wave shape as sin(x)
* while also updating its shape and depth parameters
* to a member variable for further use in other
* methods. 
* 
*/
void SynthVoice::updateOscMod(float freq, float shape, float depth)
{
    //modOsc.setWaveType(0);
    //modOsc.setWaveFrequency(freq);
    oscModShape = shape;
    oscModDepth = depth;
}


void SynthVoice::updateLfo(float freq, float wave, float depth)
{
    lfoMod.setFreq(freq);
    lfoMod.updateLfo(wave, depth);
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
        lfoSample = lfoMod.getNextSample();
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