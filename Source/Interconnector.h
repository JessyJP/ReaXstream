/*
  ==============================================================================

	This file contains the the connection setup routines.

  ==============================================================================
*/

#pragma once

#include <string>
#include <iostream>

#include "Enumerations.h"

//#include <juce_Socket.h>



class Interconnector
{
	public: // Settings/Parameter/Properties
		DirectionOfConnection direction;
		ModeOfOperation mode;

		std::string ip;
		unsigned short port;
		std::string connectionLabel;
		AudioStreamEncoding encoding;

	public: // States
		bool connectionSetupReady;



	public:
		Interconnector();// Constructor
		~Interconnector();// Destructor
		
		// UDP connection
		bool enableBroadcasting;

		
};