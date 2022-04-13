/*
  ==============================================================================

    EmbeddedFonts.cpp
    Created: 6 Apr 2022 10:42:54pm
    Author:  User

  ==============================================================================
*/

#include "EmbeddedFonts.h"
#include <JuceHeader.h>

EmbeddedFonts::EmbeddedFonts()
{
    josefinSans = juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::JosefinSansVariableFont_wght_ttf,
        BinaryData::JosefinSansVariableFont_wght_ttfSize));
}

juce::Font& EmbeddedFonts::getJosefinSans()
{
    return josefinSans;
}


