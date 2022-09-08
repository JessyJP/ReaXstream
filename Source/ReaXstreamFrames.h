/*
  =================================================================================

    This file contains the basic transmission ReaXStream Frame types implementation.
    ReaStreamClassic - The implementation is exactly the same as the classic Reaper 
    implementation from the Reaper Pluing ReaStream in 
    https://www.reaper.fm/reaplugs/


    This class deals handling(i.e. packing and unpacking) the audio buffers into
    transmittalbe data/application frames. Therefore it's a type of Layer 5/6 
    OSI protocol. This class prepares the packets data to be encapsulated by a 
    level Layer 4 protocol for further processing.

    Author: JessyJP
  =================================================================================
*/

#pragma once

#include <JuceHeader.h>

#define classicFramePacketID 'MRSR'

//=================================================================================
// This section implements the Classic ReaStream Implementation
const unsigned int mut = 1247;// MUT (Maximum Unit Transmission) in bytes per UDP frame
// The header contains 47 bytes and the audio data contains 1200 bytes.
// The header
class ReaStreamClassicHeader
{
public:
    char packetID[4];// 'MRSR' tag for every packet like an ID (4 bytes)
    unsigned int packetSize         = 0; // size of the entire transmission packet (4 bytes)
    char* packetLabel = {};// Name of the stream (ie: default on the plugin) (32 bytes)
    uint8_t numAudioChannels        = 0;// alternative unsigned chat; // the number of channels the plugin sends (1 byte)
    unsigned int audioSampleRate    = 0;// the rate Frequency of the data (44100, 48000, ...) (4 bytes)
    unsigned short sampleByteSize   = 0;// size of the following bytes to read. (2 bytes)
};


struct ReaStreamClassicHeader_index
{// Explicit indexing but also dynamically calculated in the constructor.
    // Problem is, they are useless because of the structure padding !!!!
    //public:
    unsigned int ind_packetID               = 0;                   
    unsigned int ind_packetSize             = 4;           
    unsigned int ind_packetLabel            = 8;        
    unsigned int ind_numAudioChannels       = 40;           
    unsigned int ind_audioSampleRate        = 41;       
    unsigned int ind_sampleByteSize         = 45;
    unsigned int ind_audioBufferData        = 47;
};

//TODO:rename this class
// This is the classic reasteam frame
class ReaStreamFrame
{
    public:
        // Header and data buffer
        ReaStreamClassicHeader rsHeader;
        float UDP_Remote_dataAudioBuffer[300] = { };             // start of the audio datas (variable get from "sampleByteSize")
        float UDP_Local_dataAudioBuffer[8192] = { };             // start of the audio datas (variable get from "sampleByteSize")

        ReaStreamClassicHeader_index rsH_ind;
        unsigned int headerByteCount;       // Byte size sum of the header properties
        unsigned long long packetIndex;     // This inex is used for collision control and missing frame detection.
        
        char transmissionPacketByteBuffer[32768] = {}; // Byte buffer for protocol transmission
    public:
        ReaStreamFrame();//Default Constructor 
        ~ReaStreamFrame();//Destructor
        
        // Get function
        virtual const char* getPacketLabel();


        void packAudioBufferToTransmissionPacket(juce::AudioBuffer<float>& buffer, unsigned int sampleRateFromAudioProcessor);
        void unpackTransmissionPackToAudioBuffer(juce::AudioBuffer<float>& buffer);


        void interleaveAudioBuffer(juce::AudioBuffer<float>& buffer);
        void interleaveAudioChannels(const float** inputReadChannels, float* outputWriteChannels, const int numChannels, const int numberAudioSamples);

        std::string printFrameHeader();
};



