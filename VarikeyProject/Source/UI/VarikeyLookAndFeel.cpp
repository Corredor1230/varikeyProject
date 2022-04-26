/*
  ==============================================================================

    VarikeyLookAndFeel.cpp
    Created: 8 Apr 2022 11:37:15am
    Author:  juanp

  ==============================================================================
*/

#include<JuceHeader.h>
#include "VarikeyLookAndFeel.h"

using namespace juce;

VarikeyLookAndFeel::VarikeyLookAndFeel()
{
    setColourPalette(vaporwave);
    //These parameters define the font for most components
    //Modify them wisely!
    josefinSans.setFontSizeAndStyle(22.0f, "medium", 1.0f, 0.0f);
    comboFonts.setFontSizeAndStyle(10.0f, "italic", 1.0f, 0.0f);

    customFont = josefinSans.getCurrentFont();
    setDefaultSansSerifTypeface(josefinSans.getCurrentTypeface());
    setSliderPalette(currentPalette);
    setComponentPalette(currentPalette);
    labelBorder.setBottom(0);
    labelBorder.setTop(0);

}

VarikeyLookAndFeel::~VarikeyLookAndFeel()
{
}

ColourPalette VarikeyLookAndFeel::getColourPalette(palette paletteType)
{
    switch (paletteType)
    {
    case 0:
        ColourPalette vaporwave;
        vaporwave.activeElement = pink;
        vaporwave.inactiveElement= purp;
        vaporwave.highlightElement = pale;
        vaporwave.contrastDark= dark;
        vaporwave.globalLight = cyan;
        vaporwave.globalDark = black;
        return vaporwave;
    case 1:
        ColourPalette clean;
        clean.activeElement = orange;
        clean.inactiveElement = midGrey;
        clean.highlightElement = pale;
        clean.contrastDark = darkGrey;
        clean.globalLight = almostWhite;
        clean.globalDark = almostBlack;
        return clean;
    }
}

/*
Sets current palette to sliders globally.
Alpha must be manually introduced for this function.
*/
void VarikeyLookAndFeel::setSliderPalette(ColourPalette palette, float alpha)
{
    typedef juce::Slider::ColourIds colourIds;

    //Vertical slider
    setColour(colourIds::trackColourId, juce::Colour((juce::uint8)palette.activeElement[0],
        palette.activeElement[1], palette.activeElement[2], alpha));
    setColour(colourIds::backgroundColourId, juce::Colour((juce::uint8)palette.inactiveElement[0],
        palette.inactiveElement[1], palette.inactiveElement[2], alpha));
    setColour(colourIds::thumbColourId, getColourFromPalette(highlight, alpha));

    //Rotary slider
    setColour(colourIds::rotarySliderFillColourId, juce::Colour((juce::uint8)palette.activeElement[0],
        palette.activeElement[1], palette.activeElement[2], alpha));
    setColour(colourIds::rotarySliderOutlineColourId, juce::Colour((juce::uint8)palette.globalLight[0],
        palette.globalLight[1], palette.globalLight[2], alpha));

    //TextBox
    setColour(colourIds::textBoxBackgroundColourId, juce::Colour());
    setColour(colourIds::textBoxHighlightColourId, juce::Colour((juce::uint8)palette.activeElement[0],
        palette.activeElement[1], palette.activeElement[2], alpha));
    setColour(colourIds::textBoxOutlineColourId, juce::Colour((juce::uint8)0, 0, 0, 0.f));
    setColour(colourIds::textBoxTextColourId, getColourFromPalette(highlight, alpha));
    setColour(juce::TextEditor::ColourIds::textColourId, getColourFromPalette(highlight, alpha));


}

void VarikeyLookAndFeel::setColourPalette(palette paletteType)
{
    currentPalette = getColourPalette(paletteType);
}

