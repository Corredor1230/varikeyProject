/*
  ==============================================================================

    TuningPresets.cpp
    Created: 17 May 2022 8:27:03pm
    Author:  juanp

  ==============================================================================
*/

#include "TuningPresets.h"

std::array<float, 12> TuningPresets::getPreset(tuningPresets preset)
{
    switch (preset)
    {
    case equalTemperament:
        return equalArray;
    case just:
        return justArray;
    case pythagorean:
        return pythagoreanArray;
    case quarterMeantone:
        return quarterMeantoneArray;
    case werckmeister:
        return werckmeisterArray;
    default:
        return equalArray;
    }
}

void TuningPresets::setPreset(tuningPresets preset = equalTemperament)
{
    switch (preset)
    {
    case equalTemperament:
        currentPreset = equalArray;
    case just:
        currentPreset = justArray;
    case pythagorean:
        currentPreset = pythagoreanArray;
    case quarterMeantone:
        currentPreset = quarterMeantoneArray;
    case werckmeister:
        currentPreset = werckmeisterArray;
    default:
        currentPreset = equalArray;
    }
}

void TuningPresets::setPreset(int preset = 0)
{
    switch (preset)
    {
    case 0:
        currentPreset = equalArray;
    case 1:
        currentPreset = justArray;
    case 2:
        currentPreset = pythagoreanArray;
    case 3:
        currentPreset = quarterMeantoneArray;
    case 4:
        currentPreset = werckmeisterArray;
    default:
        currentPreset = equalArray;
    }
}

void TuningPresets::setValueTreeValues(juce::AudioProcessorValueTreeState& valueTree, juce::StringArray paramIDs, std::array<float, 12> tuningArray)
{
    for (int i = 0; i < paramIDs.size(); i++)
    {
        valueTree.getParameterAsValue(paramIDs[i]).setValue(currentPreset[i] + tuningArray[i]);
    }
}