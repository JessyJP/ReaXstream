//#pragma once

//static const char welcomeMessage[21] = "ReaXstream Starting!";
#define welcomeMessage "ReaXstream Starting!"

// The output types
#define logINFO         "ReaXstream [INFO]:  "
#define logDEBUG        "ReaXstream [DEBUG]:  "
#define logWARNING      "ReaXstream [WARNING]:  "
#define logERROR        "ReaXstream [ERROR]:  "

// Logger Switch
#define LOGGER_ON 

#ifdef LOGGER_ON
extern std::shared_ptr<juce::Logger>     logger;
extern std::unique_ptr<juce::FileLogger> fileLogger;
// Logger function
#define LOG(DTYPE,MSG) logger->outputDebugString( std::string(DTYPE) + std::string(MSG) );//Shorthand

#endif LOGGER_ON

#ifdef LOGGER_OFF

//Empty logger function
#define LOG(DTYPE,MSG)

#endif LOGGER_OFF