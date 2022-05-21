/*
  ==============================================================================

    LfoOsc.cpp
    Created: 21 May 2022 6:03:24am
    Author:  juanp

  ==============================================================================
*/

#include "LfoOsc.h"

float LfoOsc::getNextSample()
{
    float sineSample = sin(currentAngle);
    float shapedWave = waveShape * sineSample;
    float sineLimit = std::max(-1.0f, std::min(1.0f, shapedWave));
    float outputSignal = sineLimit;
    updateAngle();
    return outputSignal;
}