/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ReaXstreamAudioProcessorEditor::ReaXstreamAudioProcessorEditor (ReaXstreamAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    rxgui.reset(new ReaXstreamGUI());
    addAndMakeVisible(rxgui.get());
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 500);
}

ReaXstreamAudioProcessorEditor::~ReaXstreamAudioProcessorEditor()
{
    rxgui.reset();
}

//==============================================================================
void ReaXstreamAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);

}

void ReaXstreamAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
