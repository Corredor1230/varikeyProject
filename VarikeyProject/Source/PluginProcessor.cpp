/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VarikeyProjectAudioProcessor::VarikeyProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
: vts(*this, nullptr, "Params", buildParams())
{
    int numVoices = 8;
    synth.addSound(new SynthSound());
    for (int i = 0; i < numVoices; i++)
    {
        auto ptr = new SynthVoice(noteTuning, vts);
        /*ptr->setNoteTunner(&noteTuning);*/
        synth.addVoice(ptr);
    }
    juce::Decibels::decibelsToGain(10);
}

//PARAMETER RANGES AND ADDITION TO VTS
juce::AudioProcessorValueTreeState::ParameterLayout VarikeyProjectAudioProcessor::buildParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    std::initializer_list<const char*> synthList
    {
        "none",
        "gen1Noise", "gen2Noise",
        "noise1Tone", "noise2Tone",
        "mix",
        "fm1Ratio", "fm1Depth",
        "fm2Ratio", "fm2Depth",
        "lopCutoff", "lopQ",
        "hipCutoff", "hipQ",
        "detune", "vibFreq", "vibDepth",
        "volume"
    };

//SYNTHS
    //GENERATOR
        //Left
        createIntParameter(params, "leftGenShape", "Wave Shape 1", 0, 3, 0);
        createFloatParameter(params, "leftGenNoiseLevel", "Noise Level 1", 0.f, 1.f, 0.01f, 0.f);
        createIntParameter(params, "leftGenNoiseShape", "Noise Shape 1", 0, 1, 1);

        //Right
        createIntParameter(params, "rightGenShape", "Wave Shape 2", 0, 3, 0);
        createFloatParameter(params, "rightGenNoiseLevel", "Noise Level 2", 0.f, 1.f, 0.01f, 0.f);
        createIntParameter(params, "rightGenNoiseShape", "Noise Shape 2", 0, 1, 1);

    //ADDITIVE
        //Left
        std::string additiveLeft = "additiveLeft";
        createFloatParameter(params, "additiveLeft0", "0 Left", 0.f, 8.f, 1.f, 8.f);
        for (int i = 1; i < 9; i++)
        {
            createFloatParameter(params, additiveLeft + std::to_string(i), std::to_string(i) + "Left", 0.f, 8.f, 1.f, 0.f);
        }

        //Right
        std::string additiveRight = "additiveRight";
        createFloatParameter(params, "additiveRight0", "0 Right", 0.f, 8.f, 1.f, 8.f);
        for (int i = 1; i < 9; i++)
        {
            createFloatParameter(params, additiveRight + std::to_string(i), std::to_string(i) + "Right", 0.f, 8.f, 1.f, 0.f);
        }

    //KARPLUS
        //Left
        createFloatParameter(params, "leftKarpAtt", "Karplus Attack 1", 0.f, 1.f, 0.0001, 0.01, 0.4);
        createFloatParameter(params, "leftKarpRel", "Karplus Release 1", 0.f, 1.f, 0.0001, 1.f, 0.4);
        createFloatParameter(params, "leftKarpFb", "Karplus Feedback 1", 0.f, 1.f, 0.001, 0.95f);
        createIntParameter(params, "leftKarpNoise", "Karplus Noise 1", 0, 1, 1);

        //Right
        createFloatParameter(params, "rightKarpAtt", "Karplus Attack 2", 0.f, 1.f, 0.0001, 0.01, 0.4);
        createFloatParameter(params, "rightKarpRel", "Karplus Release 2", 0.f, 1.f, 0.0001, 1.f, 0.4);
        createFloatParameter(params, "rightKarpFb", "Karplus Feedback 2", 0.f, 1.f, 0.001, 0.95f);
        createIntParameter(params, "rightKarpNoise", "Karplus Noise 2", 0, 1, 1);

    //NOISE
        //Left
        createFloatParameter(params, "leftNoiseTone", "Noise Tone 1", 0.0f, 1.0f, 0.001f, 1.0f);
        //Right
        createFloatParameter(params, "rightNoiseTone", "Noise Tone 2", 0.0f, 1.0f, 0.001f, 1.0f);

    //FM MOD
        //Left
        createFloatParameter(params, "leftFmRatio", "FM Ratio 1", 0.0f, 8.0f, 0.1, 1.0f);
        createFloatParameter(params, "leftFmDepth", "FM Depth 1", 0.0f, 24.0f, 0.1f, 0.0f);

        //Right
        createFloatParameter(params, "rightFmRatio", "FM Ratio 2", 0.0f, 8.0f, 0.1, 1.0f);
        createFloatParameter(params, "rightFmDepth", "FM Depth 2", 0.0f, 24.0f, 0.1f, 0.0f);

    //CHOICE
        params.push_back(std::make_unique<juce::AudioParameterChoice>("leftSynthChoice", "Left Synth", synthList, 1));
        params.push_back(std::make_unique<juce::AudioParameterChoice>("rightSynthChoice", "Left Synth", synthList, 1));
        createFloatParameter(params, "synthMix", "Synth Mix", -1.0f, 1.0f, 0.01f, 0.0f);

