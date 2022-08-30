/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ReaXsteamSetup.h"
#include "ReaStreamFrame.h"

// The debug section
#define logINFO         "ReaXstream [INFO]:  "
#define logDEBUG        "ReaXstream [DEBUG]:  "
#define logWARNING      "ReaXstream [WARNING]:  "
#define logERROR        "ReaXstream [ERROR]:  "
#define LOG(DTYPE,MSG) logger->outputDebugString( std::string(DTYPE) + std::string(MSG) );//Shorthand



//==============================================================================
/**
*/
class ReaXstreamAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    ReaXstreamAudioProcessor();
    ~ReaXstreamAudioProcessor() override;

    //==============================================================================
    ReaXsteamSetup setup;// This is the setup class
    ReaStreamFrame rframe;
    //==============================================================================
    std::shared_ptr<juce::Logger> logger;//Logger

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

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

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReaXstreamAudioProcessor)
};


