/*
  ==============================================================================

	This file contains the the connection setup routines.

  ==============================================================================
*/

#pragma once

#include <string>
#include <iostream>


#include "Enumerations.h"
#include <JuceHeader.h>
// 
//#include <juce_Socket.h>



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
		std::string connectionLabel;
		AudioStreamEncoding encoding;

	protected: // States
		bool connectionEstablishedOK;
		bool resetInterConnection;


	public:
		Interconnector();// Constructor
		~Interconnector();// Destructor
		

	public:
		bool isConnectionEstablishedOK();
		// This method allows to make a connection reset
		void requestConnectionReset(bool initiateRequest);
		// This is the method that updates the interconnector about the GUI changes in bulk.
		void setInterconnectorPropertiesFromGUI
			(	
				DirectionOfConnection DoC,
				ModeOfOperation MoO, 
				TransmissionProtocol TP
			);
		void setDirectionOfConnection(DirectionOfConnection DoC);
		void setModeOfOperation(ModeOfOperation MoO);
		void setTransmissionProtocol(TransmissionProtocol TP);

		// This function creates the connections based on the interconnector settings
		void setupInterConnection();


		// UDP connection
		bool enableBroadcasting;







		bool getInterconnectionSelectionFromGUI();
		

		void createTransmitter();
		void createReciever();
		juce::DatagramSocket* UDP;
		juce::StreamingSocket* TCP;

		
};