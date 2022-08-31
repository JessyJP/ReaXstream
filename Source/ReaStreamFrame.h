/*
  ==============================================================================

    This file contains the basic ReaStream Frame implementation.
    The implementation is exactly the same as the classic Reaper implementation
    from the Reaper Pluing ReaStream in https://www.reaper.fm/reaplugs/

    This class deals handling(i.e. packing and unpacking) the audio buffers into
    transmittalbe data/application frames. Therefore it's a type of Layer 5/6 
    OSI protocol. This class prepares the packets data to be encapsulated by a 
    level Layer 4 protocol for further processing.

    Author: JessyJP
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

static char packetID_ClassicReastreamPacket[4] = { 'M','R','S','R' };

// Set maximum transmit units for UDP connection
static const unsigned int mut = 1472;// MUT (Maximum Unit Transmission) in bytes per UDP frame

//TODO:rename this class
// This is the classic reasteam frame
class ReaStreamFrame
{
    public:
        char packetID[4];                   // 'MRSR' tag for every packet like an ID (4 bytes)
        unsigned int packetSize;            // size of the entire transmission packet (4 bytes)
        char packetLabel[32];               // Name of the stream (ie: default on the plugin) (32 bytes)
        unsigned __int8 numAudioChannels;   // alternative unsigned chat; // the number of channels the plugin sends (1 byte)
        unsigned int audioSampleRate;       // the rate Frequency of the data (44100, 48000, ...) (4 bytes)
        unsigned short sampleByteSize ;     // size of the following bytes to read. (2 bytes)
        float* dataAudioBuffer;             // start of the audio datas (variable get from "sampleByteSize")

        unsigned int headerByteCount;
        unsigned long long packetIndex;     // This inex is used for collision control and missing frame detection.
        float* zeroDataAudioBuffer;
        
        char* transmissionPacketByteBuffer;
    public:
        ReaStreamFrame();//Default Constructor 
        ~ReaStreamFrame();//Destructor

        void packAudioBufferToTransmissionPacket(juce::AudioBuffer<float>& buffer, unsigned int sampleRateFromAudioProcessor);
        void unpackTransmissionPackToAudioBuffer(juce::AudioBuffer<float>& buffer);

        void frameReset();

        float* reorderAufferBufferToMultichannelFrames(float* audioSampleBuffer);

        std::string printFrameHeader();
};



