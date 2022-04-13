/*
  ==============================================================================

    Oscillator.h
    Created: 12 Apr 2022 4:02:56pm
    Author:  User

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

class Oscillator
{
public:
    Oscillator() {};
    void init(float sampleRate);
    void setFreq(float freq);
    forcedinline void updateAngle() noexcept;
    float getNextSample();
    void updateLfo(float waveValue, float depth);

private:
    float currentAngle = 0.0;
    float angleDelta = 0.0;
    double currentSampleRate = 0.0;
    float waveShape = 1.0;
    float lfoDepth = 1.0;
};