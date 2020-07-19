/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FiltersProjectAudioProcessor::FiltersProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr)
#endif
{
    NormalisableRange<float> cutoffRange(20.0f, 20000.0f);
    NormalisableRange<float> resRange(1.0f, 5.0f);
    NormalisableRange<float> filterMenuRange(0, 2);

    tree.createAndAddParameter("cutoff", "Cutoff", "cutoff", cutoffRange, 600.0f, nullptr, nullptr);
    tree.createAndAddParameter("resonance", "Resonance", "resonance", resRange, 1.0f, nullptr, nullptr);

    tree.createAndAddParameter("filterMenu", "FilterMenu", "filterMenu", filterMenuRange, 0, nullptr, nullptr);
    

}

FiltersProjectAudioProcessor::~FiltersProjectAudioProcessor()
{
}

//==============================================================================
const String FiltersProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FiltersProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FiltersProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FiltersProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FiltersProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FiltersProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FiltersProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FiltersProjectAudioProcessor::setCurrentProgram (int index)
{
}

const String FiltersProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void FiltersProjectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FiltersProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;
    dsp::ProcessSpec spec;
    spec.sampleRate = lastSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getMainBusNumOutputChannels();
    stateVariableFilter.reset();
    updateFilter();
    stateVariableFilter.prepare(spec);
}

void FiltersProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void FiltersProjectAudioProcessor::updateFilter()
{
    int menuChoice = *tree.getRawParameterValue("filterMenu");
    int cutOff = *tree.getRawParameterValue("cutoff");
    int res = *tree.getRawParameterValue("resonance");

    if (menuChoice == 0)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, cutOff, res);
    }

    if (menuChoice == 1)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, cutOff, res);
    }

    if (menuChoice == 2)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, cutOff, res);
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FiltersProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void FiltersProjectAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    dsp::AudioBlock<float> block(buffer);
    updateFilter();
    stateVariableFilter.process(dsp::ProcessContextReplacing<float>(block));
}

//==============================================================================
bool FiltersProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FiltersProjectAudioProcessor::createEditor()
{
    return new FiltersProjectAudioProcessorEditor (*this);
}

//==============================================================================
void FiltersProjectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FiltersProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FiltersProjectAudioProcessor();
}
