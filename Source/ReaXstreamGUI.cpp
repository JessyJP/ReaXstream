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
#include <cassert>

// Options class is defined in
//#include "../Submodules/sound_meter/meter/sd_MeterHelpers.h"

//[/Headers]

#include "ReaXstreamGUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
void ReaXstreamGUI::TextEditListner_Class::textEditorTextChanged(juce::TextEditor* textEditorThatHasChanged)
{

 //   flagChangeGUIstate = true;
 //
 //   //    if (textEditorThatHasChanged == textEditor_ipUrlPort.get())
 //   {
 //       LOG(LOG_WARNING LOG_GUI, "THE IP/URL:port NEEDS INPUT VALIDATION!!!");
 //       LOG(LOG_GUI, "IP [" + textEditor_ipUrlPort->getText().toStdString() + "]");
 //       rxAudioProcessor->setIP(textEditor_ipUrlPort->getText().toStdString());
 //       //TODO: it's not wokring !!!!!!!!!
 //   }
 //   //    else if (textEditorThatHasChanged == textEditor_identifier.get())
 //   {
 //       LOG(LOG_WARNING LOG_GUI, "THE IDENTIFIER NEEDS INPUT VALIDATION!!!");
 //       LOG(LOG_GUI, "Label [" + textEditor_identifier->getText().toStdString() + "]");
 //       rxAudioProcessor->setIdentifier(textEditor_identifier->getText().toStdString());
 //
 //   }
 //
 //   this->rxAudioProcessor->requestConnectionReset(this->checkGUIstateChanged());


}
//[/MiscUserDefs]

