/*
  ==============================================================================

    UnitTest.h
    Created: 11 Sep 2022 1:14:16am
    Author:  JessyJP

  ==============================================================================
*/

#pragma once

#define UNITTEST_ON // UNITTEST_OFF

#ifdef UNITTEST_ON

#include <cassert>
#include <iostream>
#include "Logger.h"


#define _CHECK_(call,output) // switched off state
#define _SHOW_RESULTS_(fname) // switched off state

#ifdef LOGGER_OFF

 //   #undef _CHECK_
    #define _CHECK_(call,output) UnitTestIndex++; \
     if (  call == output) { std::cout<< "Test ["<<UnitTestIndex<<"] = Passed!"; UnitTestPassed++;}\
    else{ std::cout<< "Test ["<<UnitTestIndex<<"] = Failed \n!"; std::cout <<"CALL: "<< #call << " [!=] OUTPUT: " << #output;}

    #define _SHOW_RESULTS_(fname) std::cout<<"#fname summary ["<<UnitTestPassed<<"/"<<UnitTestIndex<<"] Passed" ;

#endif LOGGER_OFF



#ifdef LOGGER_ON

 //   #undef _CHECK_
    #define _CHECK_(call,output, ... ) UnitTestIndex++; \
     if (  call == output) { LOG_UNIT_TEST( "Test [" + std::to_string(UnitTestIndex) + "] = Passed!"); UnitTestPassed++;}\
     else { LOG_UNIT_TEST("Test [" + std::to_string(UnitTestIndex) + "] = Failed \n!"); \
            LOG_UNIT_TEST("CALL: " +  #call + " [!=] OUTPUT: " + #output );\
            }//try{ LOG_UNIT_TEST( "-> INPUT: " + std::to_string(__VA_ARGS__); }  }

    #define _SHOW_RESULTS_(fname) LOG_UNIT_TEST("[ "+ #fname + " ] summary [" + std::to_string(UnitTestPassed) + "/" + std::to_string(UnitTestIndex) +  "] Passed") ;

#endif LOGGER_ON


#ifdef LOGGER_INTEGRATED
#endif LOGGER_INTEGRATED


#include "ReaXstreamGUI.h"

extern void UnitTest_Enumerations();
extern void UnitTest_ReaXstreamGUI(ReaXstreamGUI* guiPtr);

#endif UNITTEST_ON