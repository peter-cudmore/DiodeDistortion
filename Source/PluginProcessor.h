/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class DiodeDistortionAudioProcessor  : public AudioProcessor,
                            public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    DiodeDistortionAudioProcessor();
    ~DiodeDistortionAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    #define PARAM_SETNAME "ParamSetName"
    #define PARAM_BYPASS "Bypass"
    #define PARAM_GAIN "Gain"
    #define PARAM_LEVEL "Level"
    
    AudioProcessorValueTreeState& getState() { return *mState; };
    void parameterChanged(const String& parameterID, float newValue)
            { MajorParamChange = true; };
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiodeDistortionAudioProcessor)
    bool MajorParamChange;
    ScopedPointer<AudioProcessorValueTreeState> mState;
    ScopedPointer<UndoManager> mUndoManager; 
    
    
    
    //DSP Parameters
    void processMono(float* buffer, int samples);
    void processStereo(float* lbuffer, float* rbuffer, int samples);
    
    LinearSmoothedValue<float> pGain;
    LinearSmoothedValue<float> pLevel;
    
    float coeff1;
    float coeff2;
    float coeff3;
    float beta;
    
    float lastinL;
    float lastoutL;
    float lastinR;
    float lastoutR;
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