//==============================================================================
ReaXstreamGUI::ReaXstreamGUI ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    flagChangeGUIstate = true;
    //[/Constructor_pre]

    label_LOGO.reset (new juce::Label ("LOGO_label",
                                       TRANS("ReaXstream")));
    addAndMakeVisible (label_LOGO.get());
    label_LOGO->setFont (juce::Font ("David CLM", 30.50f, juce::Font::plain).withExtraKerningFactor (0.035f));
    label_LOGO->setJustificationType (juce::Justification::centredTop);
    label_LOGO->setEditable (false, false, false);
    label_LOGO->setColour (juce::Label::backgroundColourId, juce::Colour (0x008f1414));
    label_LOGO->setColour (juce::Label::textColourId, juce::Colours::red);
    label_LOGO->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_LOGO->setColour (juce::TextEditor::backgroundColourId, juce::Colours::blue);

    label_LOGO->setBounds (0, 0, 300, 50);

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

    textEditor_ipUrlPort.reset (new juce::TextEditor ("ipUrlPortTextEditor"));
    addAndMakeVisible (textEditor_ipUrlPort.get());
    textEditor_ipUrlPort->setTooltip (TRANS("localhost:58710"));
    textEditor_ipUrlPort->setMultiLine (false);
    textEditor_ipUrlPort->setReturnKeyStartsNewLine (false);
    textEditor_ipUrlPort->setReadOnly (false);
    textEditor_ipUrlPort->setScrollbarsShown (false);
    textEditor_ipUrlPort->setCaretVisible (true);
    textEditor_ipUrlPort->setPopupMenuEnabled (true);
    textEditor_ipUrlPort->setText (TRANS("localhost:58710"));

    textEditor_identifier.reset (new juce::TextEditor ("identifierTextEdit"));
    addAndMakeVisible (textEditor_identifier.get());
    textEditor_identifier->setMultiLine (false);
    textEditor_identifier->setReturnKeyStartsNewLine (false);
    textEditor_identifier->setReadOnly (false);
    textEditor_identifier->setScrollbarsShown (false);
    textEditor_identifier->setCaretVisible (true);
    textEditor_identifier->setPopupMenuEnabled (true);
    textEditor_identifier->setText (TRANS("default"));

    label_directionOfConnection.reset (new juce::Label ("directionOfConnectionLabel",
                                                        TRANS("Direction Of Connection")));
    addAndMakeVisible (label_directionOfConnection.get());
    label_directionOfConnection->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_directionOfConnection->setJustificationType (juce::Justification::centredBottom);
    label_directionOfConnection->setEditable (false, false, false);
    label_directionOfConnection->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_directionOfConnection->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_modeOfOperation.reset (new juce::Label ("modeOfOperationLabel",
                                                  TRANS("Mode Of Operation")));
    addAndMakeVisible (label_modeOfOperation.get());
    label_modeOfOperation->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_modeOfOperation->setJustificationType (juce::Justification::centredBottom);
    label_modeOfOperation->setEditable (false, false, false);
    label_modeOfOperation->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_modeOfOperation->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_transmissionProtocolLabel.reset (new juce::Label ("transmissionProtocolLabel",
                                                            TRANS("Transmission Protocol")));
    addAndMakeVisible (label_transmissionProtocolLabel.get());
    label_transmissionProtocolLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_transmissionProtocolLabel->setJustificationType (juce::Justification::centredBottom);
    label_transmissionProtocolLabel->setEditable (false, false, false);
    label_transmissionProtocolLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_transmissionProtocolLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_ipaddres.reset (new juce::Label ("ipaddresLabel",
                                           TRANS("IP/URL : Port")));
    addAndMakeVisible (label_ipaddres.get());
    label_ipaddres->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_ipaddres->setJustificationType (juce::Justification::centredBottom);
    label_ipaddres->setEditable (false, false, false);
    label_ipaddres->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_ipaddres->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_identifierLabel.reset (new juce::Label ("identifierLabel",
                                                  TRANS("Identifier")));
    addAndMakeVisible (label_identifierLabel.get());
    label_identifierLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_identifierLabel->setJustificationType (juce::Justification::centredBottom);
    label_identifierLabel->setEditable (false, false, false);
    label_identifierLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_identifierLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    hyperlink_gitHub.reset (new juce::HyperlinkButton (TRANS("link to GitHub"),
                                                       juce::URL ("https://github.com/JessyJP/ReaXstream")));
    addAndMakeVisible (hyperlink_gitHub.get());
    hyperlink_gitHub->setTooltip (TRANS("https://github.com/JessyJP/ReaXstream"));
    hyperlink_gitHub->setButtonText (TRANS("link to GitHub"));

    label_dbLevelRMS.reset (new juce::Label ("dbLevelRMS_label",
                                             TRANS("-inf")));
    addAndMakeVisible (label_dbLevelRMS.get());
    label_dbLevelRMS->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_dbLevelRMS->setJustificationType (juce::Justification::centredLeft);
    label_dbLevelRMS->setEditable (false, false, false);
    label_dbLevelRMS->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_dbLevelRMS->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_dbLevelRMS->setBounds (32, 392, 48, 48);


    //[UserPreSize]

    // ---- This section modifies the communication protocols.
    // By default all transmission/reception protocols should be disabled unitl the user selelcts the communication mode.
    for (int i = 0; i < comboBox_transmissionProtocol->getNumItems(); i++)// i is the item index
    {// The loop is standard C++ loop starting at 0 and up to but exluding a fixed limit.
     // The combo box indices, however, start 1 one and go to the limit.
     // But the indexing of the items will start from 0
        assert(comboBox_transmissionProtocol->getItemId(i) != 0);
        comboBox_transmissionProtocol->setItemEnabled(i+1, false);
    }

    // ---- This section modifies the input textfields
    // Change the size of the font
    juce::String tmpStr = "";
    textEditor_ipUrlPort->setFont(16);
    textEditor_identifier->setFont(16);
    // Refresh the strings by reapplying them
    tmpStr = textEditor_ipUrlPort->getText();
    textEditor_ipUrlPort->setText(TRANS(""));
    textEditor_ipUrlPort->setText(tmpStr);
    tmpStr = textEditor_identifier->getText();
    textEditor_identifier->setText(TRANS(""));
    textEditor_identifier->setText(tmpStr);

