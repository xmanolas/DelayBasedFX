/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CmDelayLinesAudioProcessorEditor::CmDelayLinesAudioProcessorEditor (CmDelayLinesAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{

    //Initialise plugin window
    setSize (400, 300);
    setResizable(false, false);

    //Initialise dryWet Slider
    dryWetSlider.setRange(0.0f, 1.0f);
    dryWetSlider.setValue(0.5f);
    dryWetSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    dryWetSlider.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    dryWetSlider.setColour(0x1001700, Colours::black);
    dryWetSlider.addListener(this);
    addAndMakeVisible(&dryWetSlider);
    
    //Initialise dryWet Label
    dryWetLabel.setText("Dry / Wet", dontSendNotification);
    dryWetLabel.setJustificationType(Justification::horizontallyCentred);
    dryWetLabel.setColour(juce::Label::textColourId, Colours::grey);
    dryWetLabel.attachToComponent(&dryWetSlider, false);
    
    
    // Ignore this - for testing purposes
    //startTimer(100);
    
}

CmDelayLinesAudioProcessorEditor::~CmDelayLinesAudioProcessorEditor()
{
    
}

//==============================================================================

void CmDelayLinesAudioProcessorEditor::paint (Graphics& g)
{
    // Set Background colour and font
    g.fillAll (Colours::black);
    g.setColour (Colours::white);
    g.setFont (20.0f);
    //g.drawText ((std::to_string(processor.dcBpm)), getLocalBounds(), Justification::centred, true);
}

void CmDelayLinesAudioProcessorEditor::resized()
{
    // Set Slider and Label position and size
    dryWetLabel.setBounds(0, 0, 40, 20);
    dryWetSlider.setBounds(((getWidth() / 2) -  (getWidth() / 2) / 2), ((getHeight() / 2) -  (getHeight() / 2) / 2), getWidth() / 2, getHeight() / 2);
}

void CmDelayLinesAudioProcessorEditor::sliderValueChanged (Slider *slider)
{
    // Send slider values to Plugin processor variables
    if (slider == &dryWetSlider)
    {
        processor.dryWetAmount = dryWetSlider.getValue();
    }
}

