/*
  ==============================================================================

	This file contains the the connection setup routines.

  ==============================================================================
*/

#pragma once

#include <string>
#include <list>
#include <iostream>

// This enumerations declares the basic direction mode operation
enum DirectionOfConnection { HostServerTransmitter, ClientReceiver };
// TODO: Maybe relabel them to make them shorter

// This enumeration declares the types connection modes
enum ModeOfOperation 
{
	ReaStreamClassic,
	ReaStreamMobile,/*ReaXstreamMobile*/
	ReaInterConnect/*ReaTransmit/ReaInterface*/ 
};

// This declares the available transmission protocol methods
enum TransmissionProtocol {
	UDP,
	TCP,
	SharedMemory,
	USB
};


static const char welcomeMessage[21] = "ReaXstream Starting!";

// Set maximum transmit units for UDP connection
static const unsigned int mut = 1472;// MUT (Maximum Unit Transmission) in bytes per UDP frame


class ReaXsteamSetup
{
	public: // Settings/Parameter/Properties
		DirectionOfConnection direction;
		ModeOfOperation mode;

		std::string ip;
		unsigned short port;
		std::string connectionLabel;

	public: // States
		bool connectionSetupReady;

	public:
		ReaXsteamSetup();// Constructor
		~ReaXsteamSetup();// Destructor
		
		//Get Connection protocols by modes
		std::list<TransmissionProtocol> getAvailableProtocolByModeOfOperation(ModeOfOperation mode);
		
};


