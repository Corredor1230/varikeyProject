/*
  ==============================================================================

    EmbeddedFonts.h
    Created: 8 Apr 2022 11:39:18am
    Author:  juanp

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

class EmbeddedFonts
{
public:

    enum fontStyle
    {
        regular = 0,
        bold,
        italic,
        medium,
        semi
    };

    EmbeddedFonts();
    juce::Font& getJosefinSans();
    juce::Font& getCurrentFont();
    juce::Typeface::Ptr getCurrentTypeface();
    void setFontSizeAndStyle(float height, const juce::String& style, 
        float horizontal, float kerning);
    void setFontStyle(const juce::String& style);
private:

    void loadFontAndTypeface();
    int fontStyle = 0;

    juce::Font currentFont;
    juce::Typeface::Ptr currentTypeface;

    juce::Font josefinSansRegular;
    juce::Font josefinSansBold;
    juce::Font josefinSansItalic;
    juce::Font josefinSansMedium;
    juce::Font josefinSansSemi;

    juce::Typeface::Ptr jSansRegularTypeface;
    juce::Typeface::Ptr jSansBoldTypeface;
    juce::Typeface::Ptr jSansItalicTypeface;
    juce::Typeface::Ptr jSansMediumTypeface;
    juce::Typeface::Ptr jSansSemiTypeface;


};