#include "Interconnector.h"

// Define Constructor 
Interconnector::Interconnector() 
{ 
	// Default values
	direction = DirectionOfConnection::HostServerTransmitter;
	mode = ModeOfOperation::ReaStreamClassic;
	ip = "localhost";//"broadcast"
	port = 58710;
	connectionLabel = "default";
	encoding = AudioStreamEncoding::FLOAT32;
	connectionSetupReady = false;
}


// Define Destructor
Interconnector::~Interconnector()
{

}

