/*
  ==============================================================================

    Distortion.h
    Created: 30 Apr 2022 2:32:49pm
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include<iostream>
#include<JuceHeader.h>

class Distortion
{
public:
    Distortion() {};

    void updateDistortion(float inputGain, float outputGain);
    void process(juce::AudioBuffer<float>& inputBuffer, int channel, int sample);

private:

    float inputGain = 0;
    float outputGain = 0;
    float inputSample = 0;
    float distSample = 0;
    float outputSample = 0;
    float minInputValue = 0.1;
    float limitedInput = 0;
    float gainReduction = 0;
    float normalizeValue = 0;
};