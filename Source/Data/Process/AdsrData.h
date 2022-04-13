/*
  ==============================================================================

    AdsrData.h
    Created: 23 Mar 2022 12:03:45pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    // no overrides?
    void updateADSR(const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParams;
};
