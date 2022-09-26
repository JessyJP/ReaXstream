#pragma once

//#ifndef LOGGER_H
//#define LOGGER_H
	

//static const char LoggerWelcomeMessage[21] = "ReaXstream Starting!";
#define LoggerWelcomeMessage  "ReaXstream Starting!"

// The output types
#define LOG_INFO        "ReaXstream |INFO|:"
#define LOG_GUI			"ReaXstream |GUI|:"
#define LOG_DEBUG       "ReaXstream |DEBUG]:"
#define LOG_WARNING     "ReaXstream |WARNING|:"
#define LOG_ERROR       "ReaXstream |ERROR|:"
// More specialized logging options
#define LOG_FRAME(name_thisMethod,x)  std::string("ReaXstream | Frame[") + std::to_string(x) + "][" + name_thisMethod

// Logger selection Switch. ON/OFF/Itegrated
// LOGGER_OFF / LOGGER_ON / LOGGER_INTEGRATED
#define LOGGER_OFF

//#endif LOGGER_H


#ifdef LOGGER_OFF

	//Empty logger function
	#define LOG(DTYPE,MSG)
	#define LOG_UNIT_TEST(str)
	#define GUI_WINDOW_LOG

#endif LOGGER_OFF

#ifdef LOGGER_ON

	#include <JuceHeader.h>
	extern std::shared_ptr<juce::Logger> stdOutLogger;
	extern std::shared_ptr<juce::FileLogger> fileLogger;

	// Logger function
	#define LOG(DTYPE,MSG) stdOutLogger->outputDebugString( std::string(DTYPE) + std::string(MSG) );fileLogger->logMessage(juce::String(DTYPE) + juce::String(MSG)); //Shorthand
	#define LOG_UNIT_TEST( str ) stdOutLogger->outputDebugString( std::string("") + str);//Shorthand
	#define GUI_WINDOW_LOG

#endif LOGGER_ON


#ifdef LOGGER_INTEGRATED
	#define LOGGER_ON
	// The debuger can be integrated into the app
	#include <JuceHeader.h>
	#include "DiagnosticWindowGUI.h"



	class IntegratedLoggerGUI
	{
		public :
			class BasicWindow; // Forward declaration for the basic window class

		public:

			IntegratedLoggerGUI();
			~IntegratedLoggerGUI();
			// It's not inherited so it's not overwritten. There is not reason to inherit in fact.
	//		static void JUCE_CALLTYPE 	outputDebugString(const juce::String& text);
			void outputDebugString(const juce::String& text);

			std::unique_ptr<BasicWindow> loggerWindow;
			std::unique_ptr<DiagnosticWindowGUI> logGUI;
			std::unique_ptr<juce::TopLevelWindow> testWindow;


			bool enabled = false;

};

	#include <JuceHeader.h>
	extern std::shared_ptr<juce::Logger> stdOutLogger;
	extern std::shared_ptr<juce::FileLogger> fileLogger;
	extern std::shared_ptr<IntegratedLoggerGUI> myIntegratedLogger;

	// Logger function
	#define LOG(DTYPE,MSG) myIntegratedLogger->outputDebugString( std::string(DTYPE) + std::string(MSG) );//Shorthand
	#define LOG_UNIT_TEST( str ) myIntegratedLogger->outputDebugString( std::string("") + str);//Shorthand

	// This is the GUI insetion 
//	#define GUI_WINDOW_LOG   \
//    logGUIwin = std::unique_ptr<juce::DocumentWindow>(new juce::DocumentWindow("Integreated Logger", juce::Colours::grey, juce::DocumentWindow::allButtons));


#endif LOGGER_INTEGRATED

