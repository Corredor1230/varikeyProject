/*
  ==============================================================================

    NoteTuning.h
    Created: 24 Mar 2022 5:25:44am
    Author:  User

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <vector>

class NoteTuning
{
public:
    enum notes {
        c = 0,
        ces,
        d,
        des,
        e,
        f,
        fes,
        g,
        ges,
        a,
        aes,
        b,
        numNotes
    };


    float alterMidiPitch(int midiPitch);

    float midiToHertz(const float midiNoteNumber);

    int getModulus(const int midiNoteNumber);

    void setTuning(std::array<float, 12>& tuning);


private:

    std::array<float, 12> noteTuning;

};

