/*
  ==============================================================================

    EmbeddedFonts.h
    Created: 6 Apr 2022 10:42:54pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class EmbeddedFonts
{
public:

    EmbeddedFonts();
    juce::Font& getJosefinSans();
private:
    juce::Font josefinSans;
};