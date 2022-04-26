/*
  ==============================================================================

    EmbeddedFonts.cpp
    Created: 8 Apr 2022 11:39:18am
    Author:  juanp

  ==============================================================================
*/

#include "EmbeddedFonts.h"

EmbeddedFonts::EmbeddedFonts()
{
    //JosefinSans typeface initialization
    loadFontAndTypeface();
}

/*
* Returns josefinSans font.
* Parameters can be modified using setFontSizeAndStyle method.
* Default parameters return 16.f size plain font.
*/
juce::Font& EmbeddedFonts::getJosefinSans()
{
    switch (fontStyle)
    {
    case regular:
        return josefinSansRegular;
        break;
    case bold:
        return josefinSansBold;
        break;
    case italic:
        return josefinSansItalic;
        break;
    case medium:
        return josefinSansMedium;
        break;
    case semi:
        return josefinSansSemi;
        break;
    }
}

/*
* This method adds different possible styles for the josefinSans font.
* Style keywords include "plain", "bold", "italic", "medium" and "semi".
* Horizontal refers to spacing within the font. 1.f is the default.
* Kerning default is 0.f. Negative values create negative kerning.
*/
void EmbeddedFonts::setFontSizeAndStyle(float height, const juce::String& style, float horizontal, float kerning)
{
    if (style == "plain")
    {
        currentTypeface = jSansRegularTypeface;
        josefinSansRegular.setSizeAndStyle(height, 0, horizontal, kerning);
        currentFont = josefinSansRegular;
        fontStyle = regular;
    }
    else if (style == "bold")
    {
        currentTypeface = jSansBoldTypeface;
        josefinSansBold.setSizeAndStyle(height, 0, horizontal, kerning);
        currentFont = josefinSansBold;
        fontStyle = bold;
    }
    else if (style == "italic")
    {
        currentTypeface = jSansItalicTypeface;
        josefinSansItalic.setSizeAndStyle(height, 0, horizontal, kerning);
        currentFont = josefinSansItalic;
        fontStyle = italic;
    }
    else if (style == "medium")
    {
        currentTypeface = jSansMediumTypeface;
        josefinSansMedium.setSizeAndStyle(height, 0, horizontal, kerning);
        currentFont = josefinSansMedium;
        fontStyle = medium;
    }
    else if (style == "Semibold")
    {
        currentTypeface = jSansSemiTypeface;
        josefinSansSemi.setSizeAndStyle(height, 0, horizontal, kerning);
        currentFont = josefinSansSemi;
        fontStyle = semi;
    }
    else
    {
        currentTypeface = jSansRegularTypeface;
        josefinSansRegular.setSizeAndStyle(height, 0, horizontal, kerning);
        currentFont = josefinSansRegular;
        fontStyle = regular;
    }
}

/*Possible style strings
* "plain", "bold", "italic",
* "medium", "semi"
for font style */
void EmbeddedFonts::setFontStyle(const juce::String& style)
{
    if (style == "plain")
    {
        fontStyle = regular;
    }
    else if (style == "bold")
    {
        fontStyle = bold;
    }
    else if (style == "italic")
    {
        fontStyle = italic;
    }
    else if (style == "medium")
    {
        fontStyle = medium;
    }
    else if (style == "Semibold")
    {
        fontStyle = semi;
    }
    else
    {
        fontStyle = regular;
    }
}

/*Returns current font as a juce::Font object*/
juce::Font& EmbeddedFonts::getCurrentFont()
{
    return currentFont;
}

juce::Typeface::Ptr EmbeddedFonts::getCurrentTypeface()
{
    return currentTypeface;
}

void EmbeddedFonts::loadFontAndTypeface()
{
    jSansRegularTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::JosefinSansRegular_ttf,
        BinaryData::JosefinSansRegular_ttfSize);
    josefinSansRegular = juce::Font(jSansRegularTypeface);

    jSansBoldTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::JosefinSansBold_ttf,
        BinaryData::JosefinSansBold_ttfSize);
    josefinSansBold = juce::Font(jSansBoldTypeface);

    jSansItalicTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::JosefinSansItalic_ttf,
        BinaryData::JosefinSansItalic_ttfSize);
    josefinSansItalic = juce::Font(jSansItalicTypeface);

    jSansMediumTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::JosefinSansMedium_ttf,
        BinaryData::JosefinSansMedium_ttfSize);
    josefinSansMedium = juce::Font(jSansMediumTypeface);

    jSansSemiTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::JosefinSansSemiBold_ttf,
        BinaryData::JosefinSansSemiBold_ttfSize);
    josefinSansSemi = juce::Font(jSansSemiTypeface);
}