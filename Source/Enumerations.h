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
	UDP=2,
	TCP=3,
	SharedMemory=1,
	USB=4
};

enum AudioStreamEncoding
{
	FLOAT32, FLOAT24, FLOAT16, FLOAT8,
	PCM32, PCM24, PCM16, PCM8,
	INT32, INT24, INT16, INT8
};
//==============================================================================

//Get Connection protocols by modes
static std::list<TransmissionProtocol> getAvailableProtocolByModeOfOperation(ModeOfOperation mode);
static std::list<std::string> convertListOfTransmissionProtocolsToStringList(std::list<TransmissionProtocol> listOfProtocols);
static ModeOfOperation convertModeOfOperationStringToEnum(std::string modeStr);

// Casting allows us to convert form ENUM to INT <=and=> INT to ENUM 

// To convert to sting 

static std::string convertEnum2String(DirectionOfConnection direction);
static std::string convertEnum2String(ModeOfOperation mode );
static std::string convertEnum2String(TransmissionProtocol protocol);

