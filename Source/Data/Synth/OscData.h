/*
  ==============================================================================

    OscData.h
    Created: 24 Mar 2022 3:30:14am
    Author:  User

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    // humm... me sorprende q no haya overrides aca
    // también me pregunto porque usar un audio Block y no un audio Buffer
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void setWaveFrequency(const float frequency);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    float getCurrentSample();

private:

    float currentSample{};
};
