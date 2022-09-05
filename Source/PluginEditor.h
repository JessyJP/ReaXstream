/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ReaXstreamGUI.h"

//==============================================================================
/**
*/
class ReaXstreamAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ReaXstreamAudioProcessorEditor (ReaXstreamAudioProcessor&);
    ~ReaXstreamAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ReaXstreamAudioProcessor& audioProcessor;

    // This pointer will hold the main content componenet for the GUI
    std::unique_ptr<ReaXstreamGUI> rxgui;
    // If needed a get funcion can be made available publicly.
    // If that is the case then all the internal element component handles can be 
    // made publicly available. In general, however, this shouldn't be done and only
    // the funcionality needed should be exposed by the "ReaXstreamGUI" class.

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReaXstreamAudioProcessorEditor)
};
