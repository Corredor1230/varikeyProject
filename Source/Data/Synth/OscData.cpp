/*
  ==============================================================================

    OscData.cpp
    Created: 24 Mar 2022 3:30:14am
    Author:  User

  ==============================================================================
*/

#include "OscData.h"



void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    prepare(spec);
}

void OscData::setWaveType(const int choice)
{

    switch (choice) 
    {
    case 0:
        initialise([](float x) {return std::sin(x); });
        break;
    case 1:
        initialise([](float x) {return x / juce::MathConstants<float>::pi; });
        break;
    case 2:
        initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });
        break;

    default:
        jassertfalse; //Something went wrong
        break;
    }
}

void OscData::setWaveFrequency(const float frequency)
{
    setFrequency(frequency);
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    for (int ch = 0; ch < block.getNumChannels(); ch++)
    {
        for (int sa = 0; sa < block.getNumSamples(); sa++)
        {
            currentSample = block.getSample(ch, sa);
        }
    }
    process(juce::dsp::ProcessContextReplacing<float>(block));

}

float OscData::getCurrentSample()
{
    return currentSample;
}