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
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ComboBox> comboBox_directionOfConnection;
    std::unique_ptr<juce::ComboBox> comboBox_modeOfOperation;
    std::unique_ptr<juce::ComboBox> comboBox_transmissionProtocol;
    std::unique_ptr<juce::TextEditor> textEditor_ipUrlPort;
    std::unique_ptr<juce::TextEditor> textEditor_identifier;
    std::unique_ptr<juce::TextButton> button_apply;
    std::unique_ptr<juce::Label> lable_directionOfConnection;
    std::unique_ptr<juce::Label> label_modeOfOperation;
    std::unique_ptr<juce::Label> label_transmissionProtocolLabel;
    std::unique_ptr<juce::Label> label_ipaddres;
    std::unique_ptr<juce::Label> label_identifierLabel;
    std::unique_ptr<juce::HyperlinkButton> hyperlink_gitHub;
    std::unique_ptr<juce::Label> juce__label6;
    std::unique_ptr<juce::Label> juce__label7;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReaXstreamGUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
