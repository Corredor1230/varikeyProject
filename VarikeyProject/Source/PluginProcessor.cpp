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

    std::initializer_list<const char*> synthList
    {
        "none",
        "gen1Noise", "gen2Noise",
        "noise1Tone", "noise2Tone",
        "mix",
        "distInLeft", "distOutLeft",
        "distInRight", "distOutRight",
        "lopCutoff", "lopQ",
        "hipCutoff", "hipQ",
        "detune", "vibFreq", "vibDepth",
        "volume"
    };

    std::initializer_list<const char*> oscList
    {
        "Generator", "Additive", "Karplus", "Noise"
    };

//SYNTHS
    //GENERATOR
        //Left
        createIntParameter(params, "leftGenShape", "Wave Shape 1", 0, 3, 0);
        createFloatParameter(params, "leftGenNoiseLevel", "Noise Level 1", 0.f, 1.f, 0.01f, 0.f, 1.4);
        createIntParameter(params, "leftGenNoiseShape", "Noise Shape 1", 0, 1, 1);

        //Right
        createIntParameter(params, "rightGenShape", "Wave Shape 2", 0, 3, 0);
        createFloatParameter(params, "rightGenNoiseLevel", "Noise Level 2", 0.f, 1.f, 0.01f, 0.f, 1.4);
        createIntParameter(params, "rightGenNoiseShape", "Noise Shape 2", 0, 1, 1);

    //ADDITIVE
        //Left
        std::string additiveLeft = "additiveLeft";
        createFloatParameter(params, "additiveLeft0", "0 Left", 0.f, 8.f, 1.f, 8.f);

        for (int i = 1; i < 8; i++)
        {
            createFloatParameter(params, additiveLeft + std::to_string(i), std::to_string(i) + " Left", 0.f, 8.f, 1.f, 0.f);
        }

        //Right
        std::string additiveRight = "additiveRight";
        createFloatParameter(params, "additiveRight0", "0 Right", 0.f, 8.f, 1.f, 8.f);
        for (int i = 1; i < 9; i++)
        {
            createFloatParameter(params, additiveRight + std::to_string(i), std::to_string(i) + " Right", 0.f, 8.f, 1.f, 0.f);
        }

    //KARPLUS
        //Left
        createFloatParameter(params, "leftKarpAtt", "Karplus Attack 1", 0.f, 1.f, 0.001, 0.01, 0.4);
        createFloatParameter(params, "leftKarpRel", "Karplus Release 1", 0.f, 1.f, 0.001, 1.f, 0.4);
        createFloatParameter(params, "leftKarpFb", "Karplus Feedback 1", 0.f, 1.f, 0.001, 0.95f);
        createIntParameter(params, "leftKarpNoise", "Karplus Noise 1", 0, 1, 1);

        //Right
        createFloatParameter(params, "rightKarpAtt", "Karplus Attack 2", 0.f, 1.f, 0.001, 0.01, 0.4);
        createFloatParameter(params, "rightKarpRel", "Karplus Release 2", 0.f, 1.f, 0.001, 1.f, 0.4);
        createFloatParameter(params, "rightKarpFb", "Karplus Feedback 2", 0.f, 1.f, 0.001, 0.95f);
        createIntParameter(params, "rightKarpNoise", "Karplus Noise 2", 0, 1, 1);

    //NOISE
        //Left
        createFloatParameter(params, "leftNoiseTone", "Noise Tone 1", 0.0f, 1.0f, 0.001f, 1.0f);
        //Right
        createFloatParameter(params, "rightNoiseTone", "Noise Tone 2", 0.0f, 1.0f, 0.001f, 1.0f);

    //DISTORTION
        //Left

        createFloatParameter(params, "leftDistInput", "Input", 0.0f, 100.0f, 0.1f, 1.0f, 0.5);
        createFloatParameter(params, "leftDistOutput", "Output", 0.0f, 1.0f, 0.01f, 1.0f, 0.7);
        params.push_back(std::make_unique<juce::AudioParameterBool>("leftDistOnOff", "On/Off", false));

        //Right

        createFloatParameter(params, "rightDistInput", "Input", 0.0f, 10.0f, 0.1f, 1.0f, 0.5);
        createFloatParameter(params, "rightDistOutput", "Output", 0.0f, 1.0f, 0.01f, 1.0f, 0.7);
        params.push_back(std::make_unique<juce::AudioParameterBool>("rightDistOnOff", "On/Off", false));


    //CHOICE
        params.push_back(std::make_unique<juce::AudioParameterChoice>("leftSynthChoice", "Left Synth", 
            juce::StringArray(oscList), 1));
        params.push_back(std::make_unique<juce::AudioParameterChoice>("rightSynthChoice", "Right Synth", 
            juce::StringArray(oscList), 1));
        createFloatParameter(params, "synthMix", "Synth Mix", -1.0f, 1.0f, 0.01f, 0.0f);

