#include "ReaXsteamSetup.h"

// Define Constructor 
ReaXsteamSetup::ReaXsteamSetup() 
{ 
	// Default values
	direction = DirectionOfConnection::HostServerTransmitter;
	mode = ModeOfOperation::ReaStreamClassic;
	ip = "localhost";//"broadcast"
	port = 58710;
	connectionLabel = "default";
	connectionSetupReady = false;
}


// Define Destructor
ReaXsteamSetup::~ReaXsteamSetup()
{

}

std::list<TransmissionProtocol> getAvailableProtocolByModeOfOperation(ModeOfOperation mode)
{
	std::list<TransmissionProtocol> availableProtocolsList(0);
	switch (mode)
	{
		case ModeOfOperation::ReaStreamClassic:// Uses the classic protocol
			//Wireless or Ethernet - Remote or Local Host
			availableProtocolsList.push_back(TransmissionProtocol::UDP);
			availableProtocolsList.push_back(TransmissionProtocol::TCP);
			availableProtocolsList.push_back(TransmissionProtocol::USB);
			break;
		case ModeOfOperation::ReaStreamMobile:// Uses reordered buffer in the addition to the indexing
			//Wireless, Ethernet or USB - Remote Mobile Host
			availableProtocolsList.push_back(TransmissionProtocol::UDP);
			availableProtocolsList.push_back(TransmissionProtocol::TCP);
			availableProtocolsList.push_back(TransmissionProtocol::USB);
			break;
		case ModeOfOperation::ReaInterConnect:
			//Shared Memory or Loopback - Local Host
			availableProtocolsList.push_back(TransmissionProtocol::SharedMemory);
			availableProtocolsList.push_back(TransmissionProtocol::UDP);
			availableProtocolsList.push_back(TransmissionProtocol::TCP);
			break;
	}


	return availableProtocolsList;
}