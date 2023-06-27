/*
  ==============================================================================

    TuningComponent.cpp
    Created: 8 Apr 2022 11:35:01am
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TuningComponent.h"

//==============================================================================
TuningComponent::TuningComponent(juce::AudioProcessorValueTreeState& vts) : vts(vts)
, attachment0(vts, "tuning0", slider0)
, attachment1(vts, "tuning1", slider1)
, attachment2(vts, "tuning2", slider2)
, attachment3(vts, "tuning3", slider3)
, attachment4(vts, "tuning4", slider4)
, attachment5(vts, "tuning5", slider5)
, attachment6(vts, "tuning6", slider6)
, attachment7(vts, "tuning7", slider7)
, attachment8(vts, "tuning8", slider8)
, attachment9(vts, "tuning9", slider9)
, attachment10(vts, "tuning10", slider10)
, attachment11(vts, "tuning11", slider11)
, transposeAttachment(vts, "scaleCenter", transposeSlider)
, breakAttachment(vts, "keyboardBreak", keybreakSlider)
, breakToggleAttachment(vts, "bassControlsTuning", keyBreakToggle)
, presetAttachment(vts, "tuningPreset", presetSelector)

{


    //transposeTextBoxWidth = getWidth() / 12;
    //transposeTextBoxHeight = getHeight() / 6;
    addAndMakeVisible(transposeSlider);
    addAndMakeVisible(centerLabel);

    centerLabel.setText("C", juce::dontSendNotification);
    centerLabel.setJustificationType(juce::Justification::centred);

    transposeSlider.setRange(0.0, 11.0, 1.0);
    transposeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    //transposeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,
    //    false, 25, 25);
    transposeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 25, 25);

    addAndMakeVisible(keyBreakToggle);
    keyBreakToggle.setName("Key Break Toggle");

    addAndMakeVisible(transposeLabel);
    transposeLabel.setText("Centered at: ", juce::dontSendNotification);
    transposeLabel.attachToComponent(&transposeSlider, true);

    addAndMakeVisible(titleLabel);
    titleLabel.setText("Note Tuning", juce::dontSendNotification);

    addAndMakeVisible(keyBreakLabel);
    keyBreakLabel.setText("Tuning control below: ", juce::dontSendNotification);

    addAndMakeVisible(presetSelector);
    addAndMakeVisible(presetLabel);
    presetSelector.addItemList(presetList, 1);
    presetSelector.setJustificationType(juce::Justification::centred);
    presetSelector.setTextWhenNothingSelected("12-TET");

    presetLabel.setText("Tuning Preset: ", juce::dontSendNotification);
    presetLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(keyBreakValue);
    addAndMakeVisible(keybreakSlider);

    addAndMakeVisible(valueOutline);
    keyBreakValue.setEditable(true);
    //keyBreakValue.setColour(juce::Label::ColourIds::outlineColourId, 
    //    slider0.findColour(juce::Slider::ColourIds::trackColourId));
    keyBreakValue.setText(keybreakSlider.getTextFromValue(keybreakSlider.getValue()), juce::dontSendNotification);
    keyBreakValue.setJustificationType(juce::Justification::centredLeft);

    setSliderParams(slider0, label0, "0", vertical);
    setSliderParams(slider1, label1, "1", vertical);
    setSliderParams(slider2, label2, "2", vertical);
    setSliderParams(slider3, label3, "3", vertical);
    setSliderParams(slider4, label4, "4", vertical);
    setSliderParams(slider5, label5, "5", vertical);
    setSliderParams(slider6, label6, "6", vertical);
    setSliderParams(slider7, label7, "7", vertical);
    setSliderParams(slider8, label8, "8", vertical);
    setSliderParams(slider9, label9, "9", vertical);
    setSliderParams(slider10, label10, "10", vertical);
    setSliderParams(slider11, label11, "11", vertical);

    auto& comboBoxIndex = *vts.getRawParameterValue("tuningPreset");

    presetSelector.setSelectedItemIndex(comboBoxIndex.load() + comboBoxOffset, juce::sendNotification);
    oldValue = getPresetIndex(presetSelector.getText());
}

TuningComponent::~TuningComponent()
{
}

void TuningComponent::paint (juce::Graphics& g)
{


    g.fillAll(juce::Colour());
    //juce::Rectangle<float> border;
    //border.setBounds(5, 5, getWidth() - 10, getHeight() - 10);
    //g.setColour(slider0.findColour(juce::ToggleButton::ColourIds::tickDisabledColourId));
    //juce::Line<float> line(juce::Point<float>(5, 0), juce::Point<float>(getRight() - 5, 0));
    //g.drawLine(line);
    //g.drawRect(border, 1.0f);

    juce::Colour toggleOff = getLookAndFeel().findColour(juce::ToggleButton::ColourIds::tickDisabledColourId);
    juce::Colour toggleOn = getLookAndFeel().findColour(juce::ToggleButton::ColourIds::tickColourId);

    switch (keyBreakToggle.getToggleState())
    {
    case 0:

        keyBreakLabel.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        keyBreakValue.setColour(juce::Label::ColourIds::textColourId, toggleOff);
        keyBreakToggle.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, toggleOff);
        break;
    case 1:
        keyBreakLabel.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        keyBreakValue.setColour(juce::Label::ColourIds::textColourId, toggleOn);
        keyBreakToggle.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, toggleOn);
        break;
    }

    breakKeyString = keyBreakValue.getText();
    breakKeyValue = breakKeyString.getIntValue();
    keybreakSlider.setValue(breakKeyValue, juce::sendNotification);

    switch ((int)transposeSlider.getValue())
    {
    case 0:
        centerLabel.setText("C", juce::dontSendNotification);
        break;
    case 1:
        centerLabel.setText("C#/Db", juce::dontSendNotification);
        break;
    case 2:
        centerLabel.setText("D", juce::dontSendNotification);
        break;
    case 3:
        centerLabel.setText("D#/Eb", juce::dontSendNotification);
        break;
    case 4:
        centerLabel.setText("E", juce::dontSendNotification);
        break;
    case 5:
        centerLabel.setText("F", juce::dontSendNotification);
        break;
    case 6:
        centerLabel.setText("F#/Gb", juce::dontSendNotification);
        break;
    case 7:
        centerLabel.setText("G", juce::dontSendNotification);
        break;
    case 8:
        centerLabel.setText("G#/Ab", juce::dontSendNotification);
        break;
    case 9:
        centerLabel.setText("A", juce::dontSendNotification);
        break;
    case 10:
        centerLabel.setText("A#/Bb", juce::dontSendNotification);
        break;
    case 11:
        centerLabel.setText("B", juce::dontSendNotification);
        break;
    default:
        jassertfalse;
        break;
    }

    setSliderLabels((int)transposeSlider.getValue());

    if (oldValue != getPresetIndex(presetSelector.getText()))
    {
        oldValue = getPresetIndex(presetSelector.getText());
        presets.setPreset(getPresetIndex(presetSelector.getText()));
        currentPreset = presets.getCurrentPreset();
        //presetSelector.onChange = [&]() {updateSlidersFromArray(currentPreset); };
        updateSlidersFromArray(currentPreset);
    }

    //presets.setPreset(getPresetIndex(presetSelector.getText()));
    //DBG(getPresetIndex(presetSelector.getText()));
    //currentPreset = presets.getCurrentPreset();
    //presetSelector.onChange = [=]() {updateSlidersFromArray(presets.getCurrentPreset()); };


}

void TuningComponent::resized()
{
    auto bounds = getBounds().reduced(5, 5);
    int height = bounds.getHeight();
    int width = bounds.getWidth();
    int padding = 10;
    int sliderLabel = height / 7;
    int title = height / 6;
    int sliderWidth = (width / 12) - padding;
    int sliderStartX = padding;
    int sliderStartY = title + sliderLabel;


    transposeTextBoxWidth = sliderWidth * 2;
    transposeTextBoxHeight = height / 6;
    int centerLabelWidth = 40;
    int labelStartX = (padding * 2) / 1.1;
    int topStartY = 3;
    int transposeHeight = height / 6;
    int transposeWidth = width - transposeTextBoxWidth - labelStartX - centerLabelWidth - padding - 1;
    int transposeStartX = sliderStartX + padding + transposeTextBoxWidth;
    int transposeStartY = 3 * (height / 4);

    int sliderHeight = height - title - sliderLabel - transposeHeight;

    slider0.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    slider1.setBounds(slider0.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider2.setBounds(slider1.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider3.setBounds(slider2.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider4.setBounds(slider3.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider5.setBounds(slider4.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider6.setBounds(slider5.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider7.setBounds(slider6.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider8.setBounds(slider7.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider9.setBounds(slider8.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider10.setBounds(slider9.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider11.setBounds(slider10.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    transposeSlider.setBounds(transposeStartX + centerLabelWidth, slider0.getBottom(), transposeWidth, transposeHeight);
    titleLabel.setBounds(labelStartX, topStartY, transposeTextBoxWidth, transposeTextBoxHeight);
    keyBreakToggle.setBounds(titleLabel.getRight() + sliderWidth, topStartY + 2, padding * 3, transposeTextBoxHeight);
    keyBreakLabel.setBounds(keyBreakToggle.getRight(), topStartY, sliderWidth * 3.5, transposeTextBoxHeight);
    keyBreakLabel.setJustificationType(juce::Justification::centredLeft);
    keyBreakValue.setBounds(keyBreakLabel.getRight(), topStartY, sliderWidth, transposeTextBoxHeight);
    presetLabel.setBounds(keyBreakValue.getRight() + padding, topStartY, sliderWidth * 2.5, transposeTextBoxHeight);
    presetSelector.setBounds(presetLabel.getRight() + padding, topStartY + padding / 2, sliderWidth * 3, transposeTextBoxHeight - padding);
    transposeLabel.setBounds(labelStartX, slider0.getBottom() - 2, transposeTextBoxWidth, transposeTextBoxHeight);
    transposeLabel.setJustificationType(juce::Justification::centredLeft);
    centerLabel.setBounds(transposeStartX, slider0.getBottom() - 2, centerLabelWidth, transposeTextBoxHeight);


}

void TuningComponent::setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setNormalisableRange(juce::NormalisableRange<double>(-1.0, 1.0, 0.01));
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(&slider, false);

    switch (style)
    {
    case vertical:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        break;
    case rotary:
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        break;
    case horizontal:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
        break;
    default:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
        break;
    }
}

void TuningComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}

void TuningComponent::setFont(juce::Font& font)
{
    customFont = font;
}

void TuningComponent::setSliderLabels(int centerValue)
{
    label0.setText(noteArray[getArrayValue(0, centerValue)], juce::dontSendNotification);
    label1.setText(noteArray[getArrayValue(1, centerValue)], juce::dontSendNotification);
    label2.setText(noteArray[getArrayValue(2, centerValue)], juce::dontSendNotification);
    label3.setText(noteArray[getArrayValue(3, centerValue)], juce::dontSendNotification);
    label4.setText(noteArray[getArrayValue(4, centerValue)], juce::dontSendNotification);
    label5.setText(noteArray[getArrayValue(5, centerValue)], juce::dontSendNotification);
    label6.setText(noteArray[getArrayValue(6, centerValue)], juce::dontSendNotification);
    label7.setText(noteArray[getArrayValue(7, centerValue)], juce::dontSendNotification);
    label8.setText(noteArray[getArrayValue(8, centerValue)], juce::dontSendNotification);
    label9.setText(noteArray[getArrayValue(9, centerValue)], juce::dontSendNotification);
    label10.setText(noteArray[getArrayValue(10, centerValue)], juce::dontSendNotification);
    label11.setText(noteArray[getArrayValue(11, centerValue)], juce::dontSendNotification);
}

void TuningComponent::updateSlidersFromArray(std::array<float, 12> newValues)
{
    slider0.setValue(newValues[0], juce::sendNotification);
    slider1.setValue(newValues[1], juce::sendNotification);
    slider2.setValue(newValues[2], juce::sendNotification);
    slider3.setValue(newValues[3], juce::sendNotification);
    slider4.setValue(newValues[4], juce::sendNotification);
    slider5.setValue(newValues[5], juce::sendNotification);
    slider6.setValue(newValues[6], juce::sendNotification);
    slider7.setValue(newValues[7], juce::sendNotification);
    slider8.setValue(newValues[8], juce::sendNotification);
    slider9.setValue(newValues[9], juce::sendNotification);
    slider10.setValue(newValues[10], juce::sendNotification);
    slider11.setValue(newValues[11], juce::sendNotification);
}

int TuningComponent::getPresetIndex(const juce::String& preset)
{
    if (preset == "12-TET") return 0;
    if (preset == "Just Intonation") return 1;
    if (preset == "Pythagorean") return 2;
    if (preset == "1/4 Meantone") return 3;
    if (preset == "Werckmeister III") return 4;
    if (preset == "Marimba 1") return 5;
    if (preset == "Marimba 2") return 6;
    if (preset == "Marimba 3") return 7;
    if (preset == "Slendro") return 8;
    return 0;
}

void TuningComponent::updateCenterSlider(const int controlNote)
{
    int ctrl = controlNote;
    transposeSlider.setValue(ctrl, juce::sendNotification);
}

void TuningComponent::setComboBoxOffset(int offset)
{
    comboBoxOffset = offset;
}