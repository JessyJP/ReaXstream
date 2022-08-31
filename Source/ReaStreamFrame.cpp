#include "ReaStreamFrame.h"
#include "PluginProcessor.h"

#include "Logger.h"

using namespace std;

ReaStreamFrame::ReaStreamFrame()
{
    packetIndex = 0;
    // Compute the header byte count
    headerByteCount = sizeof(packetID) + sizeof(packetSize) + sizeof(packetLabel) + 
                      sizeof(numAudioChannels) + sizeof(audioSampleRate) + sizeof(sampleByteSize);

    dataAudioBuffer = (float *) malloc(mut *sizeof(float)); 
    zeroDataAudioBuffer = (float*)malloc(sizeof(dataAudioBuffer));
    for (auto i = 0; i < mut; i++) { dataAudioBuffer[i] = 0; }

    transmissionPacketByteBuffer = (char*)malloc(mut*2);
    for (auto i = 0; i < mut*2; i++) { transmissionPacketByteBuffer[i] = 0; }

    // start of the audio datas (variable get from "sampleByteSize")
    frameReset();
}

ReaStreamFrame::~ReaStreamFrame()
{
	free(dataAudioBuffer);
    free(zeroDataAudioBuffer);
    free(transmissionPacketByteBuffer);
}


void ReaStreamFrame::packAudioBufferToTransmissionPacket(juce::AudioBuffer<float>& buffer,unsigned int sampleRateFromAudioProcessor)
{
    // Make Header
    // Header identifier label
    memcpy(packetID, packetID_ClassicReastreamPacket, sizeof(packetID));
    // Header Audio Sample
    audioSampleRate = sampleRateFromAudioProcessor;
    numAudioChannels = uint8_t(buffer.getNumChannels());
    unsigned short numSamples = static_cast<unsigned short>(buffer.getNumSamples());
    sampleByteSize = numAudioChannels * numSamples * sizeof(float);

    // This copies the first [this->headerByteCount == 47 (usually)] bytes from the header
    int c = 0;
    memcpy(transmissionPacketByteBuffer + c, packetID, sizeof(packetID)); c += sizeof(packetID);
    memcpy(transmissionPacketByteBuffer + c, (char*) (&packetSize), sizeof(packetSize)); c += sizeof(packetSize);
    memcpy(transmissionPacketByteBuffer + c, packetLabel, sizeof(packetLabel)); c += sizeof(packetLabel);
    memcpy(transmissionPacketByteBuffer + c, (char*)(&numAudioChannels), sizeof(numAudioChannels)); c += sizeof(numAudioChannels);
    memcpy(transmissionPacketByteBuffer + c, (char*)(&audioSampleRate), sizeof(audioSampleRate)); c += sizeof(audioSampleRate);
    memcpy(transmissionPacketByteBuffer + c, (char*)(&sampleByteSize), sizeof(sampleByteSize)); c += sizeof(sampleByteSize);
    
        
    for (int channel = 0; channel < numAudioChannels; ++channel)
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
    memcpy(packetID, transmissionPacketByteBuffer + c, sizeof(packetID));                   c += sizeof(packetID);
    memcpy(&packetSize, transmissionPacketByteBuffer + c, sizeof(packetSize));              c += sizeof(packetSize);
    memcpy(packetLabel, transmissionPacketByteBuffer + c, sizeof(packetLabel));             c += sizeof(packetLabel);
    memcpy(&numAudioChannels, transmissionPacketByteBuffer + c, sizeof(numAudioChannels));  c += sizeof(numAudioChannels);
    memcpy(&audioSampleRate, transmissionPacketByteBuffer + c, sizeof(audioSampleRate));    c += sizeof(audioSampleRate);
    memcpy(&sampleByteSize, transmissionPacketByteBuffer + c, sizeof(sampleByteSize));      c += sizeof(sampleByteSize);

    for (int channel = 0; channel < numAudioChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        memcpy(channelData, transmissionPacketByteBuffer+c, int(sampleByteSize/ numAudioChannels));
        c += sizeof(channelData);
        //TODO some flags were supposed to be set
    }

}


void ReaStreamFrame::frameReset()
{
    for (auto p = 0; p < 4; p++) { packetID[p] = 0;}
    packetSize = 0;            // size of the entire transmission packet (4 bytes)
    for (auto c = 0; c < 32; c++) { packetLabel[c] = char(0); }
    // start of the audio datas (variable get from "sampleByteSize")
    numAudioChannels = 0;   //alternative unsigned chat; // the number of channels the plugin sends (1 byte)
    audioSampleRate = 0;       // the rate Frequency of the data (44100, 48000, ...) (4 bytes)
    sampleByteSize = 0;            // size of the following bytes to read. (2 bytes)
    for (auto i = 0; i < mut; i++){dataAudioBuffer[i] = 0; }
    // start of the audio datas (variable get from "sampleByteSize")

    packetIndex++;     // This inex is used for collision control and missing frame detection.

}

float* ReaStreamFrame::reorderAufferBufferToMultichannelFrames(float* audioSampleBuffer)
{
    return nullptr;
    //TODO:finish this function
}

std::string ReaStreamFrame::printFrameHeader()
{
    char* sep = " ";
    string outputString = "";

    outputString += ("PacketID [") + string(packetID) + "] " + sep;
    outputString += ("Packet Size: [") + std::to_string(packetSize) + "] " + sep;
    outputString += ("Packet Label: [") + string(packetLabel) + "] " + sep;
    outputString += ("numAudioChannels: [") + std::to_string(numAudioChannels) + "] " + sep;
    outputString += ("audioSampleRate: [") + std::to_string(audioSampleRate) + "] " + sep;
    outputString += ("sampleByteSize: [") + std::to_string(sampleByteSize) + "] " + sep;

    LOG(LOG_FRAME(packetIndex), outputString);

    return outputString;
}