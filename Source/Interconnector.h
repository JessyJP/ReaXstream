/*
  ==============================================================================

	This file contains the the connection setup routines.

  ==============================================================================
*/

#pragma once

#include <string>
#include <iostream>
#include <JuceHeader.h>
#include "Enumerations.h"


// Inteconnection Class which acts as protocol adapter/gateway/pipeline
class Interconnector
{
	protected: // Settings/Parameter/Properties
		// These are the main 3 properties
		DirectionOfConnection direction;
		ModeOfOperation mode;
		TransmissionProtocol protocol;

		// These properties involve the specific protocols
		std::string ip;
		unsigned short port;
		std::string connectionIdentifier;
		int numberOfChannels;// TODO: this has to update and indicate change in the number of channels
		AudioStreamEncoding encoding;

	protected: // States
		bool connectionEstablishedOK;
		bool resetInterConnection;
		bool resetFrame;
		TransmissionProtocol currentEstablishedProtocol;

		// UDP connection
		juce::DatagramSocket* udp;
		juce::StreamingSocket* tcp;
//			SharedMemory = 3,
//			USB = 4


		// Generally it refers to UDP but could work in tandem for the other protocols
		bool enableBroadcasting;



	public:
		Interconnector();// Constructor
		~Interconnector();// Destructor
		

	public:
		// State check function for established connection 
		bool checkIsConnectionEstablishedOK();
		bool checkIsResetInterConnectionRequested();

		// This method allows to make a connection reset
		void requestConnectionReset(bool initiateRequest);
		// This is the method that updates the interconnector about the GUI changes in bulk.
		void setInterconnectorPropertiesFromGUI
			(	
				DirectionOfConnection DoC,
				ModeOfOperation MoO, 
				TransmissionProtocol TP
			);
		// Individual set methods
		void setDirectionOfConnection(DirectionOfConnection DoC);
		void setModeOfOperation(ModeOfOperation MoO);
		void setTransmissionProtocol(TransmissionProtocol TP);
		void setIP(std::string newIP);
		void setIdentifier(std::string newIdentifier);

		// This function creates the connections based on the interconnector settings
		void setupInterConnection();
		void closeCurrentConecction();
		
};