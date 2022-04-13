/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceSynthAudioProcessor::JuceSynthAudioProcessor()
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
    ,vts(*this, nullptr, "Params", buildParams())
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
juce::AudioProcessorValueTreeState::ParameterLayout JuceSynthAudioProcessor::buildParams()
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
        juce::NormalisableRange<float>(0.0f, 10.0f, 0.001f, 0.3f, false), 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("lfoWave", "Wave",
        juce::NormalisableRange<float>(1.0f, 100.0f, 0.1f, 0.3f, false), 1.0f));


    //Global Params
    params.push_back((std::make_unique<juce::AudioParameterFloat>("gain", "gain",
        0, 1, 0.5)));
    params.push_back((std::make_unique<juce::AudioParameterInt>("selector", "selector",
        0, 2, 0)));

    return { params.begin(), params.end() };
}

JuceSynthAudioProcessor::~JuceSynthAudioProcessor()
{
}

//==============================================================================
const juce::String JuceSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JuceSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JuceSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JuceSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String JuceSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void JuceSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void JuceSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
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

void JuceSynthAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void JuceSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


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
            auto& gain = *vts.getRawParameterValue("Gain");

    //        //noteTuning.setTuning(NoteTuning::c, vts.getParameterAsValue("c").getValue());
    //        //noteTuning.setTuning(NoteTuning::ces, vts.getParameterAsValue("ces").getValue());
    //        //noteTuning.setTuning(NoteTuning::d, vts.getParameterAsValue("d").getValue());
    //        //noteTuning.setTuning(NoteTuning::des, vts.getParameterAsValue("des").getValue());
    //        //noteTuning.setTuning(NoteTuning::e, vts.getParameterAsValue("e").getValue());
    //        //noteTuning.setTuning(NoteTuning::f, vts.getParameterAsValue("f").getValue());
    //        //noteTuning.setTuning(NoteTuning::fes, vts.getParameterAsValue("fes").getValue());
    //        //noteTuning.setTuning(NoteTuning::g, vts.getParameterAsValue("g").getValue());
    //        //noteTuning.setTuning(NoteTuning::ges, vts.getParameterAsValue("ges").getValue());
    //        //noteTuning.setTuning(NoteTuning::a, vts.getParameterAsValue("a").getValue());
    //        //noteTuning.setTuning(NoteTuning::aes, vts.getParameterAsValue("aes").getValue());
    //        //noteTuning.setTuning(NoteTuning::b, vts.getParameterAsValue("b").getValue());


            tuning[0] = vts.getParameterAsValue("c").getValue();
            tuning[1] = vts.getParameterAsValue("ces").getValue();
            tuning[2] = vts.getParameterAsValue("d").getValue();
            tuning[3] = vts.getParameterAsValue("des").getValue();
            tuning[4] = vts.getParameterAsValue("e").getValue();
            tuning[5] = vts.getParameterAsValue("f").getValue();
            tuning[6] = vts.getParameterAsValue("fes").getValue();
            tuning[7] = vts.getParameterAsValue("g").getValue();
            tuning[8] = vts.getParameterAsValue("ges").getValue();
            tuning[9] = vts.getParameterAsValue("a").getValue();
            tuning[10] = vts.getParameterAsValue("aes").getValue();
            tuning[11] = vts.getParameterAsValue("b").getValue();
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
            voice->updateLfo(lfoFreq, lfoWave, lfoDepth);
            voice->updateModAdsr(vts.getParameterAsValue("modAtt").getValue(),
                vts.getParameterAsValue("modDec").getValue(),
                vts.getParameterAsValue("modSus").getValue(),
                vts.getParameterAsValue("modRel").getValue());
        }

    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool JuceSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JuceSynthAudioProcessor::createEditor()
{
    return new JuceSynthAudioProcessorEditor (*this);
}

//==============================================================================
void JuceSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceSynthAudioProcessor();
}
