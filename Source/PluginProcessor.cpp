/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "ACME4Editor.h"

#define TICKSPEED 16.0
#define TICKLENGTH 25.0

//==============================================================================
Acme4v2AudioProcessor::Acme4v2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    lastPosInfo.resetToDefault();
}

Acme4v2AudioProcessor::~Acme4v2AudioProcessor()
{
}

//==============================================================================
const String Acme4v2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Acme4v2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Acme4v2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Acme4v2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Acme4v2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Acme4v2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Acme4v2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Acme4v2AudioProcessor::setCurrentProgram (int index)
{
}

const String Acme4v2AudioProcessor::getProgramName (int index)
{
    return {};
}

void Acme4v2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Acme4v2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Acme4v2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Acme4v2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Acme4v2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    static bool isPaused = true;
    static double lastBeat4thPos = 0.0;

    // ask the host for the current time so we can display it...
    AudioPlayHead::CurrentPositionInfo newTime;
    
    if (getPlayHead() != 0 && getPlayHead()->getCurrentPosition (newTime))
    {
        // Successfully got the current time from the host..
        lastPosInfo = newTime;
    }
    else
    {
        // If the host fails to fill-in the current time, we'll just clear it to a default..
        lastPosInfo.resetToDefault();
    }
    
    if (newTime.isPlaying || newTime.isRecording) {
        
        const double beats16th  = fmod (newTime.ppqPosition, 1.0/(TICKSPEED/4.0)) / (1.0/(TICKSPEED/4.0));
        
        // wait until we reach the beginning of the next 1/4 beat
        isPaused &= !(newTime.ppqPosition <= lastBeat4thPos);
        
        if (!isPaused)
        {
            const double smpsPer16th = ((60.0/newTime.bpm)*getSampleRate())/(TICKSPEED/4.0);
            double smpsFrom16th = beats16th*smpsPer16th-getLatencySamples();
            
            const double pulseSmpLength = TICKLENGTH/1000.0*getSampleRate();
            
            while (smpsFrom16th<0 ) smpsFrom16th+=smpsPer16th;
            
            if (totalNumInputChannels>0) {
                double smpCount = smpsFrom16th;
                
                if (smpsPer16th>0) {
                    auto* channelData = buffer.getWritePointer (0);
                    
                    for (int i = 0; i < buffer.getNumSamples(); ++i)
                    {
                        const double modCount = fmod(smpCount,smpsPer16th);
                        
                        if (modCount<pulseSmpLength) {
                            channelData[i] = +1.0;
                        } else {
                            channelData[i] = 0.0f;
                        }
                        
                        smpCount+=1;
                        
                    }
                    
                }
                
                for (int channel = 1; channel < totalNumInputChannels; ++channel)
                {
                    auto* firstChannelData = buffer.getWritePointer (0);
                    float* channelData = buffer.getWritePointer (channel);
                    
                    for (int i = 0; i < buffer.getNumSamples(); ++i)
                    {
                        channelData[i] = firstChannelData[i];
                    }
                    
                }
            }
        }
        
    } else {
        for (int i = 0; i < totalNumInputChannels; ++i)
            buffer.clear (i, 0, buffer.getNumSamples());
        isPaused = true;
        lastBeat4thPos = newTime.ppqPosition;
    }
    
    isPaused &= (newTime.isPlaying || newTime.isRecording);

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
}

//==============================================================================
bool Acme4v2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Acme4v2AudioProcessor::createEditor()
{
    return new ACME4Editor (*this);
}

//==============================================================================
void Acme4v2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Acme4v2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Acme4v2AudioProcessor();
}