//PROCESSES
    //FILTER
        //LOP
        createFloatParameter(params, "lopCutoff", "Cutoff LOP", 20.0f, 20000.0f, 1.0f, 1000.0f, 0.3);
        params.push_back(std::make_unique<juce::AudioParameterBool>("lopOnOff", "On/Off", false));
        createFloatParameter(params, "lopQ", "Q LOP", 1.0f, 10.0f, 0.01f, 1.0f);

        //HIP
        createFloatParameter(params, "hipCutoff", "Cutoff HIP", 20.0f, 20000.0f, 1.0f, 1000.0f, 0.3);
        params.push_back(std::make_unique<juce::AudioParameterBool>("hipOnOff", "On/Off", false));
        createFloatParameter(params, "hipQ", "Q HIP", 1.0f, 10.0f, 0.01f, 1.0f);

    //ADSR
        //Amp
        createFloatParameter(params, "ampAdsrAtt", "Attack 1", 0.01, 5.0f, 0.001, 0.03, 0.3);
        createFloatParameter(params, "ampAdsrDec", "Decay 1", 0.01, 5.0f, 0.001, 0.03, 0.3);
        createFloatParameter(params, "ampAdsrSus", "Sustain 1", 0.0, 1.0f, 0.001f, 0.5f);
        createFloatParameter(params, "ampAdsrRel", "Release 1", 0.01, 5.0f, 0.001, 0.03, 0.3);

        //Mod
        createFloatParameter(params, "modAdsrAtt", "Attack 2", 0.01, 5.0f, 0.001, 0.03, 0.3);
        createFloatParameter(params, "modAdsrDec", "Decay 2", 0.01, 5.0f, 0.001, 0.03, 0.3);
        createFloatParameter(params, "modAdsrSus", "Sustain 2", 0.0, 1.0f, 0.001f, 0.5f);
        createFloatParameter(params, "modAdsrRel", "Release 2", 0.01, 5.0f, 0.001, 0.03, 0.3);
        params.push_back(std::make_unique<juce::AudioParameterChoice>("modAdsrRoute", "Route Adsr", synthList, 1));

    //LFO
        //Lfo 1
        createFloatParameter(params, "lfo1Freq", "Frequency 1", 0.0f, 20.0f, 0.01f, 0.0f, 0.3);
        createFloatParameter(params, "lfo1Depth", "Depth 1", 0.0f, 1.0f, 0.001f, 0.0f);
        createFloatParameter(params, "lfo1Shape", "Shape 1", 1.0f, 100.0f, 0.1f, 1.0f);
        params.push_back(std::make_unique<juce::AudioParameterChoice>("lfo1Route", "Route Lfo 1", synthList, 1));

        //Lfo 2
        createFloatParameter(params, "lfo2Freq", "Frequency 2", 0.0f, 20.0f, 0.01f, 0.0f, 0.3);
        createFloatParameter(params, "lfo2Depth", "Depth 2", 0.0f, 1.0f, 0.001f, 0.0f);
        createFloatParameter(params, "lfo2Shape", "Shape 2", 1.0f, 100.0f, 0.1f, 1.0f);
        params.push_back(std::make_unique<juce::AudioParameterChoice>("lfo2Route", "Route Lfo 2", synthList, 1));

        //Lfo 3
        createFloatParameter(params, "lfo3Freq", "Frequency 3", 0.0f, 20.0f, 0.01f, 0.0f, 0.3);
        createFloatParameter(params, "lfo3Depth", "Depth 3", 0.0f, 1.0f, 0.001f, 0.0f);
        createFloatParameter(params, "lfo3Shape", "Shape 3", 1.0f, 100.0f, 0.1f, 1.0f);
        params.push_back(std::make_unique<juce::AudioParameterChoice>("lfo3Route", "Route Lfo 3", synthList, 1));

        //Lfo 4
        createFloatParameter(params, "lfo4Freq", "Frequency 4", 0.0f, 20.0f, 0.01f, 0.0f, 0.3);
        createFloatParameter(params, "lfo4Depth", "Depth 4", 0.0f, 1.0f, 0.001f, 0.0f);
        createFloatParameter(params, "lfo4Shape", "Shape 4", 1.0f, 100.0f, 0.1f, 1.0f);
        params.push_back(std::make_unique<juce::AudioParameterChoice>("lfo4Route", "Route Lfo 4", synthList, 1));

