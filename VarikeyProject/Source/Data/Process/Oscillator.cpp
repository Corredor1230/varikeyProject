/*
  ==============================================================================

    Oscillator.cpp
    Created: 12 Apr 2022 4:02:56pm
    Author:  User

  ==============================================================================
*/

#include "Oscillator.h"

void Oscillator::init(float sampleRate)
{
    currentSampleRate = sampleRate;

}

void Oscillator::setFreq(float freq)
{
    auto cyclesPerSample = freq / currentSampleRate;
    angleDelta = cyclesPerSample * 2 * M_PI;
}

//forcedinline 
void Oscillator::updateAngle() noexcept
{
    currentAngle += angleDelta;
    if (currentAngle >= M_PI * 2)
        currentAngle -= M_PI * 2;
}

void Oscillator::updateLfo(float waveValue, float depth)
{
    waveShape = waveValue;
    lfoDepth = depth;
}

void Oscillator::updateLfo(float waveValue)
{
    waveShape = waveValue;
}

float Oscillator::getNextSample() 
{
    float sineSample = sin(currentAngle);
    float shapedWave = waveShape * sineSample;
    float sineLimit = std::max(-1.0f, std::min(1.0f, shapedWave));
    float outputSignal = sineLimit * lfoDepth;
    updateAngle();
    return outputSignal;
}
