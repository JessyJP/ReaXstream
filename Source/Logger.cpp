#include "JuceHeader.h"
#include "Logger.h"

#ifdef LOGGER_ON
// ========================================
// Initialize plug-in logger
std::shared_ptr<juce::Logger> stdOutLogger					= std::shared_ptr<juce::Logger>(juce::Logger::getCurrentLogger());
//std::shared_ptr<juce::FileLogger> fileLogger				= std::shared_ptr<juce::FileLogger>(juce::FileLogger::createDateStampedLogger("logs", "mylog", ".log", welcomeMessage));

// ========================================
#endif LOGGER_ON


#ifdef LOGGER_INTEGRATED
// ========================================    
    std::shared_ptr<IntegratedLoggerGUI> myIntegratedLogger = std::shared_ptr<IntegratedLoggerGUI>(new IntegratedLoggerGUI());


    // Window class - I need it here only once so pasted direcl from forum
    // The logger needs a new window. No need to mess with the existing window.
    class IntegratedLoggerGUI::BasicWindow : public juce::DocumentWindow
    {
        private:
            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BasicWindow)

        public:
            BasicWindow(const juce::String& name, juce::Colour backgroundColour, int buttonsNeeded)
                : DocumentWindow(name, backgroundColour, buttonsNeeded)
            {
            }

            void closeButtonPressed() override
            {
                delete this;
            }
    };



    IntegratedLoggerGUI::IntegratedLoggerGUI()
    {
        
        logGUI = std::unique_ptr<DiagnosticWindowGUI>(new DiagnosticWindowGUI());
    //    logGUI = new DiagnosticWindowGUI();

        return;
    	loggerWindow = std::unique_ptr<BasicWindow>( new BasicWindow("Integreated Logger", juce::Colours::grey, juce::DocumentWindow::allButtons) );
    //    loggerWindow = new BasicWindow("Integreated Logger", juce::Colours::grey, juce::DocumentWindow::allButtons);
	    loggerWindow->setUsingNativeTitleBar(true);
    //	loggerWindow->centreWithSize(basicWindow->getWidth(), basicWindow->getHeight());
        loggerWindow->setContentOwned(logGUI.get(), true);
        loggerWindow->setVisible(true);

        

        testWindow = std::unique_ptr<juce::TopLevelWindow>(new juce::TopLevelWindow("Logger sub-window", false) );
    //    testWindow = new juce::TopLevelWindow("Logger sub-window", false);
       testWindow->setSize(1000, 500);
    //   testWindow->setOpaque(false);
    //    testWindow->addToDesktop(ComponentPeer::windowHasTitleBar | ComponentPeer::windowHasCloseButton, interface->getPeer()->getNativeHandle());
        testWindow->setVisible(true);

        enabled = true;
    }

    IntegratedLoggerGUI::~IntegratedLoggerGUI()
    {
        if (enabled)
        {
//            delete(logGUI);
//            delete(testWindow);
//            delete(loggerWindow);
        }
    }

    void IntegratedLoggerGUI::outputDebugString(const juce::String& text)
    {
	    // Well, this is effectively a wrapper for the loriginal logger. In order to keep that functionality. 
	    stdOutLogger->outputDebugString(text);
	    // Now the same message is sent to the interal gui stream
        if (enabled)
        {
            logGUI->logMessage(text);
        }
    }

// ========================================
#endif LOGGER_INTEGRATED