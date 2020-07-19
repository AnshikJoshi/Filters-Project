/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FiltersProjectAudioProcessorEditor::FiltersProjectAudioProcessorEditor (FiltersProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 200);

    filterMenu.setJustificationType(Justification::centred);
    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 2);
    filterMenu.addItem("Band Pass", 3);
    addAndMakeVisible(&filterMenu);

    filterCutoffDail.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutoffDail.setRange(20.0f, 20000.0f);
    filterCutoffDail.setValue(600.0f);
    filterCutoffDail.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterCutoffDail.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterCutoffDail);

    filterResDail.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterResDail.setRange(1.0f, 5.0f);
    filterResDail.setValue(2.0f);
    filterResDail.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterResDail.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterResDail);

    filterCutoffValue = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "cutoff", filterCutoffDail);
    filterResValue = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "resonance", filterResDail);
    filterMenuChoice = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "filterMenu", filterMenu);

    filterCutoffDail.setSkewFactorFromMidPoint(1000.0f);
    

    getLookAndFeel().setColour(Slider::rotarySliderFillColourId, Colours::grey);
    getLookAndFeel().setColour(Slider::thumbColourId, Colours::lightgrey);

}

FiltersProjectAudioProcessorEditor::~FiltersProjectAudioProcessorEditor()
{
}

//==============================================================================
void FiltersProjectAudioProcessorEditor::paint (Graphics& g)
{
    Rectangle<int> titleArea(0, 10, getWidth(), 20);
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText("Filter", titleArea, Justification::centredTop);
    g.drawText("Cutoff", 46, 70, 50, 25, Justification::centredLeft);
    g.drawText("Resonance", 107, 70, 70, 25, Justification::centredLeft);
    Rectangle<float> area(25, 25, 150, 150);
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
   

}

void FiltersProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    Rectangle<int> area = getLocalBounds().reduced(40);

    filterMenu.setBounds(area.removeFromTop(20));
    filterCutoffDail.setBounds(30, 90, 70, 70);
    filterResDail.setBounds(100, 90, 70, 70);
}
