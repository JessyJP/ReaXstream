/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Enumerations.h"
// The enumeration conversions can be done here or in the interconnector.
// It is more appropriate for all of that to be handled as early as possible,
// there fore enumeration and input validation can be handled at the scource.


// Level meter components
//#include "../Submodules/sound_meter/meter/sd_MetersComponent.h"
//#include "jucetice_HighQualityMeter.h"
#include "..\Submodules\level-meter-demo\Source\Component\HorizontalMeter.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ReaXstreamGUI  : public juce::Component,
                       public juce::ComboBox::Listener
{
public:
    //==============================================================================
    ReaXstreamGUI ();
    ~ReaXstreamGUI() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    void setReaXstreamAudioProcessorP(ReaXstreamAudioProcessor* rxAudioProcessorP_in);
    // Check the GUI state change check variable
    bool checkGUIstateChanged();

    // GUI elements get state methods
    DirectionOfConnection   getStateDirectionOfConnectionComboBox();
    ModeOfOperation         getStateModeOfOperationComboBox();
    TransmissionProtocol    getStateTransmissionProtocolComboBox();
    std::string             getStateIpUrlPortTextEditor_IPURL();
    int                     getStateIpUrlPortTextEditor_port();
    std::string             getStateIdentifierTextEditor();

    // GUI elements set state methods
    void setStateDirectionOfConnectionComboBox(DirectionOfConnection  in_DoC);
    void setStateModeOfOperationComboBox(ModeOfOperation in_MoO);
    void setStateTransmissionProtocolComboBox(TransmissionProtocol in_TP);
    void setStateIpUrlPortTextEditor_IPURL(std::string in_ipOrUrl);//IP/URL_PORT v.1: ip/url only
    void setStateIpUrlPortTextEditor_port(unsigned short in_port);//IP/URL_PORT v.2: port only
    void setStateIpUrlPortTextEditor(std::string in_ipOrUrlPort);//IP/URL_PORT v.3: ip/url & port as one
    void setStateIpUrlPortTextEditor(std::string in_ipOrUrk, unsigned short in_port);//IP/URL_PORT v.4: ip/url & port
    void setStateIdentifierTextEditor(std::string in_identifier);
    // Set audio levels and repaint
    void setAudioLevelsAndRepaint(int channel, float level);


    // Method to set the apptopirate transmission protocols for the corresponding mode
    void updateTransmissionProtocolsForModeSelection(ModeOfOperation mode);

    // Custom text change callback
    class TextEditListner_Class : public juce::TextEditor::Listener
    {// TODO FINISH THIS CLASS Or decide on the method for input validation
        void* parent;// Cast to "ReaXstreamGUI"
        public:
            TextEditListner_Class(void* pointer);// Lazy do declare
            void textEditorTextChanged(juce::TextEditor* textEditorThatHasChanged);

    };


    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    // Default port
    int defaultPort = 0;// This has to be initialized

    // Set the plugin processor pointer reference.
    ReaXstreamAudioProcessor* rxAudioProcessor;
    bool flagChangeGUIstate;// This flag indicates a change in the GUI

  //  std::unique_ptr<sd::SoundMeter::MetersComponent> level_meter;
    std::unique_ptr<Gui::HorizontalMeter> level_meter_L;
    std::unique_ptr<Gui::HorizontalMeter> level_meter_R;


    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> label_LOGO;
    std::unique_ptr<juce::ComboBox> comboBox_directionOfConnection;
    std::unique_ptr<juce::ComboBox> comboBox_modeOfOperation;
    std::unique_ptr<juce::ComboBox> comboBox_transmissionProtocol;
    std::unique_ptr<juce::TextEditor> textEditor_ipUrlPort;
    std::unique_ptr<juce::TextEditor> textEditor_identifier;
    std::unique_ptr<juce::Label> label_directionOfConnection;
    std::unique_ptr<juce::Label> label_modeOfOperation;
    std::unique_ptr<juce::Label> label_transmissionProtocolLabel;
    std::unique_ptr<juce::Label> label_ipaddres;
    std::unique_ptr<juce::Label> label_identifierLabel;
    std::unique_ptr<juce::HyperlinkButton> hyperlink_gitHub;
    std::unique_ptr<juce::Label> label_dbLevelRMS_L;
    std::unique_ptr<juce::Label> label_dbLevelRMS_R;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReaXstreamGUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

