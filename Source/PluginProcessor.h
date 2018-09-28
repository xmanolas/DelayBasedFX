/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class CmDelayLinesAudioProcessor  : public AudioProcessor

{
public:
    //==============================================================================
    CmDelayLinesAudioProcessor();
    ~CmDelayLinesAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //=============================== DC ===========================================
   
    
    void dcFillBuffer (int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);
    void dcGetBuffer (AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);
    void dcGetInverseBuffer (AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);
    void dcModulator (AudioBuffer<float>& buffer, int dcModFreq);
    
    double dcBpm;
    bool dcIsLoop;
    bool dcDelayOnOffState = true;
    float dcDelayTime = 1.0f;
    float dryWetAmount;
    

private:
    //==============================================================================
    
    AudioBuffer<float> dcBuffer;
    int dcBpmFrag = 0;
    int bufferWritePos = 0;
    double dcSampleRate = 44100;
    double dcCurrentAngle = 0.0;
    double dcAngleDelta = 0.0;
    int x = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CmDelayLinesAudioProcessor)
};
