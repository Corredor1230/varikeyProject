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
    float newMidi{0};
    std::array<float, 12> modifier = noteTuning;
    //std::array<float, 12> modifier;
    for (int i = 0; i < 12; i++)
    {
        if (pitchModulus == i)
        {
            //modifier[i] = noteTuning[i];
            newMidi = midiPitch + modifier[i];
        }
    }


    DBG(newMidi);

    return newMidi;
}

void NoteTuning::setTuning(std::array<float, 12>& tuning)
{
    //for (int i = 0; i < 12; i++)
    //{
    //    noteTuning[i] = tuning[i];
    //}

    noteTuning = tuning;
}

float NoteTuning::midiToHertz(const float midiNoteNumber)
{
    float hertz = 440.f * pow(2.f, (midiNoteNumber - 69.f) / 12.f);
    return hertz;
}