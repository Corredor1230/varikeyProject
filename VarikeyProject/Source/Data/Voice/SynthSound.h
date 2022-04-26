/*
  ==============================================================================

    SynthSound.h
    Created: 22 Mar 2022 10:48:21pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};