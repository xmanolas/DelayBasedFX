/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include <string>

//==============================================================================
/**
*/
class CmDelayLinesAudioProcessorEditor  : public AudioProcessorEditor , public Slider::Listener,  public Button::Listener, private Timer
{
public:
    CmDelayLinesAudioProcessorEditor (CmDelayLinesAudioProcessor&);
    ~CmDelayLinesAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider *slider) override;
    void buttonClicked (Button *buttonThatWasClicked) override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
   
    CmDelayLinesAudioProcessor& processor;
    
    // private declarations
    Slider dryWetSlider;
    Slider delayTimeSlider;
    Label dryWetLabel;
    Label delayTimeLabel;
    Label delayLabel;
    TextButton dcDelayOnOff;
    LookAndFeel_V4 dcButtonLookAndFeel;
    
   

    
    void timerCallback () override
    {
        //dryWetLabel.setText(std::to_string(processor.dcBpm), dontSendNotification);
        //repaint();
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CmDelayLinesAudioProcessorEditor)
};

