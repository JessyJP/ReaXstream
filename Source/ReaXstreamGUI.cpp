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

//[Headers] You can add your own extra header files here...
#include "Logger.h"
//[/Headers]

#include "ReaXstreamGUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ReaXstreamGUI::ReaXstreamGUI ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    flagChangeGUIstate = true;
    //[/Constructor_pre]

    comboBox_directionOfConnection.reset (new juce::ComboBox ("directionOfConnectionComboBox"));
    addAndMakeVisible (comboBox_directionOfConnection.get());
    comboBox_directionOfConnection->setEditableText (false);
    comboBox_directionOfConnection->setJustificationType (juce::Justification::centredLeft);
    comboBox_directionOfConnection->setTextWhenNothingSelected (juce::String());
    comboBox_directionOfConnection->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox_directionOfConnection->addItem (TRANS("Host Server Transmitter"), 1);
    comboBox_directionOfConnection->addSeparator();
    comboBox_directionOfConnection->addItem (TRANS("Client Receiver"), 2);
    comboBox_directionOfConnection->addListener (this);

    comboBox_directionOfConnection->setBounds (264, 49, 280, 32);

    comboBox_modeOfOperation.reset (new juce::ComboBox ("modeOfOperationComboBox"));
    addAndMakeVisible (comboBox_modeOfOperation.get());
    comboBox_modeOfOperation->setEditableText (false);
    comboBox_modeOfOperation->setJustificationType (juce::Justification::centredLeft);
    comboBox_modeOfOperation->setTextWhenNothingSelected (juce::String());
    comboBox_modeOfOperation->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox_modeOfOperation->addItem (TRANS("ReaStreamClassic"), 1);
    comboBox_modeOfOperation->addSeparator();
    comboBox_modeOfOperation->addItem (TRANS("ReaStreamMobile"), 2);
    comboBox_modeOfOperation->addSeparator();
    comboBox_modeOfOperation->addItem (TRANS("ReaInterConnect"), 3);
    comboBox_modeOfOperation->addListener (this);

    comboBox_modeOfOperation->setBounds (264, 121, 280, 32);

    comboBox_transmissionProtocol.reset (new juce::ComboBox ("transmissionProtocolComboBox"));
    addAndMakeVisible (comboBox_transmissionProtocol.get());
    comboBox_transmissionProtocol->setEditableText (false);
    comboBox_transmissionProtocol->setJustificationType (juce::Justification::centredLeft);
    comboBox_transmissionProtocol->setTextWhenNothingSelected (juce::String());
    comboBox_transmissionProtocol->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox_transmissionProtocol->addItem (TRANS("UDP"), 1);
    comboBox_transmissionProtocol->addSeparator();
    comboBox_transmissionProtocol->addItem (TRANS("TCP"), 2);
    comboBox_transmissionProtocol->addSeparator();
    comboBox_transmissionProtocol->addItem (TRANS("SharedMemory"), 3);
    comboBox_transmissionProtocol->addSeparator();
    comboBox_transmissionProtocol->addItem (TRANS("USB"), 4);
    comboBox_transmissionProtocol->addListener (this);

    comboBox_transmissionProtocol->setBounds (264, 192, 280, 32);

    textEditor_ipUrlPort.reset (new juce::TextEditor ("ipUrlPortTextEditor"));
    addAndMakeVisible (textEditor_ipUrlPort.get());
    textEditor_ipUrlPort->setTooltip (TRANS("localhost:5005"));
    textEditor_ipUrlPort->setMultiLine (false);
    textEditor_ipUrlPort->setReturnKeyStartsNewLine (false);
    textEditor_ipUrlPort->setReadOnly (false);
    textEditor_ipUrlPort->setScrollbarsShown (true);
    textEditor_ipUrlPort->setCaretVisible (true);
    textEditor_ipUrlPort->setPopupMenuEnabled (true);
    textEditor_ipUrlPort->setText (TRANS("localhost:5005"));

    textEditor_ipUrlPort->setBounds (264, 249, 200, 24);

    textEditor_identifier.reset (new juce::TextEditor ("identifierTextEdit"));
    addAndMakeVisible (textEditor_identifier.get());
    textEditor_identifier->setMultiLine (false);
    textEditor_identifier->setReturnKeyStartsNewLine (false);
    textEditor_identifier->setReadOnly (false);
    textEditor_identifier->setScrollbarsShown (true);
    textEditor_identifier->setCaretVisible (true);
    textEditor_identifier->setPopupMenuEnabled (true);
    textEditor_identifier->setText (TRANS("default"));

    textEditor_identifier->setBounds (264, 289, 150, 24);

    button_apply.reset (new juce::TextButton ("apply_button"));
    addAndMakeVisible (button_apply.get());
    button_apply->setButtonText (TRANS("Apply"));
    button_apply->addListener (this);

    button_apply->setBounds (264, 337, 144, 40);

    lable_directionOfConnection.reset (new juce::Label ("directionOfConnectionLabel",
                                                        TRANS("Direction Of Connection")));
    addAndMakeVisible (lable_directionOfConnection.get());
    lable_directionOfConnection->setFont (juce::Font (22.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lable_directionOfConnection->setJustificationType (juce::Justification::centredRight);
    lable_directionOfConnection->setEditable (false, false, false);
    lable_directionOfConnection->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lable_directionOfConnection->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lable_directionOfConnection->setBounds (0, 49, 256, 24);

    label_modeOfOperation.reset (new juce::Label ("modeOfOperationLabel",
                                                  TRANS("Mode Of Operation")));
    addAndMakeVisible (label_modeOfOperation.get());
    label_modeOfOperation->setFont (juce::Font (22.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_modeOfOperation->setJustificationType (juce::Justification::centredRight);
    label_modeOfOperation->setEditable (false, false, false);
    label_modeOfOperation->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_modeOfOperation->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_modeOfOperation->setBounds (0, 121, 256, 24);

    label_transmissionProtocolLabel.reset (new juce::Label ("transmissionProtocolLabel",
                                                            TRANS("Transmission Protocol")));
    addAndMakeVisible (label_transmissionProtocolLabel.get());
    label_transmissionProtocolLabel->setFont (juce::Font (22.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_transmissionProtocolLabel->setJustificationType (juce::Justification::centredRight);
    label_transmissionProtocolLabel->setEditable (false, false, false);
    label_transmissionProtocolLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_transmissionProtocolLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_transmissionProtocolLabel->setBounds (0, 192, 256, 24);

    label_ipaddres.reset (new juce::Label ("ipaddresLabel",
                                           TRANS("IP/URL : Port")));
    addAndMakeVisible (label_ipaddres.get());
    label_ipaddres->setFont (juce::Font (22.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_ipaddres->setJustificationType (juce::Justification::centredRight);
    label_ipaddres->setEditable (false, false, false);
    label_ipaddres->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_ipaddres->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_ipaddres->setBounds (106, 249, 150, 24);

    label_identifierLabel.reset (new juce::Label ("identifierLabel",
                                                  TRANS("Identifier")));
    addAndMakeVisible (label_identifierLabel.get());
    label_identifierLabel->setFont (juce::Font (22.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_identifierLabel->setJustificationType (juce::Justification::centredRight);
    label_identifierLabel->setEditable (false, false, false);
    label_identifierLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_identifierLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_identifierLabel->setBounds (106, 289, 150, 24);

    hyperlink_gitHub.reset (new juce::HyperlinkButton (TRANS("ReaXstream on GitHub"),
                                                       juce::URL ("https://github.com/JessyJP/ReaXstream")));
    addAndMakeVisible (hyperlink_gitHub.get());
    hyperlink_gitHub->setTooltip (TRANS("https://github.com/JessyJP/ReaXstream"));
    hyperlink_gitHub->setButtonText (TRANS("ReaXstream on GitHub"));

    hyperlink_gitHub->setBounds (264, 393, 184, 24);

    juce__label6.reset (new juce::Label ("new label",
                                         TRANS("+++ PUT Audio Levels here\n")));
    addAndMakeVisible (juce__label6.get());
    juce__label6->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label6->setJustificationType (juce::Justification::centredLeft);
    juce__label6->setEditable (false, false, false);
    juce__label6->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label6->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label6->setBounds (208, 432, 288, 24);

    juce__label7.reset (new juce::Label ("new label",
                                         TRANS("+++ Put ReaXstream cool text logo here")));
    addAndMakeVisible (juce__label7.get());
    juce__label7->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label7->setJustificationType (juce::Justification::centredLeft);
    juce__label7->setEditable (false, false, false);
    juce__label7->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label7->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label7->setBounds (224, 8, 288, 24);


    //[UserPreSize]
 //   textEditor_ipUrlPort->addListener(this);//TODO figure out the texteditor callback methods
 //   textEditor_identifier->addListener(this);//TODO figure out the texteditor callback methods
    //[/UserPreSize]

    setSize (600, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ReaXstreamGUI::~ReaXstreamGUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    comboBox_directionOfConnection = nullptr;
    comboBox_modeOfOperation = nullptr;
    comboBox_transmissionProtocol = nullptr;
    textEditor_ipUrlPort = nullptr;
    textEditor_identifier = nullptr;
    button_apply = nullptr;
    lable_directionOfConnection = nullptr;
    label_modeOfOperation = nullptr;
    label_transmissionProtocolLabel = nullptr;
    label_ipaddres = nullptr;
    label_identifierLabel = nullptr;
    hyperlink_gitHub = nullptr;
    juce__label6 = nullptr;
    juce__label7 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ReaXstreamGUI::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ReaXstreamGUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ReaXstreamGUI::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    flagChangeGUIstate = true;
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBox_directionOfConnection.get())
    {
        //[UserComboBoxCode_comboBox_directionOfConnection] -- add your combo box handling code here..
        LOG(LOG_GUI, "Direction of Connection Change [" + convertEnum2String(getStateDirectionOfConnectionComboBox()) + "]");
        this->rxAudioProcessor->setDirectionOfConnection(getStateDirectionOfConnectionComboBox());
        //[/UserComboBoxCode_comboBox_directionOfConnection]
    }
    else if (comboBoxThatHasChanged == comboBox_modeOfOperation.get())
    {
        //[UserComboBoxCode_comboBox_modeOfOperation] -- add your combo box handling code here..
        LOG(LOG_GUI, "Mode of operation [" + convertEnum2String(getStateModeOfOperationComboBox()) + "]");
        // Set the apptopirate transmission protocols for the corresponding mode
        updateTransmissionProtocolsForModeSelection(getStateModeOfOperationComboBox());
        this->rxAudioProcessor->setModeOfOperation(getStateModeOfOperationComboBox());
        //[/UserComboBoxCode_comboBox_modeOfOperation]
    }
    else if (comboBoxThatHasChanged == comboBox_transmissionProtocol.get())
    {
        //[UserComboBoxCode_comboBox_transmissionProtocol] -- add your combo box handling code here..
        LOG(LOG_GUI, "Transmission protocol [" + convertEnum2String(getStateTransmissionProtocolComboBox()) + "]");
        this->rxAudioProcessor->setTransmissionProtocol(getStateTransmissionProtocolComboBox());
        //[/UserComboBoxCode_comboBox_transmissionProtocol]
    }

    //[UsercomboBoxChanged_Post]
    this->rxAudioProcessor->requestConnectionReset(this->checkGUIstateChanged());
    //[/UsercomboBoxChanged_Post]
}

void ReaXstreamGUI::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == button_apply.get())
    {
        //[UserButtonCode_button_apply] -- add your button handler code here..
        textEditorTextChanged();
        //[/UserButtonCode_button_apply]
    }

    //[UserbuttonClicked_Post]
    this->rxAudioProcessor->requestConnectionReset(this->checkGUIstateChanged());
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//==============================================================================
void ReaXstreamGUI::setReaXstreamAudioProcessorP(ReaXstreamAudioProcessor* rxAudioProcessorP_in)
{
    this->rxAudioProcessor = rxAudioProcessorP_in;
    // This function is called by the child constructor as to not call this in the constructor itself.
}

bool ReaXstreamGUI::checkGUIstateChanged()
{
    if (flagChangeGUIstate)// if true then reset it and return that it was true, ptherwise return false
    {
        flagChangeGUIstate = false; // Reset when cheked.
        return true;
    }
    return false;
}

// GUI elements get state methods
DirectionOfConnection ReaXstreamGUI::getStateDirectionOfConnectionComboBox()
{
    return DirectionOfConnection(comboBox_directionOfConnection->getSelectedId());
}

ModeOfOperation ReaXstreamGUI::getStateModeOfOperationComboBox()
{
    return ModeOfOperation(comboBox_modeOfOperation->getSelectedId());
}

TransmissionProtocol ReaXstreamGUI::getStateTransmissionProtocolComboBox()
{
    return TransmissionProtocol(comboBox_transmissionProtocol->getSelectedId());
}

//std::string ReaXstreamGUI::getStateIpUrlPortTextEditor()
//{
//    return textEditor_ipUrlPort->getText();
//} // TODO FINISh this and the next function and use them

//int ReaXstreamGUI::getStateIdentifierTextEditor()
//{
//    return 0;
//}

// Method to set the apptopirate transmission protocols for the corresponding mode
void ReaXstreamGUI::updateTransmissionProtocolsForModeSelection(ModeOfOperation mode)
{
    // TODO: finish this function
    std::list<TransmissionProtocol> availableProtocolList = getAvailableProtocolByModeOfOperation(mode);
    LOG(LOG_INFO, "");
    LOG(LOG_INFO, convertEnum2String(mode));
    for (auto const& protoStr : availableProtocolList)
    {
        LOG(LOG_INFO, "|-- " + convertEnum2String(protoStr));
    }

    // Loop over the options in the Protocol list in the combo box
    for (int i = 1; i <= comboBox_transmissionProtocol->getNumItems(); i++)
    {
        bool found = false;
        // Loop over the protocols and
        for (auto const& avalableProtocol : availableProtocolList)
        {
            // If the protocol is found, enable the protocol and break out of the loop and continue
            if (avalableProtocol == comboBox_transmissionProtocol->getItemId(i))
            {
                comboBox_transmissionProtocol->setItemEnabled(i,true);
                found = true;
                break;
            }
        }

        // If not found in the list of available protocols disable the protocol
        if (!found)
        {
            comboBox_transmissionProtocol->setItemEnabled(i,false);
        }
        LOG(LOG_ERROR, "SOMETHING IS WRONG, TODO: debug and fix");
    }
}

// Overwrite the listner function for the text fields
void ReaXstreamGUI::textEditorTextChanged()//juce::TextEditor* textEditorThatHasChanged
{

    flagChangeGUIstate = true;

//    if (textEditorThatHasChanged == textEditor_ipUrlPort.get())
    {
        LOG(LOG_WARNING LOG_GUI, "THE IP/URL:port NEEDS INPUT VALIDATION!!!");
        LOG(LOG_GUI, "IP [" + textEditor_ipUrlPort->getText().toStdString() + "]");
        rxAudioProcessor->setIP(textEditor_ipUrlPort->getText().toStdString());
        //TODO: it's not wokring !!!!!!!!!
    }
//    else if (textEditorThatHasChanged == textEditor_identifier.get())
    {
        LOG(LOG_WARNING LOG_GUI, "THE IDENTIFIER NEEDS INPUT VALIDATION!!!");
        LOG(LOG_GUI, "Label [" + textEditor_identifier->getText().toStdString() + "]");
        rxAudioProcessor->setIdentifier(textEditor_identifier->getText().toStdString());

    }

    this->rxAudioProcessor->requestConnectionReset(this->checkGUIstateChanged());


}
//==============================================================================
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ReaXstreamGUI" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="600">
  <BACKGROUND backgroundColour="ff323e44"/>
  <COMBOBOX name="directionOfConnectionComboBox" id="7c29d2021560a2d0" memberName="comboBox_directionOfConnection"
            virtualName="" explicitFocusOrder="0" pos="264 49 280 32" editable="0"
            layout="33" items="Host Server Transmitter&#10;&#10;Client Receiver"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="modeOfOperationComboBox" id="dd7819fc9b8b5151" memberName="comboBox_modeOfOperation"
            virtualName="" explicitFocusOrder="0" pos="264 121 280 32" editable="0"
            layout="33" items="ReaStreamClassic&#10;&#10;ReaStreamMobile&#10;&#10;ReaInterConnect"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="transmissionProtocolComboBox" id="92fbe0d462e2316e" memberName="comboBox_transmissionProtocol"
            virtualName="" explicitFocusOrder="0" pos="264 192 280 32" editable="0"
            layout="33" items="UDP&#10;&#10;TCP&#10;&#10;SharedMemory&#10;&#10;USB"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTEDITOR name="ipUrlPortTextEditor" id="24663907342789dd" memberName="textEditor_ipUrlPort"
              virtualName="" explicitFocusOrder="0" pos="264 249 200 24" tooltip="localhost:5005"
              initialText="localhost:5005" multiline="0" retKeyStartsLine="0"
              readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="identifierTextEdit" id="3dc7429827394451" memberName="textEditor_identifier"
              virtualName="" explicitFocusOrder="0" pos="264 289 150 24" initialText="default"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="apply_button" id="d34c5dc5dafae149" memberName="button_apply"
              virtualName="" explicitFocusOrder="0" pos="264 337 144 40" buttonText="Apply"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="directionOfConnectionLabel" id="f95d663081268283" memberName="lable_directionOfConnection"
         virtualName="" explicitFocusOrder="0" pos="0 49 256 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Direction Of Connection" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="22.0" kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="modeOfOperationLabel" id="c1dfa9e780524ac3" memberName="label_modeOfOperation"
         virtualName="" explicitFocusOrder="0" pos="0 121 256 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Mode Of Operation" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="22.0" kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="transmissionProtocolLabel" id="f14641459af31190" memberName="label_transmissionProtocolLabel"
         virtualName="" explicitFocusOrder="0" pos="0 192 256 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Transmission Protocol" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="22.0" kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="ipaddresLabel" id="7693eeae6ebceb8" memberName="label_ipaddres"
         virtualName="" explicitFocusOrder="0" pos="106 249 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="IP/URL : Port" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="22.0" kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="identifierLabel" id="a54772e0dcb1892a" memberName="label_identifierLabel"
         virtualName="" explicitFocusOrder="0" pos="106 289 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Identifier" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="22.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <HYPERLINKBUTTON name="gitHubHyperlink" id="17b08a3c4e2b4a2" memberName="hyperlink_gitHub"
                   virtualName="" explicitFocusOrder="0" pos="264 393 184 24" tooltip="https://github.com/JessyJP/ReaXstream"
                   buttonText="ReaXstream on GitHub" connectedEdges="0" needsCallback="0"
                   radioGroupId="0" url="https://github.com/JessyJP/ReaXstream"/>
  <LABEL name="new label" id="ea426327de1b3551" memberName="juce__label6"
         virtualName="" explicitFocusOrder="0" pos="208 432 288 24" edTextCol="ff000000"
         edBkgCol="0" labelText="+++ PUT Audio Levels here&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2b6750f7890c35fe" memberName="juce__label7"
         virtualName="" explicitFocusOrder="0" pos="224 8 288 24" edTextCol="ff000000"
         edBkgCol="0" labelText="+++ Put ReaXstream cool text logo here"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

