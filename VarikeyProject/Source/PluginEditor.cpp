/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VarikeyProjectAudioProcessorEditor::VarikeyProjectAudioProcessorEditor(VarikeyProjectAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
    , filters(audioProcessor.vts)
    , genLeft(audioProcessor.vts, "leftGenShape", "leftGenNoiseLevel", "leftGenNoiseShape")
    , genRight(audioProcessor.vts, "rightGenShape", "rightGenNoiseLevel", "rightGenNoiseShape")
    , leftOscAttachment(audioProcessor.vts, "leftSynthChoice", leftOscChoice)
    , rightOscAttachment(audioProcessor.vts, "rightSynthChoice", rightOscChoice)
    , mixAttachment(audioProcessor.vts, "synthMix", crossSlider)
    , volumeAttachment(audioProcessor.vts, "volume", volumeSlider)
    , additiveLeft(audioProcessor.vts, leftAdditiveIDs)
    , additiveRight(audioProcessor.vts, rightAdditiveIDs)
    , karpLeft(audioProcessor.vts, "leftKarpAtt", "leftKarpRel", "leftKarpFb", "leftKarpNoise")
    , karpRight(audioProcessor.vts, "rightKarpAtt", "rightKarpRel", "rightKarpFb", "rightKarpNoise")
    , noiseLeft(audioProcessor.vts, "leftNoiseTone")
    , noiseRight(audioProcessor.vts, "rightNoiseTone")
    , ampAdsr(audioProcessor.vts)
    , distLeft(audioProcessor.vts, "leftDistInput", "leftDistOutput", "leftDistOnOff")
    , distRight(audioProcessor.vts, "rightDistInput", "rightDistOutput", "rightDistOnOff")
    , lfo1(audioProcessor.vts, "lfo1Freq", "lfo2Freq", "lfo1Depth", 
        "lfo2Depth", "lfo1Shape", "lfo2Shape", "lfo1Route", "lfo2Route")
    , lfo2(audioProcessor.vts, "lfo3Freq", "lfo4Freq", "lfo3Depth", 
        "lfo4Depth", "lfo3Shape", "lfo4Shape", "lfo3Route", "lfo4Route")
    , modAdsr(audioProcessor.vts)
    , tuner(audioProcessor.vts)
    , pitchwheel(audioProcessor.vts)
{
    varikeyLookAndFeel.setColourPalette(VarikeyLookAndFeel::palette::vaporwave);
    setLookAndFeel(&varikeyLookAndFeel);
    addAndMakeVisible(tuner);

    varikeyLogo = Drawable::createFromImageData(BinaryData::Varikey_svg,
        BinaryData::Varikey_svgSize);

    addAndMakeVisible(additiveLeft);
    addAndMakeVisible(additiveRight);
    addAndMakeVisible(genLeft);
    addAndMakeVisible(genRight);
    addAndMakeVisible(karpLeft);
    addAndMakeVisible(karpRight);
    addAndMakeVisible(noiseLeft);
    addAndMakeVisible(noiseRight);
    addAndMakeVisible(lfo1);
    addAndMakeVisible(lfo2);
    addAndMakeVisible(pitchwheel);

    addAndMakeVisible(leftOscChoice);
    addAndMakeVisible(rightOscChoice);

    addAndMakeVisible(distLeft);
    addAndMakeVisible(distRight);

    addAndMakeVisible(crossSlider);
    addAndMakeVisible(crossLabel);

    addAndMakeVisible(filters);
    addAndMakeVisible(ampAdsr);
    addAndMakeVisible(modAdsr);

    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(volumeLabel);

    volumeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    volumeLabel.setText("Volume", juce::dontSendNotification);
    volumeLabel.setJustificationType(juce::Justification::centred);

    crossSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    crossSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    crossSlider.setRange(-1.0, 1.0, 0.01);
    crossLabel.setText("Mix", juce::sendNotification);
    crossLabel.setJustificationType(juce::Justification::centred);

    josefinSans.setFontSizeAndStyle(60.f, "plain", 1.f, 0.f);


    juce::String rightRegionTitle = "Osc 2: ";
    additiveRight.setRegionTitle(rightRegionTitle);
    genRight.setRegionTitle(rightRegionTitle);
    karpRight.setRegionTitle(rightRegionTitle);
    noiseRight.setRegionTitle(rightRegionTitle);

    juce::String lfo2Region1 = "3";
    juce::String lfo2Region2 = "4";
    lfo2.setRegionTitle(lfo2Region1, lfo2Region2);

    std::initializer_list<const char*> synthList{ "Generator", "Additive", "Karplus", "Noise" };
    leftOscChoice.addItemList(juce::StringArray(synthList), 1);
    leftOscChoice.setJustificationType(juce::Justification::centred);
    leftOscChoice.setTextWhenNothingSelected("Generator");
    //leftOscChoice.setSelectedId(1);
    rightOscChoice.addItemList(juce::StringArray(synthList), 1);
    rightOscChoice.setJustificationType(juce::Justification::centred);
    rightOscChoice.setTextWhenNothingSelected("Generator");
    //rightOscChoice.setSelectedId(1);

    tuner.setCustomLookAndFeel(&varikeyLookAndFeel);
    additiveLeft.setCustomLookAndFeel(&varikeyLookAndFeel);
    additiveRight.setCustomLookAndFeel(&varikeyLookAndFeel);
    genLeft.setCustomLookAndFeel(&varikeyLookAndFeel);
    genRight.setCustomLookAndFeel(&varikeyLookAndFeel);
    karpLeft.setCustomLookAndFeel(&varikeyLookAndFeel);
    karpRight.setCustomLookAndFeel(&varikeyLookAndFeel);
    noiseLeft.setCustomLookAndFeel(&varikeyLookAndFeel);
    noiseRight.setCustomLookAndFeel(&varikeyLookAndFeel);
    distLeft.setCustomLookAndFeel(&varikeyLookAndFeel);
    distRight.setCustomLookAndFeel(&varikeyLookAndFeel);
    filters.setCustomLookAndFeel(&varikeyLookAndFeel);
    ampAdsr.setCustomLookAndFeel(&varikeyLookAndFeel);
    modAdsr.setCustomLookAndFeel(&varikeyLookAndFeel);
    lfo1.setCustomLookAndFeel(&varikeyLookAndFeel);
    lfo2.setCustomLookAndFeel(&varikeyLookAndFeel);
    pitchwheel.setCustomLookAndFeel(&varikeyLookAndFeel);

    setSize(700, 700);
}

VarikeyProjectAudioProcessorEditor::~VarikeyProjectAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
    tuner.setCustomLookAndFeel(nullptr);
    additiveLeft.setCustomLookAndFeel(nullptr);
    additiveRight.setCustomLookAndFeel(nullptr);
    genLeft.setCustomLookAndFeel(nullptr);
    genRight.setCustomLookAndFeel(nullptr);
    karpLeft.setCustomLookAndFeel(nullptr);
    karpRight.setCustomLookAndFeel(nullptr);
    noiseLeft.setCustomLookAndFeel(nullptr);
    noiseRight.setCustomLookAndFeel(nullptr);
    distLeft.setCustomLookAndFeel(nullptr);
    distRight.setCustomLookAndFeel(nullptr);
    filters.setCustomLookAndFeel(nullptr);
    ampAdsr.setCustomLookAndFeel(nullptr);
    modAdsr.setCustomLookAndFeel(nullptr);
    lfo1.setCustomLookAndFeel(nullptr);
    pitchwheel.setCustomLookAndFeel(nullptr);
}