/*
 Sets colours from current palette for various buttons and components.
*/
void VarikeyLookAndFeel::setComponentPalette(ColourPalette palette, float alpha)
{
    //ToggleButton Colour
    setColour(juce::ToggleButton::ColourIds::textColourId,getColourFromPalette(inactive, alpha));
    setColour(juce::ToggleButton::ColourIds::tickColourId, getColourFromPalette(active, alpha));
    setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, getColourFromPalette(contrast, alpha));

    //TabbedComponent Colour
    setColour(juce::TabbedComponent::ColourIds::backgroundColourId, getColourFromPalette(contrast, alpha));
    setColour(juce::TabbedComponent::ColourIds::outlineColourId, getColourFromPalette(highlight, alpha));
    setColour(juce::Label::ColourIds::textColourId, getColourFromPalette(highlight, alpha));
    setColour(juce::ResizableWindow::ColourIds::backgroundColourId, getColourFromPalette(gDark, alpha));

    //ComboBox Colour
    setColour(juce::ComboBox::ColourIds::backgroundColourId, getColourFromPalette(contrast, alpha));
    setColour(juce::ComboBox::ColourIds::arrowColourId, getColourFromPalette(highlight, alpha));
    setColour(juce::ComboBox::ColourIds::textColourId, getColourFromPalette(highlight, alpha));
    setColour(juce::ComboBox::ColourIds::buttonColourId, getColourFromPalette(active, alpha));
    setColour(juce::ComboBox::ColourIds::outlineColourId, getColourFromPalette(inactive, 0));
    setColour(juce::TextEditor::ColourIds::textColourId, getColourFromPalette(highlight, alpha));

    //Menu
    setColour(juce::PopupMenu::ColourIds::backgroundColourId, getColourFromPalette(contrast, alpha));
    setColour(juce::PopupMenu::ColourIds::textColourId, getColourFromPalette(highlight, alpha));
    setColour(juce::PopupMenu::ColourIds::highlightedBackgroundColourId, getColourFromPalette(inactive, alpha));
    setColour(juce::PopupMenu::ColourIds::highlightedTextColourId, getColourFromPalette(highlight, alpha));
}

/*
 String with possible colours from a standardized colour palette.
 Possible enums: active, inactive, highlight 
 contrast, gLight, gDark.
 Alpha parameter is optional.
 Returns colours from current palette.
*/
juce::Colour VarikeyLookAndFeel::getColourFromPalette(paletteColours colour, float alpha)
{
    juce::Colour activeColour;
    juce::Colour inactiveColour;
    juce::Colour highlightColour;
    juce::Colour contrastColour;
    juce::Colour gLightColour;
    juce::Colour gDarkColour;

    switch (colour)
    {
    case 0:
        activeColour = juce::Colour((juce::uint8)currentPalette.activeElement[0],
            currentPalette.activeElement[1], currentPalette.activeElement[2], alpha);
        return activeColour;
    case 1:
        inactiveColour = juce::Colour((juce::uint8)currentPalette.inactiveElement[0],
            currentPalette.inactiveElement[1], currentPalette.inactiveElement[2], alpha);
        return inactiveColour;
    case 2:
        highlightColour = juce::Colour((juce::uint8)currentPalette.highlightElement[0],
            currentPalette.highlightElement[1], currentPalette.highlightElement[2], alpha);
        return highlightColour;
    case 3:
        contrastColour = juce::Colour((juce::uint8)currentPalette.contrastDark[0],
            currentPalette.contrastDark[1], currentPalette.contrastDark[2], alpha);
        return contrastColour;
    case 4:
        gLightColour = juce::Colour((juce::uint8)currentPalette.globalLight[0],
            currentPalette.globalLight[1], currentPalette.globalLight[2], alpha);
        return gLightColour;
    case 5:
        gDarkColour = juce::Colour((juce::uint8)currentPalette.globalDark[0],
            currentPalette.globalDark[1], currentPalette.globalDark[2], alpha);
        return gDarkColour;
    default:
        jassertfalse;
    }

}


void VarikeyLookAndFeel::setFont(juce::Font& font)
{
    customFont = font;
}

juce::Font VarikeyLookAndFeel::getLabelFont(juce::Label& label)
{
    return customFont;
}

juce::Font VarikeyLookAndFeel::getComboBoxFont(juce::ComboBox& comboBox)
{
    juce::Font returnFont = comboFonts.getCurrentFont();
    return returnFont;
}

juce::BorderSize<int> VarikeyLookAndFeel::getLabelBorderSize(juce::Label& label)
{
    labelBorder = juce::BorderSize<int>::BorderSize(0, 0, 0, 0);
    label.setBorderSize(labelBorder);
    return label.getBorderSize();
}


void VarikeyLookAndFeel::setDistanceToSlider(float distance, juce::String& type)
{
    if (type == "vertical") verticalDistanceToSlider = distance;
    else if (type == "horizontal") horizontalDistanceToSlider = distance;
}


