#include "JuceHeader.h"
#include "Logger.h"

// Initialize plug-in logger
extern std::shared_ptr<juce::Logger>     logger		= std::shared_ptr<juce::Logger>    (juce::Logger::getCurrentLogger());
//extern std::unique_ptr<juce::FileLogger> fileLogger = std::unique_ptr<juce::FileLogger>(juce::FileLogger::createDateStampedLogger("logs", "mylog", ".log", welcomeMessage));