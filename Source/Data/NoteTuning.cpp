/*
  ==============================================================================

    NoteTuning.cpp
    Created: 24 Mar 2022 5:25:44am
    Author:  User

  ==============================================================================
*/

#include "NoteTuning.h"


int NoteTuning::getModulus(const int midiNoteNumber)
{
    int pitchModulus = midiNoteNumber % 12; //Number of different pitches
    return pitchModulus;
}

float NoteTuning::alterMidiPitch(int midiPitch)
{
    int pitchModulus = getModulus(midiPitch);
    float newMidi{};
    for (int i = 0; i < 12; i++)
    {
        if (pitchModulus == i)
        {
            newMidi = midiPitch + noteTuning[i];
        }
    }

    return newMidi;
}

void NoteTuning::setTuning(notes note, float tuning)
{
    noteTuning[note] = tuning;
}

float NoteTuning::midiToHertz(const float midiNoteNumber)
{
    float hertz = 440.f * pow(2.f, (midiNoteNumber - 69.f) / 12.f);
    return hertz;
}