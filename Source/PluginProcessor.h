/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Interconnector.h"
#include "ReaXstreamFrames.h"


//==============================================================================
/**
*/
class ReaXstreamAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
                            , public Interconnector // Inheriting the connection setup class 
                            , public ReaStreamFrame // Inheriting the transmission framing  
{
public:
    //==============================================================================
    ReaXstreamAudioProcessor();
    ~ReaXstreamAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    //==============================================================================
    // Methods called by the processBlock method
    void ReaStreamClassicUDPtransmission(juce::AudioBuffer<float>& buffer);
    void ReaStreamClassicUDPreception(juce::AudioBuffer<float>& buffer);
    
    void computeAudiolevels(juce::AudioBuffer<float>& buffer);

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //==============================================================================
    // This seciton declares methods not used by the pluing processing method.
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState apvts{ *this, nullptr};//"Parameters", createParameterLayout() 
    juce::AudioParameterFloat* test_gainParam;
    // This will use a little trick to store get/set the GUI componenet pointer
    void* getSet_ReaXstreamGUIpointer(void* ptr_in);

private:

    // Audio level statistic Variables
    float rmsLevel_L, rmsLevel_R;
    float maxLevel_L, maxLevel_R;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReaXstreamAudioProcessor)
};