//    textEditor_ipUrlPort->addListener(this);//TODO figure out the texteditor callback methods
 //   textEditor_identifier->addListener(this);//TODO figure out the texteditor callback methods
    // It's most likely quite tricky to have *this (dual meaning here) componenet to inherit from the Listner::TextEdit Class.

    // ---- This section creates the custom level meter
    
//    level_meter.reset( new sd::SoundMeter::MetersComponent());
//    level_meter->setChannelFormat(juce::AudioChannelSet::stereo());
//    addAndMakeVisible(level_meter.get());
//    // Set options
//    sd::SoundMeter::Options meterOptions;
//    meterOptions.faderEnabled = true;
//    meterOptions.headerEnabled = true;
//    meterOptions.peakRegion_db = -3.0f;
//    meterOptions.warningRegion_db = -12.0f;
//    level_meter->setOptions(meterOptions);

    level_meter_L.reset( new Gui::HorizontalMeter());
    level_meter_L->setBounds(10,  400 , 280, 16 );
    level_meter_L->setBounds(10, 400, 280, 16);
    addAndMakeVisible(level_meter_L.get());
    level_meter_L->setLevel(-18.f);

    level_meter_R.reset(new Gui::HorizontalMeter());
    level_meter_R->setBounds(10, 400, 280, 16);
    level_meter_R->setBounds(10, 400+8+16, 280, 16);
    addAndMakeVisible(level_meter_R.get());
    level_meter_R->setLevel(-18.f);


    //[/UserPreSize]

    setSize (300, 450);


    //[Constructor] You can add your own custom stuff here..
    //setSize(300 + 200, 450);// Fоr testing
    //[/Constructor]
}