//PROCESSES
    //FILTER
        //LOP
        createFloatParameter(params, "lopCutoff", "Cutoff LOP", 20.0f, 20000.0f, 1.0f, 1000.0f, 0.6);
        params.push_back(std::make_unique<juce::AudioParameterBool>("lopOnOff", "On/Off", false));
        createFloatParameter(params, "lopQ", "Q LOP", 1.0f, 10.0f, 0.01f, 1.0f);

        //HIP
        createFloatParameter(params, "hipCutoff", "Cutoff HIP", 20.0f, 20000.0f, 1.0f, 1000.0f, 0.6);
        params.push_back(std::make_unique<juce::AudioParameterBool>("hipOnOff", "On/Off", false));
        createFloatParameter(params, "hipQ", "Q HIP", 1.0f, 10.0f, 0.01f, 1.0f);

    //ADSR
        //Amp
        createFloatParameter(params, "ampAdsrAtt", "Attack 1", 0.01, 5.0f, 0.01, 0.03, 0.6);
        createFloatParameter(params, "ampAdsrDec", "Decay 1", 0.01, 5.0f, 0.01, 0.03, 0.6);
        createFloatParameter(params, "ampAdsrSus", "Sustain 1", 0.0, 1.0f, 0.01f, 0.5f);
        createFloatParameter(params, "ampAdsrRel", "Release 1", 0.01, 5.0f, 0.01, 0.03, 0.6);

        //Mod
        createFloatParameter(params, "modAdsrAtt", "Attack 2", 0.01, 5.0f, 0.01, 0.03, 0.3);
        createFloatParameter(params, "modAdsrDec", "Decay 2", 0.01, 5.0f, 0.01, 0.03, 0.3);
        createFloatParameter(params, "modAdsrSus", "Sustain 2", 0.0, 1.0f, 0.01f, 0.5f);
        createFloatParameter(params, "modAdsrRel", "Release 2", 0.01, 5.0f, 0.01, 0.03, 0.3);
        params.push_back(std::make_unique<juce::AudioParameterChoice>("modAdsrRoute", "Route Adsr", 
            juce::StringArray(synthList), 0));

    //LFO
        //Lfo 1
        createFloatParameter(params, "lfo1Freq", "Frequency 1", 0.0f, 15.0f, 0.01f, 0.0f, 0.5);
        createFloatParameter(params, "lfo1Depth", "Depth 1", 0.0f, 1.0f, 0.01f, 0.0f);
        createFloatParameter(params, "lfo1Shape", "Shape 1", 1.0f, 100.0f, 0.1f, 1.0f);
        params.push_back(std::make_unique<juce::AudioParameterChoice>("lfo1Route", "Route Lfo 1", 
            juce::StringArray(synthList), 0));

        //Lfo 2
        createFloatParameter(params, "lfo2Freq", "Frequency 2", 0.0f, 15.0f, 0.01f, 0.0f, 0.5);
        createFloatParameter(params, "lfo2Depth", "Depth 2", 0.0f, 1.0f, 0.01f, 0.0f);
        createFloatParameter(params, "lfo2Shape", "Shape 2", 1.0f, 100.0f, 0.1f, 1.0f);
        params.push_back(std::make_unique<juce::AudioParameterChoice>("lfo2Route", "Route Lfo 2", 
            juce::StringArray(synthList), 0));

        //Lfo 3
        createFloatParameter(params, "lfo3Freq", "Frequency 3", 0.0f, 15.0f, 0.01f, 0.0f, 0.5);
        createFloatParameter(params, "lfo3Depth", "Depth 3", 0.0f, 1.0f, 0.01f, 0.0f);
        createFloatParameter(params, "lfo3Shape", "Shape 3", 1.0f, 100.0f, 0.1f, 1.0f);
        params.push_back(std::make_unique<juce::AudioParameterChoice>("lfo3Route", "Route Lfo 3", 
            juce::StringArray(synthList), 0));

        //Lfo 4
        createFloatParameter(params, "lfo4Freq", "Frequency 4", 0.0f, 15.0f, 0.01f, 0.0f, 0.5);
        createFloatParameter(params, "lfo4Depth", "Depth 4", 0.0f, 1.0f, 0.01f, 0.0f);
        createFloatParameter(params, "lfo4Shape", "Shape 4", 1.0f, 100.0f, 0.1f, 1.0f);
        params.push_back(std::make_unique<juce::AudioParameterChoice>("lfo4Route", "Route Lfo 4", 
            juce::StringArray(synthList), 0));

