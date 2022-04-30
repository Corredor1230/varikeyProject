/*
  ==============================================================================

    Oscillator.h
    Created: 12 Apr 2022 4:02:56pm
    Author:  User

  ==============================================================================
*/

#pragma once
// otra cosa a notar es q internamente los samples son floats sin tanta razon, podrían ser doubles para q el acumulador fuera más preciso aun si retornaran floats
#define _USE_MATH_DEFINES
#include<cmath>
#include<iostream>

class Oscillator
{
public:
    Oscillator() {};
    void init(float sampleRate);
    void setFreq(float freq);
    // q se supone q hace el forcedinline?
    // esto es un macro q no es soportado por todos los compiladores y solo funciona como imagino q crees q funciona si la declaración está ahí mismo
    //forcedinline 
    void updateAngle() noexcept;
    float getNextSample();
    void updateLfo(float waveValue, float depth);

private:
    
    float currentAngle = 0.0;
    float angleDelta = 0.0;
    double currentSampleRate = 0.0;
    float waveShape = 1.0;
    float lfoDepth = 1.0;
};
