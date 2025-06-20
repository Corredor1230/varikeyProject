/*
  ==============================================================================

    LfoComponent.cpp
    Created: 8 Apr 2022 11:36:54am
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LfoComponent.h"

//==============================================================================

LfoLookAndFeel::LfoLookAndFeel()
{
}

LfoLookAndFeel::~LfoLookAndFeel()
{
}

void LfoLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
    auto fill = slider.findColour(Slider::rotarySliderFillColourId);

    auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(3);

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
    thumbTick.addRectangle(-thumbHeight / 2, -radius - lineW / 2, thumbHeight, thumbWidth);
    g.fillPath(thumbTick, AffineTransform::rotation(toAngle).translated(bounds.getCentreX(), bounds.getCentreY()));
}

LfoComponent::LfoComponent(juce::AudioProcessorValueTreeState& vts, juce::String freq1ID,
    juce::String freq2ID, juce::String depth1ID, juce::String depth2ID,
    juce::String shape1ID, juce::String shape2ID, juce::String route1ID, juce::String route2ID) : vts(vts)
    , freq1Attachment(vts, freq1ID, freq1Slider)
    , freq2Attachment(vts, freq2ID, freq2Slider)
    , depth1Attachment(vts, depth1ID, depth1Slider)
    , depth2Attachment(vts, depth2ID, depth2Slider)
    , shape1Attachment(vts, shape1ID, shape1Slider)
    , shape2Attachment(vts, shape2ID, shape2Slider)
    , route1Attachment(vts, route1ID, routeBox)
    , route2Attachment(vts, route2ID, routeBox2)
{
    setSliderParams(freq1Slider, freq1Label, "Freq", rotary);
    setSliderParams(depth1Slider, depth1Label, "Depth", rotary);
    setSliderParams(shape1Slider, shape1Label, "Shape", vertical);
    setSliderParams(freq2Slider, freq2Label, "Freq", rotary);
    setSliderParams(depth2Slider, depth2Label, "Depth", rotary);
    setSliderParams(shape2Slider, shape2Label, "Shape", vertical);

    freq1Slider.setRange(0.0, 20.0, 0.01);
    freq2Slider.setRange(0.0, 20.0, 0.01);
    depth1Slider.setRange(0.0, 1.0, 0.001);
    depth2Slider.setRange(0.0, 1.0, 0.001);
    shape1Slider.setRange(0.0, 100.0, 0.1);
    shape2Slider.setRange(0.0, 100.0, 0.1);

    addAndMakeVisible(lfo1Label);
    addAndMakeVisible(lfo2Label);
    addAndMakeVisible(routeBox);
    addAndMakeVisible(routeLabel);
    addAndMakeVisible(routeBox2);
    addAndMakeVisible(routeLabel2);

    routeLabel.setText("Route", juce::dontSendNotification);
    routeLabel2.setText("Route", juce::dontSendNotification);
    routeLabel.setInterceptsMouseClicks(false, false);
    routeLabel2.setInterceptsMouseClicks(false, false);
    routeBox.setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour());
    routeBox2.setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour());

    std::initializer_list<const char*> synthList
    {
        "none",
        "gen1Noise", "gen2Noise",
        "noise1Tone", "noise2Tone",
        "mix",
        "distInLeft", "distOutLeft",
        "distOutLeft", "distOutRight",
        "lopCutoff", "lopQ",
        "hipCutoff", "hipQ",
        "detune", "vibFreq", "vibDepth", 
        "volume"
    };

    auto& routeBoxIndex = *vts.getRawParameterValue(route1ID);
    auto& routeBox2Index = *vts.getRawParameterValue(route2ID);

    routeBox.addItemList(juce::StringArray(synthList), comboBoxOffset);
    routeBox2.addItemList(juce::StringArray(synthList), comboBoxOffset);

    routeBox.setSelectedId(routeBoxIndex.load() + comboBoxOffset, juce::NotificationType::sendNotification);
    routeBox2.setSelectedId(routeBox2Index.load() + comboBoxOffset, juce::NotificationType::sendNotification);

}

LfoComponent::~LfoComponent()
{
    setLookAndFeel(nullptr);
}

void LfoComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour());
    //juce::Rectangle<float> border;
    //border.setBounds(5, 5, getWidth() - 10, getHeight() - 10);
    //g.setColour(getLookAndFeel().findColour(juce::ToggleButton::ColourIds::tickDisabledColourId));
    //g.drawRect(border, 1.0f);



    auto bounds = getBounds().reduced(5, 5);
    int height = bounds.getHeight();
    int width = bounds.getWidth();
    g.setColour(getLookAndFeel().findColour(juce::ToggleButton::ColourIds::tickDisabledColourId));
    //g.drawLine(width / 2 + 2, 5, width / 2 + 2, height, 1.0);

    int padding = 10;
    int sliderLabel = height / 6;
    int sliderLabelWidth = 50;
    int titleHeight = height / 5;

    int rotaryWidth = (width / 6) - padding;
    int blockWidth = width / 6;
    int rotaryHeight = height - titleHeight * 2;
    int rotaryDiameter = std::min(rotaryWidth, rotaryHeight) - padding;

    int horizontalHeight = 25;
    int sliderWidth = (width / 6);
    int sliderHeight = height - titleHeight * 1.5;
    int sliderStartX = padding;
    int labelStartX = (padding * 2) / 1.1;
    int labelStartY = titleHeight + sliderLabel + padding;
    int topStartY = 3;

    lfo1Label.setText(lfoString + region1Index, juce::dontSendNotification);
    lfo1Label.setJustificationType(juce::Justification::centredLeft);
    lfo2Label.setText(lfoString + region2Index, juce::dontSendNotification);
    lfo2Label.setJustificationType(juce::Justification::centredLeft);

    lfo1Label.setBounds(sliderStartX, padding / 1.5, rotaryWidth, titleHeight);

    freq1Label.setBounds(sliderStartX, lfo1Label.getBottom(), rotaryWidth, titleHeight);
    freq1Label.setJustificationType(juce::Justification::centred);
    freq1Slider.setBounds(sliderStartX, freq1Label.getBottom(), rotaryWidth, rotaryHeight);
    depth1Label.setBounds(freq1Label.getRight() + padding, lfo1Label.getBottom(), rotaryWidth, titleHeight);
    depth1Slider.setBounds(freq1Slider.getRight() + padding, freq1Label.getBottom(), rotaryWidth, rotaryHeight);
    shape1Label.setBounds(depth1Label.getRight() + padding, lfo1Label.getBottom(), rotaryWidth, titleHeight);
    shape1Slider.setBounds(depth1Slider.getRight() + padding, freq1Label.getBottom() - titleHeight / 2, rotaryWidth, sliderHeight);

    routeLabel.setJustificationType(juce::Justification::centred);
    routeLabel.setBounds(freq1Label.getRight() + padding, padding / 1.5, rotaryWidth, titleHeight);
    routeBox.setBounds(depth1Label.getRight() + padding, padding, width / 8, titleHeight - padding / 2);
    lfo2Label.setBounds(shape1Label.getRight() + padding, padding / 1.5, rotaryWidth, titleHeight);

    freq2Label.setBounds(shape1Label.getRight() + padding, lfo1Label.getBottom(), rotaryWidth, titleHeight);
    freq2Label.setJustificationType(juce::Justification::centred);
    freq2Slider.setBounds(shape1Slider.getRight() + padding, freq2Label.getBottom(), rotaryWidth, rotaryHeight);
    depth2Label.setBounds(freq2Label.getRight() + padding, lfo1Label.getBottom(), rotaryWidth, titleHeight);
    depth2Slider.setBounds(freq2Slider.getRight() + padding, freq2Label.getBottom(), rotaryWidth, rotaryHeight);
    shape2Label.setBounds(depth2Label.getRight() + padding, lfo1Label.getBottom(), rotaryWidth, titleHeight);
    shape2Slider.setBounds(depth2Slider.getRight() + padding, freq2Label.getBottom() - titleHeight / 2, rotaryWidth, sliderHeight);

    routeLabel2.setJustificationType(juce::Justification::centred);
    routeLabel2.setBounds(freq2Label.getRight() + padding, padding / 1.5, rotaryWidth, titleHeight);
    routeBox2.setBounds(depth2Label.getRight() + padding, padding, width / 8, titleHeight - padding / 2);

    setDisabledRoutes(lfo1N, routeBox);
    setDisabledRoutes(lfo2N, routeBox2);

}

void LfoComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void LfoComponent::setSliderParams(juce::Slider& slider, juce::Label& label, juce::String name, int style)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    //label.attachToComponent(&slider, false);

    switch (style)
    {
    case vertical:
        //label.attachToComponent(&slider, false);
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        break;
    case rotary:
        //label.attachToComponent(&slider, false);
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        break;
    case horizontal:
        slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 25);
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
        break;
    default:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
        break;
    }
}

void LfoComponent::setCustomLookAndFeel(VarikeyLookAndFeel* customLookAndFeel)
{
    if (customLookAndFeel != nullptr)
    {
        lfoLookAndFeel.setColourPalette(customLookAndFeel->getCurrentPalette());
    }
    setLookAndFeel(&lfoLookAndFeel);
}

void LfoComponent::setRegionTitle(juce::String& region1, juce::String& region2)
{
    region1Index = region1;
    region2Index = region2;
}

void LfoComponent::setUsedRoutes(int lfo1Num, int lfo2Num, int lfo1Route, int lfo2Route, int lfo3Route, int lfo4Route, int modAdsrRoute)
{
    lfo1N = lfo1Num;
    lfo2N = lfo2Num;
    lfo1R = lfo1Route + 1;
    lfo2R = lfo2Route + 1;
    lfo3R = lfo3Route + 1;
    lfo4R = lfo4Route + 1;
    modAR = modAdsrRoute + 1;
    
}

void LfoComponent::setDisabledRoutes(int lfoNum, juce::ComboBox& box)
{
    switch (lfoNum)
    {
    case 0:
        jassertfalse;
        break;
    case 1:
        for (int i = 0; i <= box.getNumItems(); i++)
        {
            box.setItemEnabled(i, true);
        }
        (lfo2R == 0) ? box.setItemEnabled(lfo2R, true) : box.setItemEnabled(lfo2R, false);
        (lfo3R == 0) ? box.setItemEnabled(lfo3R, true) : box.setItemEnabled(lfo3R, false);
        (lfo4R == 0) ? box.setItemEnabled(lfo4R, true) : box.setItemEnabled(lfo4R, false);
        (modAR == 0) ? box.setItemEnabled(modAR, true) : box.setItemEnabled(modAR, false);
        break;
    case 2:
        for (int i = 0; i <= box.getNumItems(); i++)
        {
            box.setItemEnabled(i, true);
        }
        (lfo1R == 0) ? box.setItemEnabled(lfo1R, true) : box.setItemEnabled(lfo1R, false);
        (lfo3R == 0) ? box.setItemEnabled(lfo3R, true) : box.setItemEnabled(lfo3R, false);
        (lfo4R == 0) ? box.setItemEnabled(lfo4R, true) : box.setItemEnabled(lfo4R, false);
        (modAR == 0) ? box.setItemEnabled(modAR, true) : box.setItemEnabled(modAR, false);
        break;
    case 3:
        for (int i = 0; i <= box.getNumItems(); i++)
        {
            box.setItemEnabled(i, true);
        }
        (lfo1R == 0) ? box.setItemEnabled(lfo1R, true) : box.setItemEnabled(lfo1R, false);
        (lfo2R == 0) ? box.setItemEnabled(lfo2R, true) : box.setItemEnabled(lfo2R, false);
        (lfo4R == 0) ? box.setItemEnabled(lfo4R, true) : box.setItemEnabled(lfo4R, false);
        (modAR == 0) ? box.setItemEnabled(modAR, true) : box.setItemEnabled(modAR, false);
        break;
    case 4:
        for (int i = 0; i <= box.getNumItems(); i++)
        {
            box.setItemEnabled(i, true);
        }
        (lfo1R == 0) ? box.setItemEnabled(lfo1R, true) : box.setItemEnabled(lfo1R, false);
        (lfo2R == 0) ? box.setItemEnabled(lfo2R, true) : box.setItemEnabled(lfo2R, false);
        (lfo3R == 0) ? box.setItemEnabled(lfo3R, true) : box.setItemEnabled(lfo3R, false);
        (modAR == 0) ? box.setItemEnabled(modAR, true) : box.setItemEnabled(modAR, false);
        break;
    }
}

void LfoComponent::setComboBoxOffset(int offset)
{
    comboBoxOffset = offset;
}