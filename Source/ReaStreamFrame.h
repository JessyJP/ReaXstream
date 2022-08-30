/*
  ==============================================================================

    This file contains the basic ReaStream Frame implementation.
    The implementation is exactly the same as the classic Reaper implementation
    from the Reaper Pluing ReaStream in https://www.reaper.fm/reaplugs/

  ==============================================================================
*/

#pragma once
// This is the classic reasteam frame
class ReaStreamFrame
{
public:
    char packetID[4] = {0, 0, 0, 0};            // 'MRSR' tag for every packet like an ID (4 bytes)
        unsigned int packetSize = 0;            // size of the entire transmission packet (4 bytes)
        char packetLabel[32] = "defeault";      // Name of the stream (ie: default on the plugin) (32 bytes)
        unsigned __int8 numAudioChannels = 0;   //alternative unsigned chat; // the number of channels the plugin sends (1 byte)
        unsigned int audioSampleRate = 0;       // the rate Frequency of the data (44100, 48000, ...) (4 bytes)
        unsigned sampleByteSize = 0;            // size of the following bytes to read. (2 bytes)
        float* dataAudioBuffer;                 // start of the audio datas (variable get from "sampleByteSize")

        unsigned long long packetIndex = 0;     // This inex is used for collision control and missing frame detection.
   
    public:
        ReaStreamFrame();//Default Constructor 
        ~ReaStreamFrame();//Destructor

        float* reorderAufferBufferToMultichannelFrames(float* audioSampleBuffer);

        void packAudioBufferToTransmissionPacket();
        void unpackTransmissionPackToAudioBuffer();
};

