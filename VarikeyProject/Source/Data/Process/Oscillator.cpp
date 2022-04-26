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
    angleDelta = cyclesPerSample * juce::MathConstants<float>::twoPi;
}

forcedinline void Oscillator::updateAngle() noexcept
{
    currentAngle += angleDelta;
    // esto es un caso de branching innecesario
    // la ventaja es q no calculas las resta cada vez q esto se llama, pero la desventaja es q el calculo en algunas iteraciones es mayor (obviamente es un caso trivial y no hace diferencia en la práctica)
    // por ejemplo uno podría siempre llamar
    // currentAngle = mod(currentAngle + angDelta, 2 * M_PI);
    if (currentAngle >= juce::MathConstants<float>::twoPi)
        currentAngle -= juce::MathConstants<float>::twoPi;
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
    float sineLimit = juce::jlimit<float>(-1.0f, 1.0f, shapedWave);
    float outputSignal = sineLimit * lfoDepth;
    updateAngle();
    return outputSignal;
}
