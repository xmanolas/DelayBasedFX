/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CmDelayLinesAudioProcessor::CmDelayLinesAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ) ,
                    dryWetAmount(0.5f)

#endif
{
}

CmDelayLinesAudioProcessor::~CmDelayLinesAudioProcessor()
{
}

//==============================================================================

const String CmDelayLinesAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CmDelayLinesAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CmDelayLinesAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CmDelayLinesAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CmDelayLinesAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CmDelayLinesAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CmDelayLinesAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CmDelayLinesAudioProcessor::setCurrentProgram (int index)
{
}

const String CmDelayLinesAudioProcessor::getProgramName (int index)
{
    return {};
}

void CmDelayLinesAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==================================PREP TO PLAY======================================


void CmDelayLinesAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Set delay buffer size
    dcSampleRate = sampleRate;
    dcSamplesPerBlock = samplesPerBlock;
    dcSetBufferSize();
}

void CmDelayLinesAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CmDelayLinesAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


//==================================== PROCESS BLOCK ===============================

void CmDelayLinesAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    
    // Read Playhead info
    AudioPlayHead::CurrentPositionInfo myCurPos;
    getPlayHead()->getCurrentPosition(myCurPos);
    dcBpm = myCurPos.timeInSeconds;
    
    // Get number of channels
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Get length of buffer and cmBuffer
    const int bufferLength = buffer.getNumSamples();
    const int dcBufferLength = dcBuffer.getNumSamples();
    
    // Fill and read delay buffer
    if (dcDelayOnOffState == true)
    {
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            const float* bufferData = buffer.getReadPointer(channel);
            const float* dcBufferData = dcBuffer.getReadPointer(channel);
            
            //Use Buffer-related functions for processing
            dcFillBuffer(channel, bufferLength, dcBufferLength, bufferData, dcBufferData);
            //dcGetInverseBuffer(buffer, channel, bufferLength, dcBufferLength, bufferData, dcBufferData);
            dcGetBuffer(buffer, channel, bufferLength, dcBufferLength, bufferData, dcBufferData);
        }
    
    // Buffer write position wrap
    bufferWritePos += buffer.getNumSamples();
    bufferWritePos %= dcBuffer.getNumSamples();
    }
    
}

//================================ PROCESS BLOCK END ===============================


void CmDelayLinesAudioProcessor::dcSetBufferSize ()
{
    // Set delay buffer size
    const int numInputChannels = getTotalNumInputChannels();
    const int delayBufferSize = dcDelayTime * (dcSampleRate + dcSamplesPerBlock);
    dcBuffer.setSize(numInputChannels, delayBufferSize, false, true, true);
}

void CmDelayLinesAudioProcessor::dcFillBuffer (int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
   
    // Copy data from main buffer to delay buffer
    if (delayBufferLength > bufferLength + bufferWritePos)
    {
        dcBuffer.copyFromWithRamp(channel, bufferWritePos, bufferData, bufferLength, dryWetAmount, dryWetAmount);
    }
    else
    {
        const int bufferRemaining = delayBufferLength - bufferWritePos;
        dcBuffer.copyFromWithRamp(channel, bufferWritePos, bufferData, bufferRemaining, dryWetAmount, dryWetAmount);
        dcBuffer.copyFromWithRamp(channel, 0, bufferData, bufferLength - bufferRemaining, dryWetAmount, dryWetAmount);
    }
    
}

void CmDelayLinesAudioProcessor::dcGetBuffer (AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
    
    // Read data from delay buffer to main buffer
    int delayTime = dcDelayTime * 1000;
    const int bufferReadPos =  static_cast<int> (delayBufferLength + bufferWritePos - (dcSampleRate * delayTime /1000)) % delayBufferLength;
    
    if (delayBufferLength > bufferLength + bufferReadPos)
    {
        buffer.addFrom(channel, 0, delayBufferData + bufferReadPos, bufferLength);
    }
    else
    {
        const int bufferRemaining = delayBufferLength - bufferReadPos;
        buffer.addFrom(channel, 0, delayBufferData + bufferReadPos, bufferRemaining);
        buffer.addFrom(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining);
    }
    
}

void CmDelayLinesAudioProcessor::dcModulator (AudioBuffer<float>& buffer, int dcModFreq)
{
    //auto cyclesPerSample = frequencySlider.getValue() / dcSampleRate;
    //dcAngleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

void CmDelayLinesAudioProcessor::dcGetInverseBuffer (AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
    
    /*
    // Read data from delay buffer to main buffer
    int delayTime = 100;
    const int bufferReadPos =  static_cast<int> ((delayBufferLength - bufferWritePos + (dcSampleRate * delayTime /1000)) - bufferLength) % delayBufferLength;
    
    if (bufferReadPos > bufferLength)
    {
        
        buffer.copyFrom(channel, 0, delayBufferData + bufferReadPos, bufferLength);
        buffer.reverse(channel, 0, bufferLength);
    }
    else
    {
        const int bufferRemaining = bufferLength - (bufferLength - bufferReadPos);
        buffer.copyFrom(channel, 0, delayBufferData, bufferReadPos);
        buffer.copyFrom(channel, delayBufferLength - (bufferLength - bufferReadPos), delayBufferData, bufferLength - bufferReadPos);
        buffer.reverse(channel, 0, bufferLength);
    }
    */
}

//==============================================================================

bool CmDelayLinesAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CmDelayLinesAudioProcessor::createEditor()
{
    return new CmDelayLinesAudioProcessorEditor (*this);
}

//==============================================================================
void CmDelayLinesAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CmDelayLinesAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CmDelayLinesAudioProcessor();
}
