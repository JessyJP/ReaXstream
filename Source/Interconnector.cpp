#include "Interconnector.h"
#include "PluginEditor.h"
#include "Logger.h"
#define LOG_INTERCONNECTOR LOG_INFO+std::string("[Interconnector]:")

// Define Constructor 
Interconnector::Interconnector() 
{ 
	// Default values
	direction = DirectionOfConnection::HostServerTransmitter;
	mode = ModeOfOperation::ReaStreamClassic;
	ip = "localhost";//"broadcast"
	port = 58710;
	connectionIdentifier = "default";
	encoding = AudioStreamEncoding::FLOAT32;
	// State/Action flags
	connectionEstablishedOK = false;
	resetInterConnection = false;
}


// Define Destructor
Interconnector::~Interconnector()
{

}

// State check function
bool Interconnector::isConnectionEstablishedOK()
{
	return this->connectionEstablishedOK;
}

// Set functions
void Interconnector::requestConnectionReset(bool initiateRequest)
{
	this->resetInterConnection = resetInterConnection || initiateRequest;
	LOG(LOG_INTERCONNECTOR,std::string("requestConnectionReset [") + (resetInterConnection?"true":"false") + "] ");
}

void Interconnector::setInterconnectorPropertiesFromGUI
		(DirectionOfConnection DoC, ModeOfOperation MoO, TransmissionProtocol TP)
{
	this->direction = DoC;
	this->mode = MoO;
	this->protocol = TP;
	requestConnectionReset(true);
	LOG(LOG_INTERCONNECTOR, 
			std::string("\n") +
			"DirectionOfConnection "	+ convertEnum2String(direction	) + "\n" +
			"ModeOfOperation: "			+ convertEnum2String(mode		) + "\n" +
			"TransmissionProtocol: "	+ convertEnum2String(protocol	) + "\n" +
			"IP: "						+ ip							  + "\n"
//			"Port: "					+ port							  + "\n"
		);
}

void Interconnector::setDirectionOfConnection(DirectionOfConnection DoC)
{
	this->direction = DoC;
	requestConnectionReset(true);
	LOG(LOG_INTERCONNECTOR, "DirectionOfConnection [" + convertEnum2String(direction) + "]");
}

void Interconnector::setModeOfOperation(ModeOfOperation MoO)
{
	this->mode = MoO;
	requestConnectionReset(true);
	LOG(LOG_INTERCONNECTOR, "ModeOfOperation: [" + convertEnum2String(mode) + "]");
}

void Interconnector::setTransmissionProtocol(TransmissionProtocol TP)
{
	this->protocol = TP;
	requestConnectionReset(true);
	LOG(LOG_INTERCONNECTOR, "TransmissionProtocol: [" + convertEnum2String(protocol) + "]");
}

void Interconnector::setIP(std::string newIP) 
{
	ip = newIP;
	LOG(LOG_INTERCONNECTOR, "IP: [" + ip + "]");
}

void Interconnector::setIdentifier(std::string newIdentifier)
{
	connectionIdentifier = newIdentifier;
	LOG(LOG_INTERCONNECTOR, "Identifier: [" + connectionIdentifier + "]");
}

// Setup function
void Interconnector::setupInterConnection()
{
	// Check the connection protperties in the interconnector:
	// 1. If they are not set then the connection is not ready,
	// then wait for the GUI to update the properties.
	// 2. If the properties are set, then validate the inputs.
	// Then again most if not all validation should be done on the GUI element callbacks.
	// 3. If the inputs are valid then try to establish a connection.
	// 4. If the connection is established set ==> connectionEstablishedOK = true;

	// 
}

bool Interconnector::getInterconnectionSelectionFromGUI()
{


	return true;
}

void Interconnector::createTransmitter()
{
	UDP;

	connectionEstablishedOK = true;
}

void Interconnector::createReciever()
{
	//	bindToPort 

}