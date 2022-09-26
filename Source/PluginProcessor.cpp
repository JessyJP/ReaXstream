/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Enumerations.h"
#include "Logger.h"


#include "UnitTest.h"// TODO: FOR TESTING !!!!!!!! REMOVE ME

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
    static const std::string name_thisMethod = "[ReaXstreamAudioProcessor::ReaXstreamAudioProcessor()]: ";// Prefix for loggin
    LOG(LOG_INFO, name_thisMethod + LoggerWelcomeMessage);
     
    if (!connectionEstablishedOK)
    {
        LOG(LOG_WARNING, name_thisMethod+"Requesting to setup the plugin inputs!!!")
    }
    rsHeader.printFrameHeader();
    LOG(LOG_WARNING, name_thisMethod+"This part is not finished!!!")

        //++++++++++++++++TODO: test parameter

        addParameter(test_gainParam = new juce::AudioParameterFloat("gain", // parameterID
            "Gain", // parameter name
            0.0f,   // minimum value
            1.0f,   // maximum value
            0.5f)); // default value

    UnitTest_Enumerations();//TODO: this is UNIT TEST Fcuntion and has to be removed

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

    // Reset the meter values
    rmsLevel_L.reset(sampleRate, 0.5);
    rmsLevel_R.reset(sampleRate, 0.5);
    maxLevel_L.reset(sampleRate, 0.5);
    maxLevel_R.reset(sampleRate, 0.5);

    rmsLevel_L.setCurrentAndTargetValue(-100.f);
    rmsLevel_R.setCurrentAndTargetValue(-100.f);
    maxLevel_L.setCurrentAndTargetValue(-100.f);
    maxLevel_R.setCurrentAndTargetValue(-100.f);

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
    const std::string name_thisMethod = "[ReaXstreamAudioProcessor::processBlock(...)]:";// Prefix for loggin
    if ( !connectionEstablishedOK || resetInterConnection ) { setupInterConnection(); return; }
    // This will allow the process loop to be bypassed when the connection is not setup.

    juce::ScopedNoDenormals noDenormals;// TODO: I don't know what this is for!
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // ==== BEGIN: Main Control logic ====
    // The inputs for the control flow validated when the connection is established
    if (direction == DirectionOfConnection::HostServerTransmitter)
    {
        if  (mode == ModeOfOperation::ReaStreamClassic) 
        {
            if (protocol == UDP)// At present lets support UDP connection only 
            {            
                LOG(LOG_INFO, name_thisMethod + " ReaStreamClassicUDPtransmission(buffer) -> called");
                ReaStreamClassicUDPtransmission(buffer);
                LOG(LOG_INFO, name_thisMethod + " ReaStreamClassicUDPtransmission(buffer) -> done");
            }
        }
        else if (mode == ModeOfOperation::ReaStreamMobile)
        {
            if (protocol == UDP)
            {
  
            }
        }
        else if (mode == ModeOfOperation::ReaInterConnect)
        {
            LOG(LOG_WARNING, name_thisMethod + "Protocols not implemented!")
        }
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
            LOG(LOG_INFO, name_thisMethod + " unpackTransmissionPackToAudioBuffer(buffer) -> called");
//           ReaStreamFrame::unpackTransmissionPackToAudioBuffer(buffer);
//           interleaveAudioBuffer(buffer);
            LOG(LOG_INFO, name_thisMethod + " unpackTransmissionPackToAudioBuffer(buffer) -> done");
        }
        else if (mode == ModeOfOperation::ReaInterConnect)
        {
            LOG(LOG_WARNING, name_thisMethod + "Protocols not implemented!")
        }
    }

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

    // Only compute the audio buffer is the GUI is created and active
    if (editorIsCreatedAndActiveState)
    {
        // Compute the audio levels for the GUI
        computeAudiolevels(buffer);
    }

}

//==============================================================================
// This section contins the methods called by blcok process loop
void ReaXstreamAudioProcessor::ReaStreamClassicUDPtransmission(juce::AudioBuffer<float>& buffer)
{
    const std::string name_thisMethod = "[ReaXstreamAudioProcessor::ReaStreamClassicUDPtransmission(...)]:";// Prefix for loggin
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
        LOG(LOG_INFO, name_thisMethod + " Frame Reset!");
    }
    //TODO: This could be computed only once in the future when channel number updates and requests frame resets!!!
    // Determine the if segmentation is needed or not
    int audioSamplesPerFrame = (MUT - headerByteSize) / (buffer.getNumChannels() * sizeof(float));

    //Pack the buffer
    int audioSampleBuffInd = 0;
    int bytesToWrite = MUT;
    while (audioSampleBuffInd < buffer.getNumSamples())
    {
        // On the last packet
        if (audioSampleBuffInd + audioSamplesPerFrame > buffer.getNumSamples())
        {
            audioSamplesPerFrame = buffer.getNumSamples() - audioSampleBuffInd;
            bytesToWrite = audioSamplesPerFrame * buffer.getNumChannels() * sizeof(float) + headerByteSize;
        }

        rsHeader.packNextAudioBufferInRSframe(buffer, UDPpackPayload, audioSampleBuffInd, audioSamplesPerFrame);
        // TODO: TESTING LINE ++++++++++++++
        *( (int*)(UDPpackPayload + 47) ) = rsHeader.packetIndex;
        // TODO: TESTING LINE ++++++++++++++
        udp->write(juce::String(ip), port, (void*)UDPpackPayload, bytesToWrite);

        audioSampleBuffInd += audioSamplesPerFrame;

        // Diagnostic message
        LOG(LOG_FRAME(name_thisMethod,rsHeader.packetIndex), rsHeader.printFrameHeader());
    }
    // TODO: lots of bug fixing here
    

}

