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
#include "Enumerations.h"
#include "PluginProcessor.h"

// The enumeration conversions can be done here or in the interconnector.
// It is more appropriate for all of that to be handled as early as possible,
// there fore enumeration and input validation can be handled at the scource.
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ReaXstreamGUI  : public juce::Component,
                       public juce::ComboBox::Listener,
                       public juce::Button::Listener
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
    //std::string getStateIpUrlPortTextEditor();
    std::string getStateIdentifierTextEditor();

    // Method to set the apptopirate transmission protocols for the corresponding mode
    void updateTransmissionProtocolsForModeSelection(ModeOfOperation mode);

    // Custom text change callback
    void textEditorTextChanged();//juce::TextEditor* textEditorThatHasChanged
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    // Set the plugin processor pointer reference.
    ReaXstreamAudioProcessor* rxAudioProcessor;
    bool flagChangeGUIstate;// This flag indicates a change in the GUI
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> label_LOGO;
    std::unique_ptr<juce::ComboBox> comboBox_directionOfConnection;
    std::unique_ptr<juce::ComboBox> comboBox_modeOfOperation;
    std::unique_ptr<juce::ComboBox> comboBox_transmissionProtocol;
    std::unique_ptr<juce::TextEditor> textEditor_ipUrlPort;
    std::unique_ptr<juce::TextEditor> textEditor_identifier;
    std::unique_ptr<juce::TextButton> button_apply;
    std::unique_ptr<juce::Label> label_directionOfConnection;
    std::unique_ptr<juce::Label> label_modeOfOperation;
    std::unique_ptr<juce::Label> label_transmissionProtocolLabel;
    std::unique_ptr<juce::Label> label_ipaddres;
    std::unique_ptr<juce::Label> label_identifierLabel;
    std::unique_ptr<juce::HyperlinkButton> hyperlink_gitHub;
    std::unique_ptr<juce::Label> juce__label6;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReaXstreamGUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

