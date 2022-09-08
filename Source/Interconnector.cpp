#include "Interconnector.h"
#include "PluginEditor.h"
#include "Logger.h"


#define LOG_INTERCONNECTOR LOG_INFO+std::string("[Interconnector]:")

// Define Constructor 
Interconnector::Interconnector() 
{ 
	// Default values
	direction = DirectionOfConnection(0);//DirectionOfConnection::HostServerTransmitter;
	mode = ModeOfOperation(0);//ModeOfOperation::ReaStreamClassic;
	protocol = TransmissionProtocol(0);//TransmissionProtocol ::UDP;
	ip = "localhost";//"broadcast"
	port = 58710;
	connectionIdentifier = "default";
	encoding = AudioStreamEncoding::FLOAT32;
	// State/Action flags
	connectionEstablishedOK = false;// By default the connection is not established
	resetInterConnection = false;// By default the connection does not need reset
	resetFrame = true;// By default the frame has to be reset and then on every interconnection reset
	currentEstablishedProtocol = TransmissionProtocol(0);
}

// Define Destructor
Interconnector::~Interconnector()
{
	closeCurrentConecction();
}


// State check function for established connection 
bool Interconnector::checkIsConnectionEstablishedOK()
{
	return connectionEstablishedOK;
}

// State check function
bool Interconnector::checkIsResetInterConnectionRequested()
{
	return resetInterConnection;
}


// Set methods
void Interconnector::requestConnectionReset(bool initiateRequest)
{
	// Request to reset the connection
	resetInterConnection = resetInterConnection || initiateRequest;
	// Also request to reset the data transmission frame
	resetFrame = resetFrame || resetInterConnection;
	LOG(LOG_INTERCONNECTOR,	std::string("requestConnectionReset [") + (resetInterConnection?"true":"false") + "] ");
	LOG(LOG_INTERCONNECTOR, std::string("requestFrameReset [")		+ (resetFrame ? "true" : "false") + "] ");
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

	// Validate the enumeration inputs
	if (!( (direction == HostServerTransmitter) || (direction == ClientReceiver) )) { return; }
	if (!( (mode == ReaStreamClassic) || (mode == ReaStreamMobile) || (mode == ReaInterConnect) )) { return; }
	if (!( (protocol == UDP) || (protocol == TCP) || (protocol == SharedMemory) || (protocol == USB) )) { return; }
		// TODO: Some input validation needs to be done here
		
	closeCurrentConecction();
	
		
	// Create a transmission connection adapter here
	if (direction == HostServerTransmitter)
	{
		switch (this->protocol)
		{
			case UDP:
			{
				udp = new juce::DatagramSocket();
				udp->waitUntilReady(false, -1);
				connectionEstablishedOK = true;
				LOG(LOG_INFO, " new UDP connection as [HostServerTransmitter]");
				break;
			}
			case TCP:
			{
				tcp = new juce::StreamingSocket();
				tcp->waitUntilReady(false, -1);
				connectionEstablishedOK = true;
				LOG(LOG_INFO, " new TCP connection as [HostServerTransmitter]");
				break;
			}
			case USB:
				break;
			case SharedMemory:
				break;
			default:
			{
				connectionEstablishedOK = false;
				break;
			}
		}
	}


	// If the connection was established ok 
	if (connectionEstablishedOK)
	{
		resetInterConnection = false;
		currentEstablishedProtocol = protocol;
	}
	// 
}

void Interconnector::closeCurrentConecction()
{
	// First destroy any current connections
	if	((currentEstablishedProtocol == UDP) ||
		 (currentEstablishedProtocol == TCP) ||
		 (currentEstablishedProtocol == USB) ||
		 (currentEstablishedProtocol == SharedMemory))
	{
		switch (currentEstablishedProtocol)
		{
			case UDP:
				udp->shutdown();
				delete(udp);
				LOG(LOG_INFO, " Close current UDP connection!");
				break;
			case TCP:

				break;
			case USB:

				break;
			case SharedMemory:

				break;
			default:
				break;

		}
		currentEstablishedProtocol = TransmissionProtocol(0);
	}

}