void ReaXstreamAudioProcessor::ReaStreamClassicUDPreception(juce::AudioBuffer<float>& buffer)
{
    const std::string name_thisMethod = "[ReaXstreamAudioProcessor::ReaStreamClassicUDPreception(...)]:";// Prefix for loggin
    //  Variables to determine the how many packet-frames per buffer are needed and to handle the data overflow.
    const int audioSamples_NeededInBuffer = buffer.getNumSamples();
    int audioSamples_WriteCounter = 0;
    int audioSamples_InTheCurrentFrame = 0;
    int audioSamples_UntilBufferIsFull = 0;
    int audioSamples_OverFlow = 0;
    // There are 2 strategies.
    // Strategy 1: Read until the audio buffer is full and store the leftover for the next buffer request.
    // Strategy 2: Read until the UDP buffer is empty and store the leftover.
    while (audioSamples_WriteCounter < audioSamples_NeededInBuffer)
    {
        // Read the UPD packet data
        udp->read((void*)UDPpackDataRead, MUT, false);
        // Unpack the header
        rsHeader.unpackUDPheaderToRSframe(UDPpackDataRead);
        
        // Do validation/checks on the header
        // 1. Check the frame signature: if it matches it is a valid packet header; if not return and check on the next buffer.
        if (!rsHeader.isValidPacketID()) 
        { LOG(LOG_INFO, name_thisMethod+"[ReceptionClient][ReaStreamClassic][UDP]=> No Packets found!"); return; }
        // 2. Check the interconnect ID: if it matches it proceed; if not bet the next UDP payload-frame.
        if (connectionIdentifier != rsHeader.interconnectID)
        { 
            LOG(LOG_FRAME(name_thisMethod, -1), "Frame[" + connectionIdentifier + "] =/= [" + rsHeader.interconnectID + "]");
            continue;
        }       
        // 3. Check the number of channels: if it matches it proceed; if not ++++TODO: come back to that later
        if (rsHeader.numAudioChannels != buffer.getNumChannels()) 
        {
            LOG(LOG_ERROR, name_thisMethod + "The numberof channels [" + to_string(getTotalNumInputChannels()) +
                            "] != [" + to_string(rsHeader.numAudioChannels) + "]" ) ;
            continue;// TODO: how will that be handled??
        }
        // 4. Check the audio sample rate: if it matches it proceed; if not ++++TODO: come back to that later
        if ( rsHeader.audioSampleRate != getSampleRate() )
        {
            LOG(LOG_ERROR, name_thisMethod + "The sample rate [" + to_string(getSampleRate()) +
                            "] != [" + to_string(rsHeader.numAudioChannels) + "] in the frame.");
            continue;// TODO: how will that be handled??
        }
        
        // The header is check and validated, now pass the UDP audio data payload to the audio buffer
        LOG(LOG_FRAME(name_thisMethod, ++rsHeader.packetIndex), rsHeader.printFrameHeader());

        // Calculate the audio samples in the current frame
        audioSamples_InTheCurrentFrame = rsHeader.sampleByteSize / (rsHeader.numAudioChannels * sizeof(float));
        // Determine the buffer overflow
        audioSamples_UntilBufferIsFull = audioSamples_NeededInBuffer - audioSamples_WriteCounter;
        if (audioSamples_UntilBufferIsFull <= audioSamples_InTheCurrentFrame)
        {
            audioSamples_OverFlow = audioSamples_InTheCurrentFrame - audioSamples_UntilBufferIsFull;
            if (audioSamples_UntilBufferIsFull == audioSamples_InTheCurrentFrame)
            {
                LOG(LOG_INFO, name_thisMethod + "Buffer Exactly Full!");
                // Copy the audio samples from frame to the buffer
                rsHeader.unpackUDPpayloadToAudioBuffer(buffer, UDPpackDataRead + headerByteSize, audioSamples_WriteCounter);
            }
            else
            {               
                // TODO: this has to call a method with an overflow handling capabilities
                LOG(LOG_INFO, name_thisMethod +
                              "audioSamples_UntilBufferIsFull ["+to_string(audioSamples_UntilBufferIsFull) + "]"+
                              "audioSamples_InTheCurrentFrame [" + to_string(audioSamples_InTheCurrentFrame) + "]"+
                              "audioSamples_OverFlow [" + to_string(audioSamples_OverFlow) + "]");
                rsHeader.unpackUDPpayloadToAudioBuffer(buffer, UDPpackDataRead + headerByteSize, audioSamples_WriteCounter,
                    audioSamples_UntilBufferIsFull,nullptr/*TODO: handle the overflow here*/);
            }
        }
        else 
        {
            // Copy the audio samples from frame to the buffer
            rsHeader.unpackUDPpayloadToAudioBuffer(buffer, UDPpackDataRead + headerByteSize, audioSamples_WriteCounter);
            // Note: UDPpackDataRead + headerByteSize /* Offset/Skip the frame header to the samples*/
        }
        // TODO: a method to append to the begining of the buffer is needed

        // ++++ TODO


        
        audioSamples_WriteCounter += audioSamples_InTheCurrentFrame;
    }

    // +++++++++++ TODO: testing code begin
    

    ReaXstreamGUI* guiPtr = (ReaXstreamGUI*)this->getSet_ReaXstreamGUIpointer(nullptr);
    

        // +++++++++++ TODO: testing code end
    LOG(LOG_WARNING, name_thisMethod + "DONT't forget to take care of the pottential overflow");// TODO
}