//GLOBAL
    //OTHER
        createFloatParameter(params, "detune", "Detune", -1.0f, 1.0f, 0.01f, 0.0f);
        createFloatParameter(params, "vibFreq", "Vibrato Frequency", 0.0f, 15.f, 0.01f, 0.0f, 0.3);
        createFloatParameter(params, "vibDepth", "Vibrato Depth", 0.0f, 1.f, 0.001f, 0.0f);
        createFloatParameter(params, "volume", "Volume", -100.0f, 0.0f, 0.1f, -20.f);

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
    filter.init(sampleRate);
    filter.buildUserInterface(&filtCtrl);
    lfo1Mod.init(sampleRate);
    lfo2Mod.init(sampleRate);
    lfo3Mod.init(sampleRate);
    lfo4Mod.init(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getNumOutputChannels();
    juceLopFilt.prepare(spec);
    juceLopFilt.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    juceHipFilt.prepare(spec);
    juceHipFilt.setType(juce::dsp::StateVariableTPTFilterType::highpass);

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

void VarikeyProjectAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels(); // esto no se usa
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    buffer.clear();

    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {

            //auto& attack = *vts.getRawParameterValue("Att");
            //GENERATOR
            auto& leftGenShape = *vts.getRawParameterValue("leftGenShape");
            auto& leftGenNoiseLevel = *vts.getRawParameterValue("leftGenNoiseLevel");
            auto& leftGenNoiseShape = *vts.getRawParameterValue("leftGenNoiseShape");

            auto& rightGenShape = *vts.getRawParameterValue("rightGenShape");
            auto& rightGenNoiseLevel = *vts.getRawParameterValue("rightGenNoiseLevel");
            auto& rightGenNoiseShape = *vts.getRawParameterValue("rightGenNoiseShape");

            //ADDITIVE
            std::array<float, 8> additiveLeft;
            std::array<float, 8> additiveRight;

            auto& additiveLeft0 = *vts.getRawParameterValue("additiveLeft0");
            auto& additiveLeft1 = *vts.getRawParameterValue("additiveLeft1");
            auto& additiveLeft2 = *vts.getRawParameterValue("additiveLeft2");
            auto& additiveLeft3 = *vts.getRawParameterValue("additiveLeft3");
            auto& additiveLeft4 = *vts.getRawParameterValue("additiveLeft4");
            auto& additiveLeft5 = *vts.getRawParameterValue("additiveLeft5");
            auto& additiveLeft6 = *vts.getRawParameterValue("additiveLeft6");
            auto& additiveLeft7 = *vts.getRawParameterValue("additiveLeft7");
            additiveLeft[0] = additiveLeft0.load();
            additiveLeft[1] = additiveLeft1.load();
            additiveLeft[2] = additiveLeft2.load();
            additiveLeft[3] = additiveLeft3.load();
            additiveLeft[4] = additiveLeft4.load();
            additiveLeft[5] = additiveLeft5.load();
            additiveLeft[6] = additiveLeft6.load();
            additiveLeft[7] = additiveLeft7.load();

            
            auto& additiveRight0 = *vts.getRawParameterValue("additiveRight0");
            auto& additiveRight1 = *vts.getRawParameterValue("additiveRight1");
            auto& additiveRight2 = *vts.getRawParameterValue("additiveRight2");
            auto& additiveRight3 = *vts.getRawParameterValue("additiveRight3");
            auto& additiveRight4 = *vts.getRawParameterValue("additiveRight4");
            auto& additiveRight5 = *vts.getRawParameterValue("additiveRight5");
            auto& additiveRight6 = *vts.getRawParameterValue("additiveRight6");
            auto& additiveRight7 = *vts.getRawParameterValue("additiveRight7");
            additiveRight[0] = additiveRight0.load();
            additiveRight[1] = additiveRight1.load();
            additiveRight[2] = additiveRight2.load();
            additiveRight[3] = additiveRight3.load();
            additiveRight[4] = additiveRight4.load();
            additiveRight[5] = additiveRight5.load();
            additiveRight[6] = additiveRight6.load();
            additiveRight[7] = additiveRight7.load();

            //KARPLUS
            auto& leftKarpAtt = *vts.getRawParameterValue("leftKarpAtt");
            auto& leftKarpRel = *vts.getRawParameterValue("leftKarpRel");
            auto& leftKarpFb = *vts.getRawParameterValue("leftKarpFb");
            auto& leftKarpNoise = *vts.getRawParameterValue("leftKarpNoise");

            auto& rightKarpAtt = *vts.getRawParameterValue("rightKarpAtt");
            auto& rightKarpRel = *vts.getRawParameterValue("rightKarpRel");
            auto& rightKarpFb = *vts.getRawParameterValue("rightKarpFb");
            auto& rightKarpNoise = *vts.getRawParameterValue("rightKarpNoise");


            //NOISE
            auto& leftNoiseTone = *vts.getRawParameterValue("leftNoiseTone");
            auto& rightNoiseTone = *vts.getRawParameterValue("rightNoiseTone");

            //DIST
            auto& leftDistInput = *vts.getRawParameterValue("leftDistInput");
            auto& leftDistOutput = *vts.getRawParameterValue("leftDistOutput");
            auto& leftDistOnOff = *vts.getRawParameterValue("leftDistOnOff");

            auto& rightDistInput = *vts.getRawParameterValue("rightDistInput");
            auto& rightDistOutput = *vts.getRawParameterValue("rightDistOutput");
            auto& rightDistOnOff = *vts.getRawParameterValue("rightDistOnOff");

            //CHOICE
            auto& leftSynthChoice = *vts.getRawParameterValue("leftSynthChoice");
            auto& rightSynthChoice = *vts.getRawParameterValue("rightSynthChoice");
            auto& synthMix = *vts.getRawParameterValue("synthMix");

            //FILTER
            auto& lopOnOff = *vts.getRawParameterValue("lopOnOff");
            auto& lopCutoff = *vts.getRawParameterValue("lopCutoff");
            auto& lopQ = *vts.getRawParameterValue("lopQ");
            auto& hipOnOff = *vts.getRawParameterValue("hipOnOff");
            auto& hipCutoff = *vts.getRawParameterValue("hipCutoff");
            auto& hipQ = *vts.getRawParameterValue("hipQ");

            loCut = lopCutoff.load();
            loQ = lopQ.load();
            juceLopFilt.setCutoffFrequency(loCut);
            juceLopFilt.setResonance(loQ);
            loSwitch = lopOnOff.load();
            hiCut = hipCutoff.load();
            hiQ = hipQ.load();
            juceHipFilt.setCutoffFrequency(hiCut);
            juceHipFilt.setResonance(hiQ);
            hiSwitch = hipOnOff.load();



            //ADSR
            auto& ampAdsrAtt = *vts.getRawParameterValue("ampAdsrAtt");
            auto& ampAdsrDec = *vts.getRawParameterValue("ampAdsrDec");
            auto& ampAdsrSus = *vts.getRawParameterValue("ampAdsrSus");
            auto& ampAdsrRel = *vts.getRawParameterValue("ampAdsrRel");

            auto& modAdsrAtt = *vts.getRawParameterValue("modAdsrAtt");
            auto& modAdsrDec = *vts.getRawParameterValue("modAdsrDec");
            auto& modAdsrSus = *vts.getRawParameterValue("modAdsrSus");
            auto& modAdsrRel = *vts.getRawParameterValue("modAdsrRel");
            auto& modAdsrRoute = *vts.getRawParameterValue("modAdsrRoute");
            modAdsrR = modAdsrRoute.load();

            //LFO
            auto& lfo1Freq = *vts.getRawParameterValue("lfo1Freq");
            auto& lfo1Depth = *vts.getRawParameterValue("lfo1Depth");
            auto& lfo1Shape = *vts.getRawParameterValue("lfo1Shape");
            auto& lfo1Route = *vts.getRawParameterValue("lfo1Route");

            auto& lfo2Freq = *vts.getRawParameterValue("lfo2Freq");
            auto& lfo2Depth = *vts.getRawParameterValue("lfo2Depth");
            auto& lfo2Shape = *vts.getRawParameterValue("lfo2Shape");
            auto& lfo2Route = *vts.getRawParameterValue("lfo2Route");

            auto& lfo3Freq = *vts.getRawParameterValue("lfo3Freq");
            auto& lfo3Depth = *vts.getRawParameterValue("lfo3Depth");
            auto& lfo3Shape = *vts.getRawParameterValue("lfo3Shape");
            auto& lfo3Route = *vts.getRawParameterValue("lfo3Route");

            auto& lfo4Freq = *vts.getRawParameterValue("lfo4Freq");
            auto& lfo4Depth = *vts.getRawParameterValue("lfo4Depth");
            auto& lfo4Shape = *vts.getRawParameterValue("lfo4Shape");
            auto& lfo4Route = *vts.getRawParameterValue("lfo4Route");

            lfo1FreqCtrl = lfo1Freq.load();
            lfo1DepthCtrl = lfo1Depth.load();
            lfo1WaveCtrl = lfo1Shape.load();
            lfo1RouteCtrl = lfo1Route.load();

            lfo2FreqCtrl = lfo2Freq.load();
            lfo2DepthCtrl = lfo2Depth.load();
            lfo2WaveCtrl = lfo2Shape.load();
            lfo2RouteCtrl = lfo2Route.load();

            lfo3FreqCtrl = lfo3Freq.load();
            lfo3DepthCtrl = lfo3Depth.load();
            lfo3WaveCtrl = lfo3Shape.load();
            lfo3RouteCtrl = lfo3Route.load();

            lfo4FreqCtrl = lfo4Freq.load();
            lfo4DepthCtrl = lfo4Depth.load();
            lfo4WaveCtrl = lfo4Shape.load();
            lfo4RouteCtrl = lfo4Route.load();

            //GLOBAL
            auto& detune = *vts.getRawParameterValue("detune");
            auto& vibFreq = *vts.getRawParameterValue("vibFreq");
            auto& vibDepth = *vts.getRawParameterValue("vibDepth");
            auto& volume = *vts.getRawParameterValue("volume");

            //TUNING
            std::array<float, 12> tuningArray;
            auto& bassControlsTuning = *vts.getRawParameterValue("bassControlsTuning");
            auto& keyboardBreak = *vts.getRawParameterValue("keyboardBreak");

            auto& tuning0 = *vts.getRawParameterValue("tuning0");
            auto& tuning1 = *vts.getRawParameterValue("tuning1");
            auto& tuning2 = *vts.getRawParameterValue("tuning2");
            auto& tuning3 = *vts.getRawParameterValue("tuning3");
            auto& tuning4 = *vts.getRawParameterValue("tuning4");
            auto& tuning5 = *vts.getRawParameterValue("tuning5");
            auto& tuning6 = *vts.getRawParameterValue("tuning6");
            auto& tuning7 = *vts.getRawParameterValue("tuning7");
            auto& tuning8 = *vts.getRawParameterValue("tuning8");
            auto& tuning9 = *vts.getRawParameterValue("tuning9");
            auto& tuning10 = *vts.getRawParameterValue("tuning10");
            auto& tuning11 = *vts.getRawParameterValue("tuning11");
            tuningArray[0] = tuning0.load();
            tuningArray[1] = tuning1.load();
            tuningArray[2] = tuning2.load();
            tuningArray[3] = tuning3.load();
            tuningArray[4] = tuning4.load();
            tuningArray[5] = tuning5.load();
            tuningArray[6] = tuning6.load();
            tuningArray[7] = tuning7.load();
            tuningArray[8] = tuning8.load();
            tuningArray[9] = tuning9.load();
            tuningArray[10] = tuning10.load();
            tuningArray[11] = tuning11.load();
            noteTuning.setTuning(tuningArray);

            auto& scaleCenter = *vts.getRawParameterValue("scaleCenter");

            voice->updateLeftGenerator(leftGenShape.load(), leftGenNoiseLevel.load(), leftGenNoiseShape.load());
            voice->updateRightGenerator(rightGenShape.load(), rightGenNoiseLevel.load(), rightGenNoiseShape.load());
            voice->updateLeftAdditive(additiveLeft);
            voice->updateRightAdditive(additiveRight);
            voice->updateLeftKarplus(leftKarpAtt.load(), leftKarpRel.load(), leftKarpFb.load(), leftKarpNoise.load());
            voice->updateRightKarplus(rightKarpAtt.load(), rightKarpRel.load(), rightKarpFb.load(), rightKarpNoise.load());
            voice->updateLeftNoise(leftNoiseTone.load());
            voice->updateRightNoise(rightNoiseTone.load());
            voice->updateChoice(leftSynthChoice.load(), rightSynthChoice.load(), synthMix.load());

            voice->updateLeftDist(leftDistInput.load(), leftDistOutput.load(), leftDistOnOff.load());
            voice->updateRightDist(rightDistInput.load(), rightDistOutput.load(), rightDistOnOff.load());
            voice->updateLopFilter(lopOnOff.load(), lopCutoff.load(), lopQ.load());
            voice->updateHipFilter(hipOnOff.load(), hipCutoff.load(), hipQ.load());
            voice->updateAmpAdsr(ampAdsrAtt.load(), ampAdsrDec.load(), ampAdsrSus.load(), ampAdsrRel.load());
            voice->updateModAdsr(modAdsrAtt.load(), modAdsrDec.load(), modAdsrSus.load(), modAdsrRel.load(), modAdsrRoute.load());
            voice->updateLfo1(lfo1Freq.load(), lfo1Depth.load(), lfo1Shape.load(), lfo1Route.load());
            voice->updateLfo2(lfo2Freq.load(), lfo2Depth.load(), lfo2Shape.load(), lfo2Route.load());
            voice->updateLfo3(lfo3Freq.load(), lfo3Depth.load(), lfo3Shape.load(), lfo3Route.load());
            voice->updateLfo4(lfo4Freq.load(), lfo4Depth.load(), lfo4Shape.load(), lfo4Route.load());
            voice->updateGlobal(detune.load(), vibFreq.load(), vibDepth.load(), volume.load(), isGlobalFilter(modAdsrR));
            voice->updateTuner(tuningArray, bassControlsTuning.load(), keyboardBreak.load(), scaleCenter.load());

            lfo1Mod.setFreq(lfo1Freq.load());
            lfo1Mod.updateLfo(lfo1Shape.load(), lfo1Depth.load());

            lfo2Mod.setFreq(lfo2Freq.load());
            lfo2Mod.updateLfo(lfo2Shape.load(), lfo2Depth.load());

            lfo3Mod.setFreq(lfo3Freq.load());
            lfo3Mod.updateLfo(lfo3Shape.load(), lfo3Depth.load());

            lfo4Mod.setFreq(lfo4Freq.load());
            lfo4Mod.updateLfo(lfo4Shape.load(), lfo4Depth.load());

            volumeDb = volume.load();
            linearVolume = juce::Decibels::decibelsToGain(volumeDb);
        }


    }


    auto audioBlock = juce::dsp::AudioBlock<float>{ buffer };
    auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);
    
    //filtCtrl.setParamValue("lopCutoff", loCut);
    //filtCtrl.setParamValue("lopQ", loQ);
    //filtCtrl.setParamValue("lopOnOff", loSwitch);
    //filtCtrl.setParamValue("hipCutoff", hiCut);
    //filtCtrl.setParamValue("hipQ", hiQ);
    //filtCtrl.setParamValue("hipOnOff", hiSwitch);

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    if (isGlobalFilter(modAdsrR))
    {
        if (loSwitch) juceLopFilt.process(context);
        if (hiSwitch) juceHipFilt.process(context);
    }

    //if(isGlobalFilter(modAdsrR))
    //filter.compute(buffer.getNumSamples(), buffer.getArrayOfWritePointers(), buffer.getArrayOfWritePointers());

    if (hasTremolo(lfo1RouteCtrl, lfo2RouteCtrl, lfo3RouteCtrl, lfo4RouteCtrl))
    {
        startGain = endGain;
        for (int samp = 0; samp < buffer.getNumSamples(); samp++)
        {
            lfo1Sample = lfo1Mod.getNextSample() * (lfo1RouteCtrl == 17);
            lfo2Sample = lfo2Mod.getNextSample() * (lfo2RouteCtrl == 17);
            lfo3Sample = lfo3Mod.getNextSample() * (lfo3RouteCtrl == 17);
            lfo4Sample = lfo4Mod.getNextSample() * (lfo4RouteCtrl == 17);
            tremoloVolume = (((lfo1Sample + lfo2Sample + lfo3Sample + lfo4Sample) + 1) / 2);
            endGain = linearVolume * tremoloVolume;
        }
        buffer.applyGainRamp(0, buffer.getNumSamples(), startGain, endGain);
    }
    else buffer.applyGain(linearVolume);

    //buffer.applyGain(linearVolume);


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

bool VarikeyProjectAudioProcessor::isGlobalFilter(int modAdsrRoute)
{
    switch (modAdsrRoute)
    {
    case 10:
        return false;
    case 11:
        return false;
    case 12:
        return false;
    case 13:
        return false;
    default:
        return true;
    }
}

bool VarikeyProjectAudioProcessor::hasTremolo(int lfo1Route, int lfo2Route, int lfo3Route, int lfo4Route)
{
    if (lfo1Route == 17) return true;
    else if (lfo2Route == 17) return true;
    else if (lfo3Route == 17) return true;
    else if (lfo4Route == 17) return true;
    else return false;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VarikeyProjectAudioProcessor();
}