//==============================================================================
void VarikeyProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(varikeyLookAndFeel.getColourFromPalette(VarikeyLookAndFeel::paletteColours::gDark));

    auto& r1 = *vts.getRawParameterValue("lfo1Route");
    auto& r2 = *vts.getRawParameterValue("lfo2Route");
    auto& r3 = *vts.getRawParameterValue("lfo3Route");
    auto& r4 = *vts.getRawParameterValue("lfo4Route");
    auto& r5 = *vts.getRawParameterValue("modAdsrRoute");
    auto& centerToggle = *vts.getRawParameterValue("bassControlsTuning");
    if (centerToggle.load()) 
        tuner.updateCenterSlider(audioProcessor.getCurrentControlNote());

    lfo1.setUsedRoutes(1, 2, r1.load(), r2.load(), r3.load(), r4.load(), r5.load());
    lfo2.setUsedRoutes(3, 4, r1.load(), r2.load(), r3.load(), r4.load(), r5.load());
    modAdsr.setUsedRoutes(r1.load(), r2.load(), r3.load(), r4.load());

    getBounds().removeFromLeft(5);
    getBounds().removeFromRight(5);
    getBounds().removeFromTop(5);
    getBounds().removeFromBottom(5);




    switch (getComboBoxIndex(leftOscChoice.getText()))
    {
    case 0:
        genLeft.setVisible(true);
        additiveLeft.setVisible(false);
        karpLeft.setVisible(false);
        noiseLeft.setVisible(false);
        break;
    case 1:
        genLeft.setVisible(false);
        additiveLeft.setVisible(true);
        karpLeft.setVisible(false);
        noiseLeft.setVisible(false);
        break;
    case 2:
        genLeft.setVisible(false);
        additiveLeft.setVisible(false);
        karpLeft.setVisible(true);
        noiseLeft.setVisible(false);
        break;
    case 3:
        genLeft.setVisible(false);
        additiveLeft.setVisible(false);
        karpLeft.setVisible(false);
        noiseLeft.setVisible(true);
        break;
    default:
        genLeft.setVisible(true);
        additiveLeft.setVisible(false);
        karpLeft.setVisible(false);
        noiseLeft.setVisible(false);
        break;
    }

    switch (getComboBoxIndex(rightOscChoice.getText()))
    {
    case 0:
        genRight.setVisible(true);
        additiveRight.setVisible(false);
        karpRight.setVisible(false);
        noiseRight.setVisible(false);
        break;
    case 1:
        genRight.setVisible(false);
        additiveRight.setVisible(true);
        karpRight.setVisible(false);
        noiseRight.setVisible(false);
        break;
    case 2:
        genRight.setVisible(false);
        additiveRight.setVisible(false);
        karpRight.setVisible(true);
        noiseRight.setVisible(false);
        break;
    case 3:
        genRight.setVisible(false);
        additiveRight.setVisible(false);
        karpRight.setVisible(false);
        noiseRight.setVisible(true);
        break;
    default:
        genRight.setVisible(true);
        additiveRight.setVisible(false);
        karpRight.setVisible(false);
        noiseRight.setVisible(false);
        break;
    }



    g.setColour(varikeyLookAndFeel.getColourFromPalette(VarikeyLookAndFeel::paletteColours::contrast));
    g.fillRect(firstRowStartX + 5, secondRowStartY, width - 10, 1);
    g.fillRect(firstRowStartX + 5, thirdRowStartY, width - 10, 1);
    g.fillRect(modAdsr.getRight() + (width - modAdsr.getRight()) / 2 - 4, secondRowStartY + 6, 1, (secondRowHeight - pitchwheelHeight) - 8);
    g.fillRect(width / 2, secondRowStartY + 6, 1, secondRowHeight - 12);

    //ADSR
    g.fillRect(filters.getRight(), secondRowStartY + 6, 1, secondRowHeight - 12);
    g.fillRect(firstRowStartX + 5, secondRowStartY + secondRowHeight / 2, filterWidth - 10, 1);
    g.fillRect(filters.getRight() + 5, secondRowStartY + secondRowHeight / 2, adsrWidth - 10, 1);

    //Volume
    g.fillRect(volumeStartX - 5, thirdRowStartY + 5, 1, thirdRowHeight - 10);
    g.fillRect(firstRowStartX + 5, firstRowHeight - 3, width - 10, 1);

    //First row lines
    //g.fillRect(width / 2, firstRowHeight - oscChoiceHeight - padding - 2, 1, oscChoiceHeight + padding);
    //g.fillRect(firstColumnWidth + 1, firstRowStartY + 5, 1, firstRowHeight - oscChoiceHeight * 1.7);
    //g.fillRect(firstColumnWidth + secondColumnWidth + 1, firstRowStartY + 5, 1, firstRowHeight - oscChoiceHeight * 1.7);
    //g.fillRect(firstColumnWidth + 1, firstRowHeight - oscChoiceHeight * 1.5, secondColumnWidth + 1, 1);
    g.fillRect(firstColumnWidth + 1, firstRowHeight + 5, 1, fmRowHeight - 10);
    g.fillRect(firstColumnWidth + secondColumnWidth + 1, firstRowHeight + 5, 1, fmRowHeight - 10);

    //LFO
    g.fillRect(modAdsr.getRight() + 5, secondRowStartY + lfoHeight + 2, lfo1.getWidth() / 2 - 15, 1);
    g.fillRect(modAdsr.getRight() + lfo1.getWidth() / 2 + 4, secondRowStartY + lfoHeight + 2, lfo1.getWidth() / 2 - 10, 1);
    g.fillRect(modAdsr.getRight() + 5, lfo2.getBottom() + 3, width - modAdsr.getRight() - 10, 1);
    juce::Rectangle<float> logoRect;
    logoRect.setBounds(genLeft.getRight() + padding * 8.6, firstRowStartY + padding * 1.5, secondColumnWidth / 4, firstRowHeight / 1.6);
    varikeyLogo->replaceColour(juce::Colours::black, varikeyLookAndFeel.getColourFromPalette(VarikeyLookAndFeel::paletteColours::highlight));
    varikeyLogo->drawWithin(g, logoRect, juce::RectanglePlacement::Flags::fillDestination, 1.0);
}

