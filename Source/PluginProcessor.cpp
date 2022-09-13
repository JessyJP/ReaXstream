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

        //++++++++++++++++TODO: test parameter

        addParameter(test_gainParam = new juce::AudioParameterFloat("gain", // parameterID
            "Gain", // parameter name
            0.0f,   // minimum value
            1.0f,   // maximum value
            0.5f)); // default value


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
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // ==== BEGIN: Main Control logic ====
    if (direction == DirectionOfConnection::HostServerTransmitter)
    {
        if  (mode == ModeOfOperation::ReaStreamClassic) 
        {
            if (protocol == UDP)// At present lets support UDP connection only 
            {            
                ReaStreamClassicUDPtransmission(buffer);
            }
        }
        else if (mode == ModeOfOperation::ReaStreamMobile)
        {
            if (protocol == UDP)
            {
//           ReaStreamFrame::unpackTransmissionPackToAudioBuffer(buffer);
//           interleaveAudioBuffer(buffer);
                LOG(LOG_WARNING, "Protocols not implemented!")
            }
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
            if (protocol == UDP)// At present lets support UDP connection only 
            {
                ReaStreamClassicUDPreception(buffer);
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
    else { LOG(LOG_ERROR, "No such direction of transmission!") }

    // ==== END: Main Control logic ====

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
// This section contins the methods called by blcok process loop
void ReaXstreamAudioProcessor::ReaStreamClassicUDPtransmission(juce::AudioBuffer<float>& buffer)
{
    // If connection and therefore frame is requested
    if (resetFrame)
    {
        rsHeader = ReaStreamClassicFrame
        (
            default_packetID,
            connectionIdentifier,
            getTotalNumInputChannels(),
            getSampleRate()
        );
        // Along with the frame reset the buffer to all zero
        for (int i = 0; i < sizeof(UDPpackPayload); i++) { UDPpackPayload[i] = 0; }
        // Frame reset
        resetFrame = false;
    }
    //TODO: This could be computed only once in the future when channel number updates and requests frame resets!!!
    // Determine the if segmentation is needed or not
    int audioSamplesPerFrame = (MUT - headerByteCount) / (buffer.getNumChannels() * sizeof(float));

    //Pack the buffer
    int audioSampleBuffInd = 0;
    int bytesToWrite = MUT;
    while (audioSampleBuffInd < buffer.getNumSamples())
    {
        // On the last packet
        if (audioSampleBuffInd + audioSamplesPerFrame > buffer.getNumSamples())
        {
            audioSamplesPerFrame = buffer.getNumSamples() - audioSampleBuffInd;
            bytesToWrite = audioSamplesPerFrame * buffer.getNumChannels() * sizeof(float) + headerByteCount;
        }

        rsHeader.packNextAudioBufferInRSframe(buffer, UDPpackPayload, audioSampleBuffInd, audioSamplesPerFrame);
        // TODO: TESTING LINE ++++++++++++++
        *( (int*)(UDPpackPayload + 47) ) = rsHeader.packetIndex;
        // TODO: TESTING LINE ++++++++++++++
        udp->write(juce::String(ip), port, (void*)UDPpackPayload, bytesToWrite);

        audioSampleBuffInd += audioSamplesPerFrame;

        // Diagnostic message
        LOG(LOG_FRAME(rsHeader.packetIndex), rsHeader.printFrameHeader());
    }
    // TODO: lots of bug fixing here
    

}

void ReaXstreamAudioProcessor::ReaStreamClassicUDPreception(juce::AudioBuffer<float>& buffer)
{
    //  Variables to determine the how many packet-frames per buffer are needed and to handle the data overflow.
    const int audioSamples_NeededInBuffer = buffer.getNumSamples();
    int audioSamples_ReadCounter = 0;
    int audioSamples_InTheCurrentFrame = 0;
    int audioSamples_UntilBufferIsFull = 0;
    int audioSamples_OverFlow = 0;
    // There are 2 strategies.
    // Strategy 1: Read until the audio buffer is full and store the leftover for the next buffer request.
    // Strategy 2: Read until the UDP buffer is empty and store the leftover.
    while (audioSamples_ReadCounter < audioSamples_NeededInBuffer)
    {
        // Read the UPD packet data
        udp->read((void*)UDPpackDataRead, MUT, false);
        // Unpack the header
        rsHeader.unpackUDPheaderToRSframe(UDPpackDataRead);
        
        // Do validation/checks on the header
        // 1. Check the frame signature: if it matches it is a valid packet header; if not return and check on the next buffer.
        if (!rsHeader.isValidPacketID()) 
        { LOG(LOG_INFO,"[ReceptionClient][ReaStreamClassic][UDP]=> No Packets found!"); return; }
        // 2. Check the interconnect ID: if it matches it proceed; if not bet the next UDP payload-frame.
        if (connectionIdentifier != rsHeader.interconnectID)
        { 
            LOG(LOG_FRAME(-1), "Frame[" + connectionIdentifier + "] =/= [" + rsHeader.interconnectID + "]");
            continue;
        }       
        // 3. Check the number of channels: if it matches it proceed; if not ++++TODO: come back to that later
        if (rsHeader.numAudioChannels != buffer.getNumChannels()) 
        {
            LOG(LOG_ERROR, "The numberof channels [" + to_string(getTotalNumInputChannels()) +
                            "] != [" + to_string(rsHeader.numAudioChannels) + "]" ) ;
            continue;// TODO: how will that be handled??
        }
        // 4. Check the audio sample rate: if it matches it proceed; if not ++++TODO: come back to that later
        if ( rsHeader.audioSampleRate != getSampleRate() )
        {
            LOG(LOG_ERROR, "The sample rate [" + to_string(getSampleRate()) +
                            "] != [" + to_string(rsHeader.numAudioChannels) + "] in the frame.");
            continue;// TODO: how will that be handled??
        }
        
        // The header is check and validated, now pass the UDP audio data payload to the audio buffer
        LOG(LOG_FRAME(++rsHeader.packetIndex), rsHeader.printFrameHeader());

        // Calculate the audio samples in the current frame
        audioSamples_InTheCurrentFrame = rsHeader.sampleByteSize / (rsHeader.numAudioChannels * sizeof(float));
        // Determine the buffer overflow
        audioSamples_UntilBufferIsFull = audioSamples_NeededInBuffer - audioSamples_ReadCounter;
        if (audioSamples_UntilBufferIsFull <= audioSamples_InTheCurrentFrame)
        {
            audioSamples_OverFlow = audioSamples_InTheCurrentFrame - audioSamples_UntilBufferIsFull;
            if (audioSamples_UntilBufferIsFull == audioSamples_InTheCurrentFrame)
            {
                LOG(LOG_INFO, "Buffer Exactly Full!");
            }
            else
            {               
                LOG(LOG_INFO, "audioSamples_UntilBufferIsFull ["+to_string(audioSamples_UntilBufferIsFull) + "]"+
                              "audioSamples_InTheCurrentFrame [" + to_string(audioSamples_InTheCurrentFrame) + "]"+
                              "audioSamples_OverFlow [" + to_string(audioSamples_OverFlow) + "]");
            }
        }

        // ++++ TODO
        (UDPpackDataRead + headerByteCount); // Convert the data to floats


        
        audioSamples_ReadCounter += audioSamples_InTheCurrentFrame;
    }

    LOG(LOG_WARNING, "DONT't forget to take care of the pottential overflow");// TODO
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
// This seciton defines methods not used by the pluing processing method.

juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout propertyLayout;

    juce::StringArray connectionDirection;
    connectionDirection.add("DirectionOfConnection::ClientReceiver");
    connectionDirection.add("DirectionOfConnection::HostServerTransmitter");
    propertyLayout.add( std::make_unique<juce::AudioParameterChoice>("Direction","Direction", connectionDirection, 0) );

    return propertyLayout;
};

void* ReaXstreamAudioProcessor::getSet_ReaXstreamGUIpointer(void* ptr_in)
{// The whole editor is not needed 
 // we jut just the componenet holding all the interaction elements
    static ReaXstreamGUI* RXS_GUI = nullptr;
    if (ptr_in != nullptr) { RXS_GUI = (ReaXstreamGUI*)ptr_in; }//Set
    return (void*)RXS_GUI;// Normal Get
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReaXstreamAudioProcessor();
}
