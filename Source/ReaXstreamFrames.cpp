#include "ReaXstreamFrames.h"
#include "PluginProcessor.h"

#include "Logger.h"

using namespace std;

ReaStreamFrame::ReaStreamFrame()
{
    packetIndex = 0;
    // Compute the header byte count
    headerByteCount = sizeof(rsHeader);
    rsH_ind.ind_packetID = 0;
    rsH_ind.ind_packetSize         = rsH_ind.ind_packetID         + sizeof(rsHeader.packetID);
    rsH_ind.ind_packetLabel        = rsH_ind.ind_packetSize       + sizeof(rsHeader.packetSize);
    rsH_ind.ind_numAudioChannels   = rsH_ind.ind_packetLabel      + sizeof(rsHeader.packetLabel);
    rsH_ind.ind_audioSampleRate    = rsH_ind.ind_numAudioChannels + sizeof(rsHeader.numAudioChannels);
    rsH_ind.ind_sampleByteSize     = rsH_ind.ind_audioSampleRate  + sizeof(rsHeader.audioSampleRate);
   

//    transmissionPacketByteBuffer = (char*)malloc(32768);//TODO: Put a limit somewhere in a variaable, don't hardcode
 //   for (int i = 0; i < sizeof(transmissionPacketByteBuffer); i++) { transmissionPacketByteBuffer[i] = 0; }

}


//RF::RF(std::string packLabel_str) 
//{
  //  packetLabel = packLabel_str.
//}

ReaStreamFrame::~ReaStreamFrame()
{

 //   free(transmissionPacketByteBuffer);
}

const char* ReaStreamFrame::getPacketLabel()
{
    const char label[32] = "default";
    return label;
}

void ReaStreamFrame::packAudioBufferToTransmissionPacket(juce::AudioBuffer<float>& buffer,unsigned int sampleRateFromAudioProcessor)
{
    // Decide on UDP segmentation
    unsigned short  numSamples = static_cast<unsigned short>(buffer.getNumSamples());
    uint8_t        numChannels = uint8_t(buffer.getNumChannels());
    int UDP_buff_Limit = 1200;// Bytes
    int offset = 0;
  //  ReaStreamClassicHeader rsHeader = { classicFramePacketID,0, getPacketLabel(), }
    // Make Header
    // Header identifier label
//    for (int c = 0; c < sizeof(packetID_ClassicReastreamPacket); c++) { rsHeader.packetID[c] = packetID_ClassicReastreamPacket[c]; }
//    rsHeader.packetLabel = getPacketLabel();
    rsHeader.audioSampleRate = sampleRateFromAudioProcessor;
     


    
    


    rsHeader.packetSize = (numSamples * numChannels * sizeof(float)) > (1200 + 47) ? (1200 + 47) :
    rsHeader.numAudioChannels = uint8_t(buffer.getNumChannels());
    
    rsHeader.sampleByteSize = rsHeader.numAudioChannels * numSamples * sizeof(float);

    // This copies the first [this->headerByteCount == 47 (usually)] bytes from the header
    int c = 0;
    memcpy(transmissionPacketByteBuffer + c, rsHeader.packetID, sizeof(rsHeader.packetID)); c += sizeof(rsHeader.packetID);
    memcpy(transmissionPacketByteBuffer + c, (char*) (&rsHeader.packetSize), sizeof(rsHeader.packetSize)); c += sizeof(rsHeader.packetSize);
    memcpy(transmissionPacketByteBuffer + c, rsHeader.packetLabel, sizeof(rsHeader.packetLabel)); c += sizeof(rsHeader.packetLabel);
    memcpy(transmissionPacketByteBuffer + c, (char*)(&rsHeader.numAudioChannels), sizeof(rsHeader.numAudioChannels)); c += sizeof(rsHeader.numAudioChannels);
    memcpy(transmissionPacketByteBuffer + c, (char*)(&rsHeader.audioSampleRate), sizeof(rsHeader.audioSampleRate)); c += sizeof(rsHeader.audioSampleRate);
    memcpy(transmissionPacketByteBuffer + c, (char*)(&rsHeader.sampleByteSize), sizeof(rsHeader.sampleByteSize)); c += sizeof(rsHeader.sampleByteSize);
    
        
    for (int channel = 0; channel < rsHeader.numAudioChannels; ++channel)
    {
        auto* channelData = buffer.getReadPointer(channel);
        memcpy(transmissionPacketByteBuffer + c, (char*)(&channelData), sizeof(channelData));
        c += sizeof(channelData);
        
    }
}

