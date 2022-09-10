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

//=================================================================================
// This section implements the Classic ReaStream Implementation
const unsigned int headerByteCount = 47;// Byte size sum of the header properties
const unsigned int MUT = 1200+headerByteCount;// MUT (Maximum Unit Transmission) in bytes per UDP frame.
// The header contains 47 bytes and the audio data contains 1200 bytes.



// Classic frame default frame identifier
static const char default_packetID[4] = {'M','R','S','R'};

// Reastrema Classic frame class
class ReaStreamClassicFrame
{
public:
    // This is the frame itself
    char packetID[4] = { 0 };// 'MRSR' tag for every packet like an ID (4 bytes)
    unsigned int packetSize = 0; // size of the entire transmission packet (4 bytes)
    char interconnectID[32] = {};// Name of the stream (ie: default on the plugin) (32 bytes)
    uint8_t numAudioChannels = 0;// alternative unsigned chat; // the number of channels the plugin sends (1 byte)
    unsigned int audioSampleRate = 0;// the rate Frequency of the data (44100, 48000, ...) (4 bytes)
    unsigned short sampleByteSize = 0;// size of the following bytes to read. (2 bytes)
    //float audioBufferData[1200 / sizeof(float)] = {};

    struct ReaStreamClassicHeader_index
    {// Explicit indexing but also dynamically calculated in the constructor.
        // Problem is, they are useless because of the structure padding !!!!
        //public:
        unsigned int i_packetID = 0;
        unsigned int i_packetSize = 4;
        unsigned int i_interconnectID = 8;
        unsigned int i_numAudioChannels = 40;
        unsigned int i_audioSampleRate = 41;
        unsigned int i_sampleByteSize = 45;
        unsigned int i_audioBufferData = 47;
    }ind;


    unsigned long long packetIndex  = 0;// This inex is used for collision control and missing frame detection.

    // Internal frame buffer
    //unsigned char udpBuffer[MUT] = {};// void* <= void pointer is also an option

public:
    // Constructors
    ReaStreamClassicFrame();// Empty constructor/ can be also used to reset the frame
    ReaStreamClassicFrame
        (
            char const      in_packetID[4], 
            std::string     packetconnectionIdentifier,
            uint8_t         in_numAudioChannels,
            unsigned int    in_audioSampleRate
        );

    // This function calculates the idices dynamically
    void calculateMemIndices();

    // Packs the audio buffer into a ReaStream frame for UDP transmission
    // This function will segment the audio buffer into multiple Reastream frames each for a UDP packet
    void packNextAudioBufferInRSframe(juce::AudioBuffer<float>& buffer, char* UDPbuffer, int audioSampleBuffInd,int samplesToRead);

    // This function will unapck the header into ReaStream Frame
    void unpackUDPheaderToRSframe(char* UDP_frameHeader);

    // This function will unapck the payload into the Audio Buffer
    void unpackUDPpayloadToAudioBuffer(juce::AudioBuffer<float>& buffer, char* UDP_frameAudioData);

    // Print frame header info
    std::string printFrameHeader();

    // Check packet ID
    bool isValidPacketID();
};




//=================================================================================
// This is the classic reasteam frame
class ReaStreamFrame
{
    public:
        // Header and data buffer
        ReaStreamClassicFrame rsHeader;
        char UDPpackPayload[MUT]; // Byte buffer for protocol transmission
        char UDPpackDataRead[MUT];

    public:
        ReaStreamFrame();//Default Constructor 
        ~ReaStreamFrame();//Destructor

        void interleaveAudioBuffer(juce::AudioBuffer<float>& buffer, float* outputWriteInterleavedAudioBuffer);
        void interleaveAudioChannels(const float** inputReadChannels, float* outputWriteChannels, const int numChannels, const int numberAudioSamples);

};



