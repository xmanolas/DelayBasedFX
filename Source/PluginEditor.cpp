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

    
    //Initialise Delay On/Off Button
    dcDelayOnOff.setButtonText("Delay Off");
    dcDelayOnOff.setColour(juce::TextButton::ColourIds::textColourOffId, Colours::grey);
    dcDelayOnOff.setColour(juce::TextButton::ColourIds::textColourOnId, Colours::orange);
    dcDelayOnOff.setClickingTogglesState(true);
    dcDelayOnOff.setState(TextButton::ButtonState::buttonDown);
    dcDelayOnOff.addListener(this);
    addAndMakeVisible(&dcDelayOnOff);
    
    //Initialise Delay Time Slider
    delayTimeSlider.setRange(0.0f, 5.0f);
    delayTimeSlider.setValue(1.0f);
    delayTimeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    delayTimeSlider.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    delayTimeSlider.setColour(0x1001700, Colours::black);
    delayTimeSlider.addListener(this);
    addAndMakeVisible(&delayTimeSlider);
    
    //Initialise Delay Time Label
    delayTimeLabel.setText("Time", dontSendNotification);
    delayTimeLabel.setJustificationType(Justification::horizontallyCentred);
    delayTimeLabel.setColour(juce::Label::textColourId, Colours::grey);
    delayTimeLabel.attachToComponent(&delayTimeSlider, false);
    
    //Initialise Delay Dry/Wet Slider
    dryWetSlider.setRange(0.0f, 1.0f);
    dryWetSlider.setValue(0.5f);
    dryWetSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    dryWetSlider.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    dryWetSlider.setColour(0x1001700, Colours::black);
    dryWetSlider.addListener(this);
    addAndMakeVisible(&dryWetSlider);
    
    //Initialise Delay Dry/Wet Label
    dryWetLabel.setText("Dry/Wet", dontSendNotification);
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
    // Set Slider, Label and Button position and size
    dcDelayOnOff.setBounds(10, 30, 120, 25);
    dryWetLabel.setBounds(0, 0, 60, 20);
    dryWetSlider.setBounds(60, 90, 60, 100);
    delayTimeSlider.setBounds(10, 90, 60, 100);
    
}

void CmDelayLinesAudioProcessorEditor::sliderValueChanged (Slider *slider)
{
    // Send slider values to Plugin processor variables
    if (slider == &dryWetSlider)
    {
        processor.dryWetAmount = dryWetSlider.getValue();
    } else if (slider == &delayTimeSlider)
    {
        processor.dcDelayTime = delayTimeSlider.getValue();
    }
}

void CmDelayLinesAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //Set On/Off Button states
    if (buttonThatWasClicked == &dcDelayOnOff)
    {
        if (dcDelayOnOff.getButtonText() == "Delay Off")
        {
            dcDelayOnOff.setButtonText("Delay On");
            processor.dcDelayOnOffState = true;
            delayTimeLabel.setColour(juce::Label::textColourId, Colours::lightgrey );
            dryWetLabel.setColour(juce::Label::textColourId, Colours::lightgrey);
        } else
        {
            dcDelayOnOff.setButtonText("Delay Off");
            processor.dcDelayOnOffState = false;
            delayTimeLabel.setColour(juce::Label::textColourId, Colours::darkgrey);
            dryWetLabel.setColour(juce::Label::textColourId, Colours::darkgrey);
        }
    }


}
