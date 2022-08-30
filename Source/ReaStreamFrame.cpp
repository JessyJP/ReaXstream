#include "ReaStreamFrame.h"

using namespace std;

ReaStreamFrame::ReaStreamFrame()
{
//    LOG(logINFO, string("Allocate: ") + string(sizeof(float)) + string("bytes"));
    dataAudioBuffer = (float *) malloc(mut *sizeof(float)); 
    zeroDataAudioBuffer = (float*)malloc(sizeof(dataAudioBuffer));
    for (auto i = 0; i < mut; i++) { dataAudioBuffer[i] = 0; }
    // start of the audio datas (variable get from "sampleByteSize")
    reset();
}

ReaStreamFrame::~ReaStreamFrame()
{
	free(dataAudioBuffer);
    free(zeroDataAudioBuffer);
}

float* ReaStreamFrame::reorderAufferBufferToMultichannelFrames(float* audioSampleBuffer)
{
	return nullptr;
}

void ReaStreamFrame::packAudioBufferToTransmissionPacket()
{
}

void ReaStreamFrame::packAudioBufferToTransmissionPacket(juce::AudioBuffer<float>& buffer)
{
    packetID[0] = 'M';
    packetID[1] = 'R';
    packetID[2] = 'S';
    packetID[3] = 'R';
    
    audioSampleRate = 48000;
    numAudioChannels = char(buffer.getNumChannels());
    unsigned short numSamples = static_cast<unsigned short>(buffer.getNumSamples());
    sampleByteSize = numAudioChannels * numSamples * sizeof(float);


    
    for (int channel = 0; channel < numAudioChannels; ++channel)
    {
        auto* channelData = buffer.getReadPointer(channel);
        //memccpy();
        
    }
}

void ReaStreamFrame::unpackTransmissionPackToAudioBuffer()
{
}


void ReaStreamFrame::reset()
{
    for (auto p = 0; p < 32; p++) { packetID[p] = 0;}


    for (auto c = 0; c < 32; c++) { packetLabel[c] = char(0); }
    // start of the audio datas (variable get from "sampleByteSize")

    packetSize = 0;            // size of the entire transmission packet (4 bytes)
    numAudioChannels = 0;   //alternative unsigned chat; // the number of channels the plugin sends (1 byte)
    audioSampleRate = 0;       // the rate Frequency of the data (44100, 48000, ...) (4 bytes)
    sampleByteSize = 0;            // size of the following bytes to read. (2 bytes)
    for (auto i = 0; i < mut; i++){dataAudioBuffer[i] = 0; }
    // start of the audio datas (variable get from "sampleByteSize")

    packetIndex++;     // This inex is used for collision control and missing frame detection.

}