void VarikeyProjectAudioProcessorEditor::resized()
{
    height = getHeight();
    width = getWidth();

    padding = 10;
    firstRowStartX = 0;
    firstRowStartY = 0;
    firstRowHeight = 2 * (height / 9);
    secondRowHeight = height / 2.75;
    firstColumnWidth = width / 3;
    filterWidth = firstColumnWidth * 0.8;
    adsrWidth = width / 2 - filterWidth;
    secondColumnWidth = width / 3;

    fmRowHeight = (height / 9);
    lfoHeight = (3 * secondRowHeight) / 8;
    pitchwheelHeight = secondRowHeight - lfoHeight * 2;
    labelHeight = 18;
    labelWidth = 50;
    labelStartX = firstColumnWidth + (secondColumnWidth / 2) - (labelWidth / 2);
    crossHeight = fmRowHeight - labelHeight;

    secondRowStartX = 0;
    secondRowStartY = height / 3;

    thirdRowStartX = 0;
    thirdRowStartY = firstRowHeight + fmRowHeight + secondRowHeight;
    thirdRowHeight = height - firstRowHeight - fmRowHeight - secondRowHeight;
    volumeWidth = width / 12 + padding * 2;
    tunerWidth = 2 * firstColumnWidth + secondColumnWidth - volumeWidth;

    volumeStartX = tunerWidth - padding;
    topStartY = 8 + padding / 2.5;
    volumeHeight = thirdRowHeight - labelHeight - 1.7 * padding - topStartY;


    oscChoiceWidth = (secondColumnWidth / 2) - padding;
    oscChoiceHeight = (firstRowHeight / 4) - 1.5 * padding;



    leftOscChoice.setBounds(firstColumnWidth + (padding / 2) - padding + 6.3, firstRowHeight - oscChoiceHeight - (padding / 1.5),
        oscChoiceWidth, oscChoiceHeight);
    rightOscChoice.setBounds(width / 2 + padding * 1.33, firstRowHeight - oscChoiceHeight - (padding / 1.5),
        oscChoiceWidth, oscChoiceHeight);

    genLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
    additiveLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
    karpLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
    noiseLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);

    genRight.setBounds(firstColumnWidth + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
    additiveRight.setBounds(firstColumnWidth + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
    karpRight.setBounds(firstColumnWidth + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
    noiseRight.setBounds(firstColumnWidth + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);

    distLeft.setBounds(firstRowStartX, firstRowHeight - padding / 2, firstColumnWidth, fmRowHeight + padding);
    distRight.setBounds(firstColumnWidth + secondColumnWidth, firstRowHeight - padding / 2, firstColumnWidth, fmRowHeight + padding);
    crossLabel.setBounds(labelStartX, firstRowHeight, labelWidth, labelHeight);
    crossSlider.setBounds(firstColumnWidth, crossLabel.getBottom(), secondColumnWidth, crossHeight);

    filters.setBounds(firstRowStartX, secondRowStartY, filterWidth, secondRowHeight);
    ampAdsr.setBounds(filters.getRight(), secondRowStartY, adsrWidth, secondRowHeight / 2);
    modAdsr.setBounds(filters.getRight(), ampAdsr.getBottom(), adsrWidth, secondRowHeight / 2);
    lfo1.setBounds(modAdsr.getRight(), secondRowStartY, width - modAdsr.getRight(), lfoHeight);
    lfo2.setBounds(modAdsr.getRight(), lfo1.getBottom(), width - modAdsr.getRight(), lfoHeight);
    pitchwheel.setBounds(modAdsr.getRight(), lfo2.getBottom(), width - modAdsr.getRight(), pitchwheelHeight);

    tuner.setBounds(firstRowStartX, thirdRowStartY, tunerWidth, thirdRowHeight);
    volumeLabel.setBounds(volumeStartX, thirdRowStartY + topStartY, volumeWidth, labelHeight);
    volumeSlider.setBounds(volumeStartX, volumeLabel.getBottom(), volumeWidth, volumeHeight);
}

int VarikeyProjectAudioProcessorEditor::getComboBoxIndex(juce::String& string)
{
        if (string == "Generator")
            return 0;
        else if (string == "Additive")
            return 1;
        else if (string == "Karplus")
            return 2;
        else if (string == "Noise")
            return 3;
        else
            return 0;
}