ReaXstreamGUI::~ReaXstreamGUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label_LOGO = nullptr;
    comboBox_directionOfConnection = nullptr;
    comboBox_modeOfOperation = nullptr;
    comboBox_transmissionProtocol = nullptr;
    textEditor_ipUrlPort = nullptr;
    textEditor_identifier = nullptr;
    label_directionOfConnection = nullptr;
    label_modeOfOperation = nullptr;
    label_transmissionProtocolLabel = nullptr;
    label_ipaddres = nullptr;
    label_identifierLabel = nullptr;
    hyperlink_gitHub = nullptr;
    label_dbLevelRMS = nullptr;


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

    comboBox_directionOfConnection->setBounds (0 + 300 / 2 - (280 / 2), 0 + 50 - -32, 280, 32);
    comboBox_modeOfOperation->setBounds ((0 + 300 / 2 - (280 / 2)) + 280 / 2 - (280 / 2), (0 + 50 - -32) + 32 - -32, 280, 32);
    comboBox_transmissionProtocol->setBounds (((0 + 300 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (280 / 2), ((0 + 50 - -32) + 32 - -32) + 32 - -32, 280, 32);
    textEditor_ipUrlPort->setBounds ((((0 + 300 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (280 / 2), (((0 + 50 - -32) + 32 - -32) + 32 - -32) + 32 - -32, 280, 32);
    textEditor_identifier->setBounds (((((0 + 300 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (280 / 2), ((((0 + 50 - -32) + 32 - -32) + 32 - -32) + 32 - -32) + 32 - -32, 280, 32);
    label_directionOfConnection->setBounds ((0 + 300 / 2 - (280 / 2)) + 280 / 2 - (220 / 2), (0 + 50 - -32) + 0 - 16, 220, 16);
    label_modeOfOperation->setBounds (((0 + 300 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (220 / 2), ((0 + 50 - -32) + 32 - -32) + 0 - 16, 220, 16);
    label_transmissionProtocolLabel->setBounds ((((0 + 300 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (220 / 2), (((0 + 50 - -32) + 32 - -32) + 32 - -32) + 0 - 16, 220, 16);
    label_ipaddres->setBounds (((((0 + 300 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (220 / 2), ((((0 + 50 - -32) + 32 - -32) + 32 - -32) + 32 - -32) + 0 - 16, 220, 16);
    label_identifierLabel->setBounds ((((((0 + 300 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (280 / 2)) + 280 / 2 - (220 / 2), (((((0 + 50 - -32) + 32 - -32) + 32 - -32) + 32 - -32) + 32 - -32) + 0 - 16, 220, 16);
    hyperlink_gitHub->setBounds (0 + 300 / 2 - (128 / 2), 0 + 50 - 5 - 16, 128, 16);
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
    LOG(LOG_GUI,"[ReaXstreamGUI] requestests for reset from the GUI side!")
    this->rxAudioProcessor->requestConnectionReset(this->checkGUIstateChanged());
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//==============================================================================

void ReaXstreamGUI::setReaXstreamAudioProcessorP(ReaXstreamAudioProcessor* rxAudioProcessorP_in)
{
    this->rxAudioProcessor = rxAudioProcessorP_in;
    // This function is called by the constructor of the Plugin Editor's constructor after this GUI
    // componenet instance has been initialized by the editor's constructor.
    // The editor has been initialized after the processor is fully initialized.
    // Therefore, default parameters for the GUI can be extracted from the processor here.
    this->rxAudioProcessor->getSet_ReaXstreamGUIpointer((void*)this);

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
std::string ReaXstreamGUI::getStateIpUrlPortTextEditor_IPURL()
{
    return textEditor_ipUrlPort->getText().toStdString();
}
int ReaXstreamGUI::getStateIpUrlPortTextEditor_port()
{// TODO: FINISH this method
//    return textEditor_ipUrlPort->getText().toStdString();
    return 0;
}
std::string ReaXstreamGUI::getStateIdentifierTextEditor()
{
    return textEditor_identifier->getText().toStdString();
}

// GUI elements set state methods
void ReaXstreamGUI::setStateDirectionOfConnectionComboBox(DirectionOfConnection  in_DoC)
{// The IDs and the options should be already matched.
    if (!isValidEnum(in_DoC) )
    {
        LOG(LOG_ERROR, "[DirectionOfConnection] Not Valid enum: " + std::to_string(in_DoC));
        return;
    }
    comboBox_directionOfConnection->setSelectedId((int)in_DoC);
    LOG(LOG_ERROR, "[DirectionOfConnection] Set to: [" + convertEnum2String(in_DoC)+"]");
}
void ReaXstreamGUI::setStateModeOfOperationComboBox(ModeOfOperation in_MoO)
{// The IDs and the options should be already matched.
    if (!isValidEnum(in_MoO) )
    {
        LOG(LOG_ERROR, "[ModeOfOperation] Not Valid enum: " + std::to_string(in_MoO));
        return;
    }
    comboBox_modeOfOperation->setSelectedId((int)in_MoO);
    LOG(LOG_ERROR, "[DirectionOfConnection] Set to: [" + convertEnum2String(in_MoO) + "]");
}
void ReaXstreamGUI::setStateTransmissionProtocolComboBox(TransmissionProtocol in_TP)
{// The IDs and the options should be already matched.
    if (!isValidEnum(in_TP))
    {
        LOG(LOG_ERROR, "[ModeOfOperation] Not Valid enum: " + std::to_string(in_TP));
        return;
    }
    comboBox_transmissionProtocol->setSelectedId((int)in_TP);
    LOG(LOG_ERROR, "[DirectionOfConnection] Set to: [" + convertEnum2String(in_TP) + "]");
}
void ReaXstreamGUI::setStateIpUrlPortTextEditor_IPURL(std::string in_ipOrUrl) {/*Todo finish this function*/}
void ReaXstreamGUI::setStateIpUrlPortTextEditor_port(unsigned short in_port) {/*Todo finish this function*/ }
void ReaXstreamGUI::setStateIpUrlPortTextEditor(std::string in_ipOrUrlPort) {/*Todo finish this function*/ }
void ReaXstreamGUI::setStateIpUrlPortTextEditor(std::string in_ipOrUrk, unsigned short in_port)
{
    setStateIpUrlPortTextEditor_IPURL(in_ipOrUrk);
    setStateIpUrlPortTextEditor_port(in_port);
}
void ReaXstreamGUI::setStateIdentifierTextEditor(std::string in_identifier)
{/*Todo finish this function*/
}
void ReaXstreamGUI::setAudioLevelsAndRepaint(int channel, float level)
{
    jassert(channel == 0 | channel == 1);
    if (channel == 0) 
    { 
        level_meter_L->setLevel(level);
        level_meter_L->repaint();
    };
    if (channel == 1) 
    { 
        level_meter_R->setLevel(level);
        level_meter_R->repaint();
    };
}

// Method to set the apptopirate transmission protocols for the corresponding mode
void ReaXstreamGUI::updateTransmissionProtocolsForModeSelection(ModeOfOperation mode)
{
    // Get list for the available protocols for the corresponding mode of operation
    std::list<TransmissionProtocol> availableProtocolList = getAvailableProtocolByModeOfOperation(mode);

    // Just some logging for display purposess
    LOG(LOG_INFO, "");
    LOG(LOG_INFO, convertEnum2String(mode));
    for (auto const& protoStr : availableProtocolList)
    {
        LOG(LOG_INFO, "|-- " + convertEnum2String(protoStr));
    }

    // Loop over the options in the Protocol list in the combo box by index then get the ID of the item with the corresponding index.
    // Notes{!} included at the end of the constructor why the indexing is this way.
    for (int item_Index = 0; item_Index < comboBox_transmissionProtocol->getNumItems(); item_Index++)
    {
        // The IDs match the enumerations, therefore direclty set the TP_ID as the corresponding ID - enumeration
        TransmissionProtocol TP_ID = (TransmissionProtocol) comboBox_transmissionProtocol->getItemId(item_Index);

        // This, slightly redundnat, part validates that the type-cast enumeration and the ID of the corresponding index are valid.
        assert(isValidEnum(TP_ID));
        assert(comboBox_transmissionProtocol->getItemId(item_Index) != 0);

        bool found = false;

        // Loop over the protocols and
        for (auto const& avalableProtocol : availableProtocolList)
        {
            // If the protocol is found, enable the protocol and break out of the loop and continue
            if (avalableProtocol == TP_ID)
            {
                comboBox_transmissionProtocol->setItemEnabled(TP_ID,true);
                LOG(LOG_GUI, "Enabled: " + convertEnum2String(TP_ID));
                found = true;
                break;
            }
        }

        // If not found in the list of available protocols disable the protocol
        if (!found)
        {
            comboBox_transmissionProtocol->setItemEnabled(TP_ID,false);
            LOG(LOG_GUI, "Disabled: " + convertEnum2String(TP_ID));
        }

    }
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
                 fixedSize="0" initialWidth="300" initialHeight="450">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="LOGO_label" id="2b6750f7890c35fe" memberName="label_LOGO"
         virtualName="" explicitFocusOrder="0" pos="0 0 300 50" bkgCol="8f1414"
         textCol="ffff0000" edTextCol="ff000000" edBkgCol="ff0000ff" labelText="ReaXstream"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="David CLM" fontsize="30.5" kerning="0.035" bold="0"
         italic="0" justification="12"/>
  <COMBOBOX name="directionOfConnectionComboBox" id="7c29d2021560a2d0" memberName="comboBox_directionOfConnection"
            virtualName="" explicitFocusOrder="0" pos="0Cc -32R 280 32" posRelativeX="2b6750f7890c35fe"
            posRelativeY="2b6750f7890c35fe" editable="0" layout="33" items="Host Server Transmitter&#10;&#10;Client Receiver"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="modeOfOperationComboBox" id="dd7819fc9b8b5151" memberName="comboBox_modeOfOperation"
            virtualName="" explicitFocusOrder="0" pos="0Cc -32R 280 32" posRelativeX="7c29d2021560a2d0"
            posRelativeY="7c29d2021560a2d0" editable="0" layout="33" items="ReaStreamClassic&#10;&#10;ReaStreamMobile&#10;&#10;ReaInterConnect"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="transmissionProtocolComboBox" id="92fbe0d462e2316e" memberName="comboBox_transmissionProtocol"
            virtualName="" explicitFocusOrder="0" pos="0Cc -32R 280 32" posRelativeX="dd7819fc9b8b5151"
            posRelativeY="dd7819fc9b8b5151" editable="0" layout="33" items="UDP&#10;&#10;TCP&#10;&#10;SharedMemory&#10;&#10;USB"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTEDITOR name="ipUrlPortTextEditor" id="24663907342789dd" memberName="textEditor_ipUrlPort"
              virtualName="" explicitFocusOrder="0" pos="0Cc -32R 280 32" posRelativeX="92fbe0d462e2316e"
              posRelativeY="92fbe0d462e2316e" tooltip="localhost:58710" initialText="localhost:58710"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="identifierTextEdit" id="3dc7429827394451" memberName="textEditor_identifier"
              virtualName="" explicitFocusOrder="0" pos="0Cc -32R 280 32" posRelativeX="24663907342789dd"
              posRelativeY="24663907342789dd" initialText="default" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
  <LABEL name="directionOfConnectionLabel" id="f95d663081268283" memberName="label_directionOfConnection"
         virtualName="" explicitFocusOrder="0" pos="0Cc 0r 220 16" posRelativeX="7c29d2021560a2d0"
         posRelativeY="7c29d2021560a2d0" edTextCol="ff000000" edBkgCol="0"
         labelText="Direction Of Connection" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="20"/>
  <LABEL name="modeOfOperationLabel" id="c1dfa9e780524ac3" memberName="label_modeOfOperation"
         virtualName="" explicitFocusOrder="0" pos="0Cc 0r 220 16" posRelativeX="dd7819fc9b8b5151"
         posRelativeY="dd7819fc9b8b5151" edTextCol="ff000000" edBkgCol="0"
         labelText="Mode Of Operation" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="20"/>
  <LABEL name="transmissionProtocolLabel" id="f14641459af31190" memberName="label_transmissionProtocolLabel"
         virtualName="" explicitFocusOrder="0" pos="0Cc 0r 220 16" posRelativeX="92fbe0d462e2316e"
         posRelativeY="92fbe0d462e2316e" edTextCol="ff000000" edBkgCol="0"
         labelText="Transmission Protocol" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="20"/>
  <LABEL name="ipaddresLabel" id="7693eeae6ebceb8" memberName="label_ipaddres"
         virtualName="" explicitFocusOrder="0" pos="0Cc 0r 220 16" posRelativeX="24663907342789dd"
         posRelativeY="24663907342789dd" edTextCol="ff000000" edBkgCol="0"
         labelText="IP/URL : Port" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="20"/>
  <LABEL name="identifierLabel" id="a54772e0dcb1892a" memberName="label_identifierLabel"
         virtualName="" explicitFocusOrder="0" pos="0Cc 0r 220 16" posRelativeX="3dc7429827394451"
         posRelativeY="3dc7429827394451" edTextCol="ff000000" edBkgCol="0"
         labelText="Identifier" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="20"/>
  <HYPERLINKBUTTON name="gitHubHyperlink" id="17b08a3c4e2b4a2" memberName="hyperlink_gitHub"
                   virtualName="" explicitFocusOrder="0" pos="0Cc 5Rr 128 16" posRelativeX="2b6750f7890c35fe"
                   posRelativeY="2b6750f7890c35fe" tooltip="https://github.com/JessyJP/ReaXstream"
                   buttonText="link to GitHub" connectedEdges="0" needsCallback="0"
                   radioGroupId="0" url="https://github.com/JessyJP/ReaXstream"/>
  <LABEL name="dbLevelRMS_label" id="ea426327de1b3551" memberName="label_dbLevelRMS"
         virtualName="" explicitFocusOrder="0" pos="32 392 48 48" edTextCol="ff000000"
         edBkgCol="0" labelText="-inf" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

