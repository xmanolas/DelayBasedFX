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

    //Initialise dryWet slider
    dryWetSlider.setRange(0.0f, 1.0f);
    dryWetSlider.setValue(0.5f);
    dryWetSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    dryWetSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    dryWetSlider.setColour(0x1001700, Colours::black);
    dryWetSlider.addListener(this);
    addAndMakeVisible(&dryWetSlider);
    dryWetLabel.setText("Dry / Wet", dontSendNotification);
    //dryWetLabel.attachToComponent(&dryWetSlider, true);
    startTimer(100);
    
}

CmDelayLinesAudioProcessorEditor::~CmDelayLinesAudioProcessorEditor()
{
    
}

//==============================================================================

void CmDelayLinesAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);
    g.setColour (Colours::white);
    g.setFont (20.0f);
    g.drawText ((std::to_string(processor.dcBpm)), getLocalBounds(), Justification::centred, true);
}

void CmDelayLinesAudioProcessorEditor::resized()
{
    dryWetLabel.setBounds(20, 20, 100, 200);
    dryWetSlider.setBounds(60, getHeight() - 60, getWidth() - 80, 30);
}

void CmDelayLinesAudioProcessorEditor::sliderValueChanged (Slider *slider)
{
    // Sent slider values to Plugin processor variables
    if (slider == &dryWetSlider)
    {
        processor.dryWetAmount = dryWetSlider.getValue();
    }
}

