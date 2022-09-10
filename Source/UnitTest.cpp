/*
  ==============================================================================

    UnitTest.cpp
    Created: 11 Sep 2022 12:46:02am
    Author:  JessyJP

  ==============================================================================
*/


#include "UnitTest.h"

#include "Logger.h"
#include "Enumerations.h"

    

void UnitTest_Enumerations()
{
    int UnitTestIndex = 0;
    int UnitTestPassed = 0;
    // _CHECK_: Method #1 in "Enumerations.h"
 //   extern std::list<TransmissionProtocol> getAvailableProtocolByModeOfOperation(ModeOfOperation mode);
    // _CHECK_: Method #2 in "Enumerations.h"
 //   extern std::list<std::string> convertListOfTransmissionProtocolsToStringList(std::list<TransmissionProtocol> listOfProtocols);
    // _CHECK_: Method #3 in "Enumerations.h"
 //   extern ModeOfOperation convertModeOfOperationStringToEnum(std::string modeStr);


    // _CHECK_: Method #4 in "Enumerations.h"
    _CHECK_( convertEnum2String(DirectionOfConnection::ClientReceiver) ,  std::string("ClientReceiver") );
    _CHECK_( convertEnum2String(DirectionOfConnection::HostServerTransmitter) , std::string("HostServerTransmitter") );
    for (auto input : { 0,3,4,5,6,7,8,9 })
    {
        _CHECK_(convertEnum2String(DirectionOfConnection(input)), std::string(""));
    }

    // _CHECK_: Method #5 in "Enumerations.h"
    _CHECK_(convertEnum2String(ModeOfOperation::ReaInterConnect), std::string("ReaInterConnect"));
    _CHECK_(convertEnum2String(ModeOfOperation::ReaStreamClassic), std::string("ReaStreamClassic"));
    _CHECK_(convertEnum2String(ModeOfOperation::ReaStreamMobile), std::string("ReaStreamMobile"));
    for (auto input : { 0,4,5,6,7,8,9 })
    {
        _CHECK_(convertEnum2String(ModeOfOperation(input)), std::string(""));
    }

    // _CHECK_: Method #6 in "Enumerations.h"
    _CHECK_(convertEnum2String(TransmissionProtocol::SharedMemory), std::string("SharedMemory"));
    _CHECK_(convertEnum2String(TransmissionProtocol::TCP), std::string("TCP"));
    _CHECK_(convertEnum2String(TransmissionProtocol::UDP), std::string("UDP"));
    _CHECK_(convertEnum2String(TransmissionProtocol::USB), std::string("USB"));
    for (auto input : { 0,5,6,7,8,9 })
    {
        _CHECK_(convertEnum2String(TransmissionProtocol(input)), std::string(""));
    }



    // _CHECK_: Method #7 in "Enumerations.h"
    _CHECK_(isValidEnum(DirectionOfConnection::ClientReceiver), true);
    _CHECK_(isValidEnum(DirectionOfConnection::HostServerTransmitter), true);
    for (auto input : { -3,-2,-1,0,3,4,5,6,7,8,9 })
    {
        _CHECK_(isValidEnum(DirectionOfConnection(input)), false);
    }

    // _CHECK_: Method #8 in "Enumerations.h"
    _CHECK_(isValidEnum(ModeOfOperation::ReaInterConnect), true);
    _CHECK_(isValidEnum(ModeOfOperation::ReaStreamClassic), true);
    _CHECK_(isValidEnum(ModeOfOperation::ReaStreamMobile), true);
    for (auto input : {-3,-2,-1,0,4,5,6,7,8,9 })
    {
        _CHECK_(isValidEnum(ModeOfOperation(input)), false , input);
    }

    // _CHECK_: Method #9 in "Enumerations.h"
    _CHECK_(isValidEnum(TransmissionProtocol::SharedMemory), true);
    _CHECK_(isValidEnum(TransmissionProtocol::TCP), true);
    _CHECK_(isValidEnum(TransmissionProtocol::UDP), true);
    _CHECK_(isValidEnum(TransmissionProtocol::USB), true);
    for (auto input : { -3,-2,-1,0 ,5,6,7,8,9 })
    {
        _CHECK_(isValidEnum(TransmissionProtocol(input)), false);
    }

    _SHOW_RESULTS_(UnitTest_Enumerations);
}



void UnitTest_ReaXstreamGUI(ReaXstreamGUI* guiPtr)
{
    guiPtr->setStateDirectionOfConnectionComboBox(DirectionOfConnection::ClientReceiver);// For testing
    guiPtr->setStateDirectionOfConnectionComboBox(DirectionOfConnection::HostServerTransmitter);// For testing
    guiPtr->setStateDirectionOfConnectionComboBox((DirectionOfConnection)0);// For testing
    guiPtr->setStateDirectionOfConnectionComboBox((DirectionOfConnection)6);// For testing
    guiPtr->setStateModeOfOperationComboBox(ModeOfOperation::ReaInterConnect);// For testing
    guiPtr->setStateModeOfOperationComboBox(ModeOfOperation::ReaStreamClassic);// For testing
    guiPtr->setStateModeOfOperationComboBox(ModeOfOperation::ReaStreamMobile);// For testing
    guiPtr->setStateModeOfOperationComboBox((ModeOfOperation)0);// For testing
    guiPtr->setStateModeOfOperationComboBox((ModeOfOperation)8);// For testing
    guiPtr->setStateTransmissionProtocolComboBox(TransmissionProtocol::SharedMemory);// For testing
    guiPtr->setStateTransmissionProtocolComboBox(TransmissionProtocol::TCP);// For testing
    guiPtr->setStateTransmissionProtocolComboBox(TransmissionProtocol::UDP);// For testing
    guiPtr->setStateTransmissionProtocolComboBox(TransmissionProtocol::USB);// For testing
    guiPtr->setStateTransmissionProtocolComboBox((TransmissionProtocol)0);// For testing
    guiPtr->setStateTransmissionProtocolComboBox((TransmissionProtocol)8);// For testing
}