/*
  ==============================================================================

    LfoOsc.h
    Created: 21 May 2022 6:03:24am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include"Oscillator.h"

class LfoOsc : public Oscillator
{
public:

    LfoOsc() {};

    float getNextSample() override;
};