//GLOBAL
    //OTHER
        createFloatParameter(params, "detune", "Detune", -1.0f, 1.0f, 0.01f, 0.0f);
        createFloatParameter(params, "vibFreq", "Vibrato Frequency", 0.0f, 20.0f, 0.01f, 0.0f, 0.3);
        createFloatParameter(params, "vibDepth", "Vibrato Depth", 0.0f, 1.0f, 0.001f, 0.0f);
        createFloatParameter(params, "volume", "Volume", -60.0f, 0.0f, 0.1f, -20.f);

    //NOTE TUNING
        //Controls
        params.push_back(std::make_unique<juce::AudioParameterBool>("bassControlsTuning", "Bass Tuning", false));
        createIntParameter(params, "keyboardBreak", "Break", 1, 127, 48);

        //Sliders
        std::string tuning = "tuning";
        for (int i = 0; i < 12; i++)
        {
            createFloatParameter(params, tuning + std::to_string(i), std::to_string(i) + "Tuner", -1.0f, 1.0f, 0.01f, 0.0f);
        }
        createIntParameter(params, "scaleCenter", "Scale Center", 0, 11, 0);

    


    return { params.begin(), params.end() };
}

VarikeyProjectAudioProcessor::~VarikeyProjectAudioProcessor()
{
}

//==============================================================================
const juce::String VarikeyProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VarikeyProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VarikeyProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VarikeyProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VarikeyProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VarikeyProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VarikeyProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VarikeyProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String VarikeyProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void VarikeyProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void VarikeyProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }

    }
}

void VarikeyProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VarikeyProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VarikeyProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels(); // esto no se usa
    auto totalNumOutputChannels = getTotalNumOutputChannels(); // esto no se usa


    //for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    //{
    //    buffer.clear(i, 0, buffer.getNumSamples());
    //}


    buffer.clear();


    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {

            auto& attack = *vts.getRawParameterValue("Att");
            auto& decay = *vts.getRawParameterValue("Dec");
            auto& sustain = *vts.getRawParameterValue("Sus");
            auto& release = *vts.getRawParameterValue("Rel");
            auto& gain = *vts.getRawParameterValue("Gain"); // esta variable no se usa

            auto& cTuning = *vts.getRawParameterValue("c");
            auto& cesTuning = *vts.getRawParameterValue("ces");
            auto& dTuning = *vts.getRawParameterValue("d");
            auto& desTuning = *vts.getRawParameterValue("des");
            auto& eTuning = *vts.getRawParameterValue("e");
            auto& fTuning = *vts.getRawParameterValue("f");
            auto& fesTuning = *vts.getRawParameterValue("fes");
            auto& gTuning = *vts.getRawParameterValue("g");
            auto& gesTuning = *vts.getRawParameterValue("ges");
            auto& aTuning = *vts.getRawParameterValue("a");
            auto& aesTuning = *vts.getRawParameterValue("aes");
            auto& bTuning = *vts.getRawParameterValue("b");

            tuning[0] = cTuning.load();
            tuning[1] = cesTuning.load();
            tuning[2] = dTuning.load();
            tuning[3] = desTuning.load();
            tuning[4] = eTuning.load();
            tuning[5] = fTuning.load();
            tuning[6] = fesTuning.load();
            tuning[7] = gTuning.load();
            tuning[8] = gesTuning.load();
            tuning[9] = aTuning.load();
            tuning[10] = aesTuning.load();
            tuning[11] = bTuning.load();
            noteTuning.setTuning(tuning);


            //Karplus Parameters
            float kFeed = vts.getParameterAsValue("kFeed").getValue();
            integers[0] = vts.getParameterAsValue("kAtt").getValue();
            integers[1] = vts.getParameterAsValue("kRel").getValue();
            integers[2] = vts.getParameterAsValue("kSwitch").getValue();
            integers[3] = vts.getParameterAsValue("fmDepth").getValue();
            integers[4] = vts.getParameterAsValue("fmIndex").getValue();

            //Gen Parameters
            std::array<int, 1> genIntegers;
            genIntegers[0] = vts.getParameterAsValue("selector").getValue();
            std::array<float, 1> genFloats;
            genFloats[0] = vts.getParameterAsValue("gain").getValue();

            //Filter Parameters
            int cutoff = vts.getParameterAsValue("cutoff").getValue();
            float q = vts.getParameterAsValue("q").getValue();

            //Lfo Parameters
            lfoFreq = vts.getParameterAsValue("lfoFreq").getValue();
            lfoDepth = vts.getParameterAsValue("lfoDepth").getValue();
            lfoWave = vts.getParameterAsValue("lfoWave").getValue();

            voice->updateFilter(cutoff, q);
            voice->updateGeneric(genIntegers, genFloats);
            voice->updateKarplus(kFeed, integers);
            voice->updateAdsr(attack.load(), decay.load(), sustain.load(), release.load());
            voice->updateLfo1(lfoFreq, lfoWave, lfoDepth);
            voice->updateModAdsr(vts.getParameterAsValue("modAtt").getValue(),
                vts.getParameterAsValue("modDec").getValue(),
                vts.getParameterAsValue("modSus").getValue(),
                vts.getParameterAsValue("modRel").getValue());
        }

    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
}

//==============================================================================
bool VarikeyProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* VarikeyProjectAudioProcessor::createEditor()
{
    return new VarikeyProjectAudioProcessorEditor (*this);
}

//==============================================================================
void VarikeyProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void VarikeyProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void VarikeyProjectAudioProcessor::createFloatParameter(std::vector < std::unique_ptr<juce::RangedAudioParameter>>& params,
    const juce::String& paramID, const juce::String& paramName, float minValue, float maxValue, float interval,
    float initValue, float skewValue)
{
    params.push_back(std::make_unique<juce::AudioParameterFloat>(paramID, paramName, juce::NormalisableRange<float>(minValue, maxValue, interval, skewValue), initValue));
}

void VarikeyProjectAudioProcessor::createIntParameter(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& params,
    const juce::String& paramID, const juce::String& paramName, int minVal, int maxVal, int defaultVal)
{
    params.push_back(std::make_unique<juce::AudioParameterInt>(paramID, paramName, minVal, maxVal, defaultVal));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VarikeyProjectAudioProcessor();
}

