/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ReaStreamFrame.h"


using namespace std;

//==============================================================================
ReaXstreamAudioProcessor::ReaXstreamAudioProcessor()
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
{
    // Initialize plug-in logger
//    std::unique_ptr<juce::FileLogger> m_flogger;
//    m_flogger = std::unique_ptr<juce::FileLogger>(juce::FileLogger::createDateStampedLogger("logs", "mylog", ".log", welcomeMsg));
    logger = std::shared_ptr<juce::Logger>(juce::Logger::getCurrentLogger());
    LOG(logINFO, welcomeMessage);

    setup = ReaXsteamSetup();
     
    if (!setup.connectionSetupReady)
    {
        LOG(logWARNING,"Requesting to setup the plugin inputs!!!")
    }


}

ReaXstreamAudioProcessor::~ReaXstreamAudioProcessor()
{
}

//==============================================================================
const juce::String ReaXstreamAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ReaXstreamAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ReaXstreamAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ReaXstreamAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ReaXstreamAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ReaXstreamAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ReaXstreamAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ReaXstreamAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ReaXstreamAudioProcessor::getProgramName (int index)
{
    return {};
}

void ReaXstreamAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ReaXstreamAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    //++++++++++++++++++++++++++++++
    
    
 

    //++++++++++++++++++++++++++++++
}

void ReaXstreamAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ReaXstreamAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ReaXstreamAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto numSamples = buffer.getNumSamples();
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    //++++++Control LOGIC
    if (setup.direction == DirectionOfConnection::HostServerTransmitter)
    {
        if  (setup.mode == ModeOfOperation::ReaStreamClassic) 
        {
            
            rframe.packAudioBufferToTransmissionPacket(buffer);

//            send(rframe);

            rframe.reset();
        }
        else if (setup.mode == ModeOfOperation::ReaStreamMobile)
        {
            LOG(logWARNING, "NOT implemented!")
        }
        else if (setup.mode == ModeOfOperation::ReaInterConnect)
        {
        }
        else { LOG(logERROR, "No such mode of opperation!") }

    }
    else if (setup.direction == DirectionOfConnection::ClientReceiver)
    {
        if (setup.mode == ModeOfOperation::ReaStreamClassic)
        {
            LOG(logWARNING, "NOT implemented!")
        }
        else if (setup.mode == ModeOfOperation::ReaInterConnect)
        {
            LOG(logWARNING, "NOT implemented!")
        }
        else { LOG(logERROR, "No such mode of opperation!") }
    
    }
    else { LOG(logERROR, "No such direction of transmission!") }

    //+++++CONTROL LOGIC

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    // TODO: should i keep that part?
}

//==============================================================================
bool ReaXstreamAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ReaXstreamAudioProcessor::createEditor()
{
    return new ReaXstreamAudioProcessorEditor (*this);
}

//==============================================================================
void ReaXstreamAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ReaXstreamAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReaXstreamAudioProcessor();
}
