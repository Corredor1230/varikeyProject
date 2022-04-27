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
, vts(*this, nullptr, "Params", buildParams())
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

    //ADSR Params
    params.push_back(std::make_unique<juce::AudioParameterFloat>("Att", "Attack",
        juce::NormalisableRange<float> {0.001f, 1.0f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("Dec", "Decay",
        juce::NormalisableRange<float> {0.01f, 1.0f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("Sus", "Sustain",
        juce::NormalisableRange<float> {0.0f, 1.0f, }, 0.6f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("Rel", "Release",
        juce::NormalisableRange<float> {0.01f, 5.0f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("Gain", "Gain",
        juce::NormalisableRange<float> {0.0f, 1.0f, }, 0.1f));


    //Tuning Params
    params.push_back(std::make_unique<juce::AudioParameterFloat>("c", "cNote",
        -1.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ces", "cesNote",
        -1.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("d", "dNote",
        -1.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("des", "desNote",
        -1.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("e", "eNote",
        -1.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("f", "fNote",
        -1.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("fes", "fesNote",
        -1.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("g", "gNote",
        -1.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ges", "gesNote",
        -1.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("a", "aNote",
        -1.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("aes", "aesNote",
        -1.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("b", "bNote",
        -1.0f, 1.0f, 0.0f));

    //Karplus Params
    params.push_back(std::make_unique<juce::AudioParameterInt>("kAtt", "kAtt",
        1, 48000, 10));
    params.push_back(std::make_unique<juce::AudioParameterInt>("kSwitch", "kSwitch",
        1, 3, 1));
    params.push_back(std::make_unique<juce::AudioParameterInt>("kRel", "kRel",
        1, 48000, 48000));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("kFeed", "kFeed",
        juce::NormalisableRange<float>{0.0, 1.0, }, 1.0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("fmDepth", "fmDepth",
        juce::NormalisableRange<float>{100, 8000, }, 500));
    params.push_back(std::make_unique<juce::AudioParameterInt>("fmIndex", "fmIndex",
        1, 8, 500));

    //Filter Params
    // el valor de skew debe ser como 0.3
    params.push_back(std::make_unique<juce::AudioParameterFloat>("cutoff", "Cutoff",
        juce::NormalisableRange<float>(40.f, 20000.f, 1.f, 3.f), 1000.f));
    //juce::AudioParameterFloat("cutoff", "Cutoff", juce::NormalisableRange<float>(40.f, 20000.f, 1.f, 3.f), 1000.f);
    params.push_back(std::make_unique<juce::AudioParameterFloat>("q", "Q",
        juce::NormalisableRange<float>{1, 10, }, 2));
    params.push_back(std::make_unique<juce::AudioParameterBool>("filterOnOff", "OnOff", 1));


    //Mod Adsr Params
    params.push_back(std::make_unique<juce::AudioParameterFloat>("modAtt", "Attack",
        juce::NormalisableRange<float> {0.01f, 1.0f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("modDec", "Decay",
        juce::NormalisableRange<float> {0.01f, 1.0f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("modSus", "Sustain",
        juce::NormalisableRange<float> {0.0f, 1.0f, }, 0.6f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("modRel", "Release",
        juce::NormalisableRange<float> {0.01f, 5.0f, }, 0.1f));


    //Lfo Params
    params.push_back(std::make_unique<juce::AudioParameterFloat>("lfoFreq", "Frequency",
        juce::NormalisableRange<float>(0.0f, 20.0f, 0.01f, 0.3f, false), 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("lfoDepth", "Depth",
        juce::NormalisableRange<float>(0.0f, 12.0f, 0.001f, 0.3f, false), 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("lfoWave", "Wave",
        juce::NormalisableRange<float>(1.0f, 100.0f, 0.1f, 0.3f, false), 1.0f));


    //Global Params
    params.push_back((std::make_unique<juce::AudioParameterFloat>("gain", "gain",
        0, 1, 0.5)));
    params.push_back((std::make_unique<juce::AudioParameterInt>("selector", "selector",
        0, 2, 0)));

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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
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
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
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

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VarikeyProjectAudioProcessor();
}
