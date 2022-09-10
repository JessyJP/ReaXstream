#include "ReaXstreamFrames.h"
#include "PluginProcessor.h"

#include "Logger.h"

using namespace std;

//=================================================================================

ReaStreamClassicFrame::ReaStreamClassicFrame(){}

ReaStreamClassicFrame::ReaStreamClassicFrame
    (
        char const      in_packetID[4],
        std::string     packetconnectionIdentifier,
        uint8_t         in_numAudioChannels,
        unsigned int    in_audioSampleRate
    )
{
    for (int c = 0; c < 4; c++) { packetID[c] = in_packetID[c]; }//Good old for loop
    for (int c = 0; (c < 31) && (c < packetconnectionIdentifier.length()); c++) 
    { interconnectID[c] = packetconnectionIdentifier[c]; }//Good old for loop
    // The last byte interconnectID[31] = 0; should already be zero from the constructor
    numAudioChannels = in_numAudioChannels;
    audioSampleRate = in_audioSampleRate;
}


void ReaStreamClassicFrame::calculateMemIndices()
{
    
    // Compute the header byte count
    ind.i_packetID              = 0;
    ind.i_packetSize            = ind.i_packetID + sizeof(packetID);
    ind.i_interconnectID        = ind.i_packetSize + sizeof(packetSize);
    ind.i_numAudioChannels      = ind.i_interconnectID + sizeof(interconnectID);
    ind.i_audioSampleRate       = ind.i_numAudioChannels + sizeof(numAudioChannels);
    ind.i_sampleByteSize        = ind.i_audioSampleRate + sizeof(audioSampleRate);
}

std::string ReaStreamClassicFrame::printFrameHeader()
{
    string sep = " ";
    string outputString = "";

    outputString += ("PacketID[") + string(packetID) + "] " + sep;
    outputString += ("InterconnectID[") + string(interconnectID) + "] " + sep;
    outputString += ("numAudioChannels[") + std::to_string(numAudioChannels) + "] " + sep;
    outputString += ("audioSampleRate[") + std::to_string(audioSampleRate) + "] " + sep;
    if (sampleByteSize > 0)
    {
        outputString += ("Packet Size[") + std::to_string(packetSize) + "] " + sep;
        outputString += ("sampleByteSize[") + std::to_string(sampleByteSize) + "] " + sep;
    }

    return outputString;
}

bool ReaStreamClassicFrame::isValidPacketID()
{
    for (int c = 0; c < 4; c++)
    {
        if (packetID[c] != default_packetID[c])
        {
            return false;
        }
    }
    return true;
}

void ReaStreamClassicFrame::packNextAudioBufferInRSframe(juce::AudioBuffer<float>& buffer, char* UDPbuffer, int audioSampleBuffInd, int samplesToRead)
{
    // Increment the packet index
    this->packetIndex++;
    // This copies the first [this->headerByteCount == 47 (usually)] bytes from the header
    sampleByteSize = numAudioChannels * samplesToRead * sizeof(float);
    packetSize = sampleByteSize + headerByteCount;
    // Change this to std::copy method
    int c = 0;// Counter
    memcpy(UDPbuffer + ind.i_packetID, packetID, sizeof(packetID)); c += sizeof(packetID);
    memcpy(UDPbuffer + c, (char*)(&packetSize), sizeof(packetSize)); c += sizeof(packetSize);
    memcpy(UDPbuffer + c, interconnectID, sizeof(interconnectID)); c += sizeof(interconnectID);
    memcpy(UDPbuffer + c, (char*)(&numAudioChannels), sizeof(numAudioChannels)); c += sizeof(numAudioChannels);
    memcpy(UDPbuffer + c, (char*)(&audioSampleRate), sizeof(audioSampleRate)); c += sizeof(audioSampleRate);
    memcpy(UDPbuffer + c, (char*)(&sampleByteSize), sizeof(sampleByteSize)); c += sizeof(sampleByteSize);

    for (int channel = 0; channel < numAudioChannels; ++channel)
    {
        const float* channelData = buffer.getReadPointer(channel, audioSampleBuffInd);
        memcpy(UDPbuffer + c, channelData, samplesToRead * sizeof(float));
        c += samplesToRead * sizeof(float);

    }
}

void ReaStreamClassicFrame::unpackUDPheaderToRSframe(char* UDP_frameHeader)
{
    // This copies the first [this->headerByteCount == 47 (usually)] bytes from the header
    int c = 0;
    memcpy(packetID, UDP_frameHeader + c, sizeof(packetID));                   c += sizeof(packetID);
    memcpy(&packetSize, UDP_frameHeader + c, sizeof(packetSize));              c += sizeof(packetSize);
    memcpy(interconnectID, UDP_frameHeader + c, sizeof(interconnectID));       c += sizeof(interconnectID);
    memcpy(&numAudioChannels, UDP_frameHeader + c, sizeof(numAudioChannels));  c += sizeof(numAudioChannels);
    memcpy(&audioSampleRate, UDP_frameHeader + c, sizeof(audioSampleRate));    c += sizeof(audioSampleRate);
    memcpy(&sampleByteSize, UDP_frameHeader + c, sizeof(sampleByteSize));      c += sizeof(sampleByteSize);
}

void ReaStreamClassicFrame::unpackUDPpayloadToAudioBuffer(juce::AudioBuffer<float>& buffer, char* UDP_frameAudioData)
{
    // The UPD payload has to be offset outside this method and here the begining of the data starts with the audio data
    int c = 0;
    for (int channel = 0; channel < numAudioChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        memcpy(channelData, UDP_frameAudioData + c, int(sampleByteSize / numAudioChannels) );
        c += sizeof(channelData);
        //TODO some flags were supposed to be set
    }

}

//=================================================================================

ReaStreamFrame::ReaStreamFrame()
{
 //   UDPpackPayload = (char*)malloc(MUT);
    for (int i = 0; i < sizeof(UDPpackPayload); i++) { UDPpackPayload[i] = 0; }
}

ReaStreamFrame::~ReaStreamFrame()
{
 //   free(UDPpackPayload);
}


void ReaStreamFrame::interleaveAudioBuffer(juce::AudioBuffer<float>& buffer,float* outputWriteInterleavedAudioBuffer)
{
    const float** inputReadChannels             = buffer.getArrayOfReadPointers();
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