void ReaXstreamAudioProcessor::computeAudiolevels(juce::AudioBuffer<float>& buffer)
{
    //Todo: consider a loop for more than 2 channels
    
    // Get the number of samples
    auto numSamplestoSkip = buffer.getNumSamples();
    // The deay calculateions based on the skipped number of samples
    rmsLevel_L.skip(numSamplestoSkip);
    rmsLevel_R.skip(numSamplestoSkip);
    maxLevel_L.skip(numSamplestoSkip);
    maxLevel_R.skip(numSamplestoSkip);
     
    // Compute the RMS values per channel 
    auto _rmsLevel_L = buffer.getRMSLevel(0, 0, buffer.getNumSamples());
    auto _rmsLevel_R = buffer.getRMSLevel(1, 0, buffer.getNumSamples());
    // Compute the Max values per channel
    auto _maxLevel_L = buffer.getMagnitude(0, 0, buffer.getNumSamples());
    auto _maxLevel_R = buffer.getMagnitude(1, 0, buffer.getNumSamples());

    // Generally the output should be in decibels 
    const auto __rmsLevel_L = juce::Decibels::gainToDecibels(_rmsLevel_L);
    const auto __rmsLevel_R = juce::Decibels::gainToDecibels(_rmsLevel_R);
    const auto __maxLevel_L = juce::Decibels::gainToDecibels(_maxLevel_L);
    const auto __maxLevel_R = juce::Decibels::gainToDecibels(_maxLevel_R);

    rmsLevel_L.skip(buffer.getNumSamples());
    rmsLevel_R.skip(buffer.getNumSamples());
    maxLevel_L.skip(buffer.getNumSamples());
    maxLevel_R.skip(buffer.getNumSamples());

    if (__rmsLevel_L < rmsLevel_L.getCurrentValue()) { rmsLevel_L.setTargetValue(__rmsLevel_L); }
    else { rmsLevel_L.setCurrentAndTargetValue(__rmsLevel_L);}

    if (__rmsLevel_R < rmsLevel_R.getCurrentValue()) { rmsLevel_R.setTargetValue(__rmsLevel_R); }
    else { rmsLevel_R.setCurrentAndTargetValue(__rmsLevel_R); }

    if (__maxLevel_L < maxLevel_L.getCurrentValue()) { maxLevel_L.setTargetValue(__maxLevel_L); }
    else { maxLevel_L.setCurrentAndTargetValue(__maxLevel_L); }

    if (__maxLevel_R < maxLevel_R.getCurrentValue()) { maxLevel_R.setTargetValue(__maxLevel_R); }
    else { maxLevel_R.setCurrentAndTargetValue(__maxLevel_R); }


}

float ReaXstreamAudioProcessor::getChannelRMS(int channel)
{
    jassert(channel == 0 | channel == 1);
    if (channel == 0) { return rmsLevel_L.getCurrentValue(); }
    if (channel == 1) { return rmsLevel_R.getCurrentValue(); }
}

float ReaXstreamAudioProcessor::getChannelMax(int channel)
{
    jassert(channel == 0 | channel == 1);
    if (channel == 0) { return maxLevel_L.getCurrentValue(); }
    if (channel == 1) { return maxLevel_R.getCurrentValue(); }
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

void ReaXstreamAudioProcessor::setEditorCreateState(bool editorCreatedIsTure)
{
    const std::string name_thisMethod = "[ReaXstreamAudioProcessor::setEditorCreateState(...)]:";// Prefix for loggin
    editorIsCreatedAndActiveState = editorCreatedIsTure;
    if (editorIsCreatedAndActiveState)
    {
        LOG(LOG_INFO, name_thisMethod + "The [Audio Processor] has been infromed that [Editor GUI] as been created and is active!");
    }
    else
    {
        LOG(LOG_INFO, name_thisMethod + "The [Audio Processor] has been infromed that [Editor GUI] as been destoryed and is not active!");
    }
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
