/*
  ==============================================================================

    TuningPresets.h
    Created: 17 May 2022 8:27:03pm
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include<iostream>
#include<array>
#include<JuceHeader.h>

class TuningPresets
{
public:

    typedef std::array<float, 12> presetArray;

    TuningPresets() {};

    enum tuningPresets
    {
        equalTemperament = 0,
        just,
        pythagorean,
        quarterMeantone,
        werckmeister,
        marimba1,
        marimba2,
        marimba3,
        slendro
    };

    std::array<float, 12> getPreset(tuningPresets preset);
    std::array<float, 12> getCurrentPreset();
    void setPreset(tuningPresets preset);
    void setPreset(int preset);
    void setValueTreeValues(juce::AudioProcessorValueTreeState& valueTree, juce::StringArray paramIDs, std::array<float, 12> tuningArray);

private:

    presetArray currentPreset;
    presetArray justArray{ 0, 0.12, 0.04, 0.16, -0.14, -0.02, -0.17, 0.02, 0.14, -0.16, -0.04, -0.12 };
    presetArray equalArray{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    presetArray pythagoreanArray{ 0, -0.1, 0.04, -0.06, 0.08, -0.02, 0.12, 0.02, -0.08, 0.06, -0.04, 0.1 };
    presetArray quarterMeantoneArray{ 0, -0.24, -0.07, 0.10, -0.14, 0.03, -0.21, -0.03, -0.27, -0.10, 0.07, -0.17 };
    presetArray werckmeisterArray{ 0, -0.10, -0.08, -0.06, -0.10, -0.02, 0.12, -0.04, -0.08, -0.12, -0.04, -0.08 };
    presetArray marimba1Array{ 0, 0, +0.10, 0, +0.20, 0, -0.50, +0.20, 0, -0.10, 0, -0.20 };
    presetArray marimba2Array{ 0, +0.40, 0, -0.15, +0.25, 0, -0.15, 0, -0.15, +0.25, 0, +0.05 };
    presetArray marimba3Array{ 0, 0, -0.20, +0.40, 0, -0.10, 0, -0.30, +0.20, 0, -0.20, 0 };
    presetArray slendroArray{ 0, 0, 0.20, 0, 0.86, 0, 0, 0.13, 0, 0.46, 0, 0 };
};
