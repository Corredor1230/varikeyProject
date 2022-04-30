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
        //juce::MathConstants<float>::twoPi *;
}

//forcedinline 
void Oscillator::updateAngle() noexcept
{
    currentAngle += angleDelta;
    // currentAngle = mod(currentAngle + angDelta, 2 * M_PI);
    if (currentAngle >= M_PI * 2)
        //juce::MathConstants<float>::twoPi)
        currentAngle -= M_PI * 2;
        //juce::MathConstants<float>::twoPi;
}

void Oscillator::updateLfo(float waveValue, float depth)
{
    waveShape = waveValue;
    lfoDepth = depth;
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
