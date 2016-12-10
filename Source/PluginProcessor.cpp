/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//Helpers

static String GetStrValue(float v) { return String(v);};
static String GetBypassStr(float v) { return (v != 0.0f) ? "Bypassed" : "Enabled";};

//==============================================================================
DiodeDistortionAudioProcessor::DiodeDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    
    mUndoManager = new UndoManager();
    mState = new AudioProcessorValueTreeState(*this, mUndoManager);
    
    //add each of your parameters
    mState->createAndAddParameter(PARAM_BYPASS, "Bypass", "", NormalisableRange<float>(0, 1, 1), 0, GetBypassStr, nullptr);
    
    mState->createAndAddParameter(PARAM_LEVEL, "Level", "", NormalisableRange<float>(0.0f, 10.0f, 0.01f), pLevel.getTargetValue(), GetStrValue, nullptr);
    
    mState->createAndAddParameter(PARAM_GAIN, "Gain", "", NormalisableRange<float>(1.0f, 50.0f, 0.05f), pGain.getTargetValue(), GetStrValue, nullptr);
    
    
    //Once all parameters are added, it is safe to create the actual ValueTree
    mState->state = ValueTree(PARAM_SETNAME);
    
    //add any controls you want to trigger a deeper update timed with the call to process
    mState->addParameterListener(PARAM_LEVEL, this);
    mState->addParameterListener(PARAM_GAIN, this);
    lastinL =0;
    lastoutL=0;
    
    lastinR=0;
    lastoutR=0;
    //start it off with deep updates regardless
    MajorParamChange = true;
}

DiodeDistortionAudioProcessor::~DiodeDistortionAudioProcessor()
{
    mState = nullptr;
    mUndoManager = nullptr;
}

//==============================================================================
const String DiodeDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DiodeDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DiodeDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double DiodeDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DiodeDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DiodeDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DiodeDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const String DiodeDistortionAudioProcessor::getProgramName (int index)
{
    return String();
}

void DiodeDistortionAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DiodeDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    const double rampLength = 0.05;
    
    pLevel.reset(sampleRate, rampLength);
    pGain.reset(sampleRate, rampLength);
    // Filter Parameters;
    double a = 0.01f;
    double b = 1.1f;
    double alpha = 1.3f;
    
    
    beta =50.0f;

    
    coeff1 = (float) ((2.0f*a*sampleRate - b)/(2.0f*a*sampleRate+b));
    coeff2 = (float) (1.0f/(2*a*sampleRate+b));
    coeff3 = (float) -((2.0f*alpha)/(2.0f*a*sampleRate+b));
}

void DiodeDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DiodeDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void DiodeDistortionAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    if (MajorParamChange == true)
    {
        pLevel.setValue(*mState->getRawParameterValue(PARAM_LEVEL));
        pGain.setValue(*mState->getRawParameterValue(PARAM_GAIN));
        MajorParamChange = false;
    }

    if(totalNumInputChannels == 1)
    {
        processMono(buffer.getWritePointer(0), buffer.getNumSamples());
    }
    else if (totalNumInputChannels==2)
    {
        processStereo(buffer.getWritePointer(0),buffer.getWritePointer(1), buffer.getNumSamples());
    }
}

void DiodeDistortionAudioProcessor::processMono(float* buffer, int samples)
{

    float level;
    float gain;
    
    for (int i=0; i<samples;i++)
    {
        level = pLevel.getNextValue();
        gain = pGain.getNextValue();
        
        buffer[i] *=gain;
        lastoutL =coeff1*lastoutL + coeff2*(lastinL + buffer[i]) + coeff3*sinh(beta*lastoutL);
        buffer[i] = level*lastoutL;
    }
}

void DiodeDistortionAudioProcessor::processStereo(float* lbuffer, float* rbuffer, int samples)
{
    float level;
    float gain;
    
    for (int i=0; i<samples;i++)
    {
        level = pLevel.getNextValue();
        gain = pGain.getNextValue();
        lbuffer[i] *=gain;
        rbuffer[i] *=gain;
        lastoutL =coeff1*lastoutL + coeff2*(lastinL + lbuffer[i]) + coeff3*sinh(beta*lastoutL);
        lastoutR =coeff1*lastoutR + coeff2*(lastinR + rbuffer[i]) + coeff3*sinh(beta*lastoutR);
        lbuffer[i] = level*lastoutL;
        rbuffer[i] = level*lastoutR;
    }
}

//==============================================================================
bool DiodeDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DiodeDistortionAudioProcessor::createEditor()
{
    return new DiodeDistortionAudioProcessorEditor (*this);
}

//==============================================================================
void DiodeDistortionAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    MemoryOutputStream stream(destData, false);
    mState->state.writeToStream(stream);
}

void DiodeDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid())
    {
        if (tree.hasType(PARAM_SETNAME))
        {
            mState->state = tree;
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DiodeDistortionAudioProcessor();
}
