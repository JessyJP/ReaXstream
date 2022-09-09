/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "Logger.h"

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
    // Calling 
    , Interconnector() , ReaStreamFrame()
{

    LOG(LOG_INFO, LoggerWelcomeMessage);
     
    if (!connectionEstablishedOK)
    {
        LOG(LOG_WARNING,"Requesting to setup the plugin inputs!!!")
    }
    rsHeader.printFrameHeader();
    LOG(LOG_WARNING," This part is not finished!!!")

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
    

    ReaXstreamAudioProcessor::getLatencySamples();


    // TODO: just enabling the connection state

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

    if ( !connectionEstablishedOK || resetInterConnection ) { setupInterConnection(); return; }
    // This will allow the process loop to be bypassed when the connection is not setup.

    juce::ScopedNoDenormals noDenormals;
    auto numSamples = buffer.getNumSamples();
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    //++++++Control LOGIC
    if (direction == DirectionOfConnection::HostServerTransmitter)
    {
        if  (mode == ModeOfOperation::ReaStreamClassic) 
        {
            if (protocol == UDP)// At present lets support UDP connection only 
            {
                // If connection and therefore frame is requested
                if (resetFrame)
                {
                    rsHeader = ReaStreamClassicFrame
                    (
                        default_packetID,
                        Interconnector::connectionIdentifier,
                        totalNumInputChannels,
                        getSampleRate()
                    );
                    // Along with the frame reset the buffer to all zero
                    for (int i = 0; i < sizeof(UDPpackPayload); i++) { UDPpackPayload[i] = char(0); }
                    // Frame reset
                    resetFrame = false;
                }
                //TODO: This could be computed only once in the future when channel number updates and requests frame resets!!!
                // Determine the if segmentation is needed or not
                int audioSamplesPerFrame = (MUT-rsHeader.headerByteCount)/(buffer.getNumChannels()* sizeof(float));

                //Pack the buffer
                int audioSampleBuffInd = 0;
                while(audioSampleBuffInd < buffer.getNumSamples())
                {
                    if (audioSampleBuffInd + audioSamplesPerFrame > buffer.getNumSamples())
                    {
                        audioSamplesPerFrame = buffer.getNumSamples() - audioSampleBuffInd;
                    }

                    rsHeader.packNextAudioBufferInRSframe(buffer, UDPpackPayload, audioSampleBuffInd, audioSamplesPerFrame);
                    audioSampleBuffInd += audioSamplesPerFrame;
                }

                LOG(LOG_FRAME(rsHeader.packetIndex), rsHeader.printFrameHeader());

                //           ReaStreamFrame::packAudioBufferToTransmissionPacket(buffer, getSampleRate());
                          // connectionIdentifier
               //            send(rframe);


                //           ReaStreamFrame::unpackTransmissionPackToAudioBuffer(buffer);
                //           interleaveAudioBuffer(buffer);

            }
        }
        else if (mode == ModeOfOperation::ReaStreamMobile)
        {
            LOG(LOG_WARNING, "Protocols not implemented!")
        }
        else if (mode == ModeOfOperation::ReaInterConnect)
        {
            LOG(LOG_WARNING, "Protocols not implemented!")
        }
        else { LOG(LOG_ERROR, "No such mode of opperation!") }

    }
    else if (direction == DirectionOfConnection::ClientReceiver)
    {
        if (mode == ModeOfOperation::ReaStreamClassic)
        {
            LOG(LOG_WARNING, "Protocols not implemented!")
        }
        else if (mode == ModeOfOperation::ReaStreamMobile)
        {
            LOG(LOG_WARNING, "Protocols not implemented!")
        }
        else if (mode == ModeOfOperation::ReaInterConnect)
        {
            LOG(LOG_WARNING, "Protocols not implemented!")
        }
        else { LOG(LOG_ERROR, "No such mode of opperation!") }
    
    }
    else { LOG(LOG_ERROR, "No such direction of transmission!") }

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


juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout propertyLayout;

    juce::StringArray connectionDirection;
    connectionDirection.add("DirectionOfConnection::ClientReceiver");
    connectionDirection.add("DirectionOfConnection::HostServerTransmitter");
    propertyLayout.add( std::make_unique<juce::AudioParameterChoice>("Direction","Direction", connectionDirection, 0) );

    return propertyLayout;
};


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReaXstreamAudioProcessor();
}
