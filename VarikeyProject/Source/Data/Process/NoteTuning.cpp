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
    // usar numNotes en cambio de 12
    int pitchModulus = midiNoteNumber % 12; //Number of different pitches
    return pitchModulus;
}

void NoteTuning::updateScaleCenter(int center)
{
    scaleCenter = center;
}

float NoteTuning::alterMidiPitch(int midiPitch)
{
    int pitchModulus = getModulus(midiPitch - scaleCenter);
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

    // cuidado q esto está en el process block supongo
    DBG(newMidi);

    return newMidi;
}

// incluso acá puedes usar numNotes
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
    // no debería hacer muuuucha diferencia pero existe exp2
    float hertz = 440.f * pow(2.f, (midiNoteNumber - 69.f) / 12.f);
    return hertz;
}