juce::Slider::SliderLayout VarikeyLookAndFeel::getSliderLayout(juce::Slider& slider)
{
    // 1. compute the actually visible textBox size from the slider textBox size and some additional constraints

    int minXSpace = 0;
    int minYSpace = 0;

    auto textBoxPos = slider.getTextBoxPosition();

    if (textBoxPos == juce::Slider::TextBoxLeft || textBoxPos == juce::Slider::TextBoxRight)
        minXSpace = 30;
    else
        minYSpace = 15;

    juce::Rectangle<int> localBounds = slider.getLocalBounds();

    auto textBoxWidth = juce::jmax(0, juce::jmin(slider.getTextBoxWidth(), localBounds.getWidth() - minXSpace));
    auto textBoxHeight = juce::jmax(0, juce::jmin(slider.getTextBoxHeight(), localBounds.getHeight() - minYSpace));

    juce::Slider::SliderLayout layout;

    // 2. set the textBox bounds

    if (textBoxPos != juce::Slider::NoTextBox)
    {
        if (slider.isBar())
        {
            layout.textBoxBounds = localBounds;
        }
        else
        {
            layout.textBoxBounds.setWidth(textBoxWidth);
            layout.textBoxBounds.setHeight(textBoxHeight);

            if (textBoxPos == juce::Slider::TextBoxLeft) { 
                layout.textBoxBounds.setX(0);
                layout.textBoxBounds.removeFromBottom(3);
            }
            else if (textBoxPos == juce::Slider::TextBoxRight)     layout.textBoxBounds.setX(localBounds.getWidth() - textBoxWidth);
            else /* above or below -> centre horizontally */ layout.textBoxBounds.setX((localBounds.getWidth() - textBoxWidth) / 2);

            if (textBoxPos == juce::Slider::TextBoxAbove)          layout.textBoxBounds.setY(0);
            else if (textBoxPos == juce::Slider::TextBoxBelow)     layout.textBoxBounds.setY(localBounds.getHeight() - textBoxHeight);
            else /* left or right -> centre vertically */    layout.textBoxBounds.setY((localBounds.getHeight() - textBoxHeight) / 2);
        }
    }

    // 3. set the slider bounds

    layout.sliderBounds = localBounds;

    if (slider.isBar())
    {
        layout.sliderBounds.reduce(1, 1);   // bar border
    }
    else
    {
        if (textBoxPos == juce::Slider::TextBoxLeft)       layout.sliderBounds.removeFromLeft(textBoxWidth - 15 + horizontalDistanceToSlider);
        else if (textBoxPos == juce::Slider::TextBoxRight) layout.sliderBounds.removeFromRight(textBoxWidth);
        else if (textBoxPos == juce::Slider::TextBoxAbove) layout.sliderBounds.removeFromTop(textBoxHeight);
        else if (textBoxPos == juce::Slider::TextBoxBelow) layout.sliderBounds.removeFromBottom(textBoxHeight - 15 + verticalDistanceToSlider);

        const int thumbIndent = getSliderThumbRadius(slider);

        if (slider.isHorizontal())    layout.sliderBounds.reduce(thumbIndent, 0);
        else if (slider.isVertical()) layout.sliderBounds.reduce(0, thumbIndent);
    }

    return layout;
}

juce::PopupMenu::Options VarikeyLookAndFeel::getOptionsForComboBoxPopupMenu(juce::ComboBox& box, juce::Label& label)
{
    return juce::PopupMenu::Options().withTargetComponent(&box)
        .withItemThatMustBeVisible(box.getSelectedId())
        .withInitiallySelectedItem(box.getSelectedId())
        .withMinimumWidth(std::max(box.getWidth(), 70))
        .withMaximumNumColumns(1)
        .withStandardItemHeight(std::max(label.getHeight(), 22));
}

juce::Font VarikeyLookAndFeel::getPopupMenuFont()
{
    return customFont;
}

void VarikeyLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
    auto fill = slider.findColour(Slider::rotarySliderFillColourId);

    auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);

    auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = jmin(8.0f, radius * 0.3f);
    auto arcRadius = radius - lineW * 0.5f;
    auto centreX = width / 2;
    auto centreY = height / 2;

    Path backgroundArc;
    backgroundArc.addCentredArc(bounds.getCentreX(),
        bounds.getCentreY(),
        arcRadius,
        arcRadius,
        0.0f,
        rotaryStartAngle,
        rotaryEndAngle,
        true);

    g.setColour(outline);
    g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));

    if (slider.isEnabled())
    {
        Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            toAngle,
            true);

        g.setColour(fill);
        g.strokePath(valueArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));
    }

    auto thumbWidth = lineW * 2.4;
    auto thumbHeight = lineW;

    g.setColour(slider.findColour(Slider::ColourIds::thumbColourId));
    Path thumbTick;
    thumbTick.addRectangle(- thumbHeight / 2, -radius - lineW / 2, thumbHeight, thumbWidth);
    g.fillPath(thumbTick, AffineTransform::rotation(toAngle).translated(bounds.getCentreX(), bounds.getCentreY()));
}

void VarikeyLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
    float sliderPos,
    float minSliderPos,
    float maxSliderPos,
    const Slider::SliderStyle style, Slider& slider)
{
    if (slider.isBar())
    {
        g.setColour(slider.findColour(Slider::trackColourId));
        g.fillRect(slider.isHorizontal() ? Rectangle<float>(static_cast<float> (x), (float)y + 0.5f, sliderPos - (float)x, (float)height - 1.0f)
            : Rectangle<float>((float)x + 0.5f, sliderPos, (float)width - 1.0f, (float)y + ((float)height - sliderPos)));
    }
    else
    {
        auto isTwoVal = (style == Slider::SliderStyle::TwoValueVertical || style == Slider::SliderStyle::TwoValueHorizontal);
        auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

        auto trackWidth = jmin(6.0f, slider.isHorizontal() ? (float)height * 0.25f : (float)width * 0.25f);

        Point<float> startPoint(slider.isHorizontal() ? (float)x : (float)x + (float)width * 0.5f,
            slider.isHorizontal() ? (float)y + (float)height * 0.5f : (float)(height + y));

        Point<float> endPoint(slider.isHorizontal() ? (float)(width + x) : startPoint.x,
            slider.isHorizontal() ? startPoint.y : (float)y);

        Path backgroundTrack;
        backgroundTrack.startNewSubPath(startPoint);
        backgroundTrack.lineTo(endPoint);
        g.setColour(slider.findColour(Slider::backgroundColourId));
        g.strokePath(backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

        Path valueTrack;
        Point<float> minPoint, maxPoint, thumbPoint;

        if (isTwoVal || isThreeVal)
        {
            minPoint = { slider.isHorizontal() ? minSliderPos : (float)width * 0.5f,
                         slider.isHorizontal() ? (float)height * 0.5f : minSliderPos };

            if (isThreeVal)
                thumbPoint = { slider.isHorizontal() ? sliderPos : (float)width * 0.5f,
                               slider.isHorizontal() ? (float)height * 0.5f : sliderPos };

            maxPoint = { slider.isHorizontal() ? maxSliderPos : (float)width * 0.5f,
                         slider.isHorizontal() ? (float)height * 0.5f : maxSliderPos };
        }
        else
        {
            auto kx = slider.isHorizontal() ? sliderPos : ((float)x + (float)width * 0.5f);
            auto ky = slider.isHorizontal() ? ((float)y + (float)height * 0.5f) : sliderPos;

            minPoint = startPoint;
            maxPoint = { kx, ky };
        }

        auto thumbWidth = getSliderThumbRadius(slider) / 1.9;
        auto thumbHeight = getSliderThumbRadius(slider) * 1.5;

        valueTrack.startNewSubPath(minPoint);
        valueTrack.lineTo(isThreeVal ? thumbPoint : maxPoint);
        g.setColour(slider.findColour(Slider::trackColourId));
        g.strokePath(valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

        if (!isTwoVal)
        {
            g.setColour(slider.findColour(Slider::thumbColourId));
            if(slider.isHorizontal())
                g.fillRect(Rectangle<float>(static_cast<float> (thumbWidth), static_cast<float> (thumbHeight)).withCentre(isThreeVal ? thumbPoint : maxPoint));
            if(slider.isVertical())
                g.fillRect(Rectangle<float>(static_cast<float> (thumbHeight), static_cast<float> (thumbWidth)).withCentre(isThreeVal ? thumbPoint : maxPoint));

        }

        if (isTwoVal || isThreeVal)
        {
            auto sr = jmin(trackWidth, (slider.isHorizontal() ? (float)height : (float)width) * 0.4f);
            auto pointerColour = slider.findColour(Slider::thumbColourId);

            if (slider.isHorizontal())
            {
                drawPointer(g, minSliderPos - sr,
                    jmax(0.0f, (float)y + (float)height * 0.5f - trackWidth * 2.0f),
                    trackWidth * 2.0f, pointerColour, 2);

                drawPointer(g, maxSliderPos - trackWidth,
                    jmin((float)(y + height) - trackWidth * 2.0f, (float)y + (float)height * 0.5f),
                    trackWidth * 2.0f, pointerColour, 4);
            }
            else
            {
                drawPointer(g, jmax(0.0f, (float)x + (float)width * 0.5f - trackWidth * 2.0f),
                    minSliderPos - trackWidth,
                    trackWidth * 2.0f, pointerColour, 1);

                drawPointer(g, jmin((float)(x + width) - trackWidth * 2.0f, (float)x + (float)width * 0.5f), maxSliderPos - sr,
                    trackWidth * 2.0f, pointerColour, 3);
            }
        }
    }
}