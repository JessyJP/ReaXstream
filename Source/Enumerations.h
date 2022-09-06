/*
  ==============================================================================

    Properties.h
    Created: 4 Sep 2022 5:21:53am
    Author:  JessyJP
	Description: This file contins state property definitions and static conver-
	sion methdods. 

  ==============================================================================
*/

#pragma once

#include <list>
#include <string>
#include <map>

//==============================================================================
// This enumerations declares the basic direction mode operation
enum DirectionOfConnection
{
	HostServerTransmitter=1,
	ClientReceiver=2
};

// This enumeration declares the types connection modes
enum ModeOfOperation
{
	ReaStreamClassic=1,
	ReaStreamMobile=2,/*ReaXstreamMobile*/
	ReaInterConnect=3/*ReaTransmit/ReaInterface*/
};

// This declares the available transmission protocol methods
enum TransmissionProtocol
{
	UDP=1,
	TCP=2,
	SharedMemory=3,
	USB=4
};

enum AudioStreamEncoding
{
	FLOAT32, FLOAT24, FLOAT16, FLOAT8,
	PCM32, PCM24, PCM16, PCM8
//	AINT32, AINT24, AINT16, AINT8
};
//==============================================================================

//Get Connection protocols by modes
extern std::list<TransmissionProtocol> getAvailableProtocolByModeOfOperation(ModeOfOperation mode);
extern std::list<std::string> convertListOfTransmissionProtocolsToStringList(std::list<TransmissionProtocol> listOfProtocols);
extern ModeOfOperation convertModeOfOperationStringToEnum(std::string modeStr);

// Casting allows us to convert form ENUM to INT <=and=> INT to ENUM 

// To convert to sting 

extern std::string convertEnum2String(DirectionOfConnection direction);
extern std::string convertEnum2String(ModeOfOperation mode );
extern std::string convertEnum2String(TransmissionProtocol protocol);

