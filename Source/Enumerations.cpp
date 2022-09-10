/*
  ==============================================================================

    Properties.cpp
    Created: 4 Sep 2022 5:21:53am
    Author:  JessyJP

  ==============================================================================
*/

#include "Enumerations.h"

// =============================================================================================


// External functions

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

std::list<std::string> convertListOfTransmissionProtocolsToStringList(std::list<TransmissionProtocol> listOfProtocols)
{
	std::list<std::string> strList;

	for (std::list<TransmissionProtocol>::iterator it = listOfProtocols.begin(); it != listOfProtocols.end(); ++it)
	{
		// todo: use either loop	
	}

	for (const auto& protocol : listOfProtocols)
	{
		strList.push_back(convertEnum2String(protocol));
	}
	return strList;
}

ModeOfOperation convertModeOfOperationStringToEnum(std::string modeStr)
{
	if (modeStr.compare("ReaInterConnect")) { return ModeOfOperation::ReaInterConnect; }
	if (modeStr.compare("ReaStreamClassic")) { return ModeOfOperation::ReaStreamClassic; }
	if (modeStr.compare("ReaStreamMobile")) { return ModeOfOperation::ReaStreamMobile; }
}



// Conversion methods from enum to strings
std::string convertEnum2String(DirectionOfConnection direction)
{
	switch (direction)
	{
		case DirectionOfConnection::ClientReceiver:				return "ClientReceiver";
		case DirectionOfConnection::HostServerTransmitter:		return "HostServerTransmitter";
		default:												return "";
	}
}

std::string convertEnum2String(ModeOfOperation mode)
{
	switch (mode)
	{
		case ModeOfOperation::ReaInterConnect:		return "ReaInterConnect";
		case ModeOfOperation::ReaStreamClassic:		return "ReaStreamClassic";
		case ModeOfOperation::ReaStreamMobile:		return "ReaStreamMobile";
		default:									return "";
	}
}

std::string convertEnum2String(TransmissionProtocol protocol)
{
	switch (protocol)
	{
		case TransmissionProtocol::SharedMemory:	return "SharedMemory";
		case TransmissionProtocol::TCP:				return "TCP";
		case TransmissionProtocol::UDP:				return "UDP";
		case TransmissionProtocol::USB:				return "USB";
		default:									return "";
	}
}


// Methods to Validate if the input is a valid enumeration
bool isValidEnum(DirectionOfConnection in_enum)
{
	switch (in_enum)
	{
		case DirectionOfConnection::HostServerTransmitter:	return true;
		case DirectionOfConnection::ClientReceiver:			return true;
		default: return false;
	}
}

bool isValidEnum(ModeOfOperation in_enum)
{
	switch (in_enum)
	{
		case ModeOfOperation::ReaStreamClassic:		return true;
		case ModeOfOperation::ReaInterConnect:		return true;
		case ModeOfOperation::ReaStreamMobile:		return true;
		default: return false;
	}
}

extern bool isValidEnum(TransmissionProtocol in_enum)
{
	switch (in_enum)
	{
		case TransmissionProtocol::SharedMemory:	return true;
		case TransmissionProtocol::TCP:				return true;
		case TransmissionProtocol::UDP:				return true;
		case TransmissionProtocol::USB:				return true;
		default: return false;
	}
}