void ReaStreamFrame::unpackTransmissionPackToAudioBuffer(juce::AudioBuffer<float>& buffer)
{
    // This copies the first [this->headerByteCount == 47 (usually)] bytes from the header
    int c = 0;
    memcpy(rsHeader.packetID, transmissionPacketByteBuffer + c, sizeof(rsHeader.packetID));                   c += sizeof(rsHeader.packetID);
    memcpy(&rsHeader.packetSize, transmissionPacketByteBuffer + c, sizeof(rsHeader.packetSize));              c += sizeof(rsHeader.packetSize);
    memcpy(rsHeader.packetLabel, transmissionPacketByteBuffer + c, sizeof(rsHeader.packetLabel));             c += sizeof(rsHeader.packetLabel);
    memcpy(&rsHeader.numAudioChannels, transmissionPacketByteBuffer + c, sizeof(rsHeader.numAudioChannels));  c += sizeof(rsHeader.numAudioChannels);
    memcpy(&rsHeader.audioSampleRate, transmissionPacketByteBuffer + c, sizeof(rsHeader.audioSampleRate));    c += sizeof(rsHeader.audioSampleRate);
    memcpy(&rsHeader.sampleByteSize, transmissionPacketByteBuffer + c, sizeof(rsHeader.sampleByteSize));      c += sizeof(rsHeader.sampleByteSize);

    for (int channel = 0; channel < rsHeader.numAudioChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        memcpy(channelData, transmissionPacketByteBuffer+c, int(rsHeader.sampleByteSize/ rsHeader.numAudioChannels));
        c += sizeof(channelData);
        //TODO some flags were supposed to be set
    }

}




void ReaStreamFrame::interleaveAudioBuffer(juce::AudioBuffer<float>& buffer)
{
    const float** inputReadChannels             = buffer.getArrayOfReadPointers();
    float* outputWriteInterleavedAudioBuffer    = UDP_Remote_dataAudioBuffer;
    const int numberAudioChannels               = buffer.getNumChannels();
    const int numberAudioSamples                = buffer.getNumSamples();
    interleaveAudioChannels(inputReadChannels, outputWriteInterleavedAudioBuffer, numberAudioChannels, numberAudioSamples);
}

void ReaStreamFrame::interleaveAudioChannels(const float** inputReadChannels, float* outputWriteChannels, const int numChannels, const int numberAudioSamples)
{
    int p = 0;
    for (int s = 0; s < numberAudioSamples; s++)// loop over all samples s
    {
        for (int c = 0; c < numChannels; c++)
        {
            outputWriteChannels[p++] = inputReadChannels[c][s];
        }
    }

    if (p != numChannels * numberAudioSamples)
    {
        LOG(LOG_ERROR, "Buffer interleave error : p:" + to_string(p) + 
                     "] number of channels ["+to_string(numChannels) + 
                     "] number of audio samples ["+to_string(numberAudioSamples) + "]");
    }
}

std::string ReaStreamFrame::printFrameHeader()
{
    string sep = " ";
    string outputString = "";

    outputString += ("PacketID [") + string(rsHeader.packetID) + "] " + sep;
    outputString += ("Packet Size: [") + std::to_string(rsHeader.packetSize) + "] " + sep;
    outputString += ("Packet Label: [") + string(rsHeader.packetLabel) + "] " + sep;
    outputString += ("numAudioChannels: [") + std::to_string(rsHeader.numAudioChannels) + "] " + sep;
    outputString += ("audioSampleRate: [") + std::to_string(rsHeader.audioSampleRate) + "] " + sep;
    outputString += ("sampleByteSize: [") + std::to_string(rsHeader.sampleByteSize) + "] " + sep;

    LOG(LOG_FRAME(packetIndex), outputString);

    return outputString;
}