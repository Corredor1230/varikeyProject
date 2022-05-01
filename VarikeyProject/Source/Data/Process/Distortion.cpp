/*
  ==============================================================================

    Distortion.cpp
    Created: 30 Apr 2022 2:32:49pm
    Author:  juanp

  ==============================================================================
*/

#include "Distortion.h"

void Distortion::updateDistortion(float input, float output)
{
    inputGain = input;
    outputGain = output;
}

void Distortion::process(juce::AudioBuffer<float>& inputBuffer, int channel, int sample)
{
    inputSample = inputBuffer.getSample(channel, sample);
    distSample = (std::fmax(0.f, std::fmin(1.f, std::tanh(inputSample * inputGain))));
    limitedInput = std::fmax(1.f, std::fmin(21.f, inputGain));
    gainReduction = ((limitedInput - 1) * 0.15) + 1;
    normalizeValue = ((std::fmax(1.f, std::fmin(3.f, inputGain)) - 1) / 2) + 1;
    outputSample = ((distSample * outputGain) / gainReduction) * 2 / normalizeValue;
    (inputGain == 0) ? inputBuffer.setSample(channel, sample, inputSample * minInputValue * outputGain) : 
        inputBuffer.setSample(channel, sample, outputSample);
}