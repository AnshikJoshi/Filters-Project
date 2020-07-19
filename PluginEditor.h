/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FiltersProjectAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    FiltersProjectAudioProcessorEditor (FiltersProjectAudioProcessor&);
    ~FiltersProjectAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    Slider filterCutoffDail;
    Slider filterResDail;
    ComboBox filterMenu;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterResValue;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterMenuChoice;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FiltersProjectAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FiltersProjectAudioProcessorEditor)
};
