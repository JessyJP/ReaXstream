#include "Interconnector.h"
#include "PluginEditor.h"

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
	// State/Action flags
	connectionEstablishedOK = false;
	resetInterConnection = false;
}


// Define Destructor
Interconnector::~Interconnector()
{

}

bool Interconnector::isConnectionEstablishedOK()
{
	return this->connectionEstablishedOK;
}

// Set functions
void Interconnector::requestConnectionReset(bool initiateRequest)
{
	this->resetInterConnection = resetInterConnection || initiateRequest;
}

void Interconnector::setInterconnectorPropertiesFromGUI(DirectionOfConnection DoC, ModeOfOperation MoO, TransmissionProtocol TP)
{
	this->direction = DoC;
	this->mode = MoO;
	this->protocol = TP;
}

void Interconnector::setDirectionOfConnection(DirectionOfConnection DoC)
{
	this->direction = DoC;
}

void Interconnector::setModeOfOperation(ModeOfOperation MoO)
{
	this->mode = MoO;
}

void Interconnector::setTransmissionProtocol(TransmissionProtocol TP)
{
	this->protocol = TP;
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