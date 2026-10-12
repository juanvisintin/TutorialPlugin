/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TutorialPluginAudioProcessorEditor : public juce::AudioProcessorEditor,
    private juce::Slider::Listener
{
public:
    TutorialPluginAudioProcessorEditor (TutorialPluginAudioProcessor&);
    ~TutorialPluginAudioProcessorEditor();

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    void sliderValueChanged(juce::Slider* slider) override;

    TutorialPluginAudioProcessor& audioProcessor;

    juce::Slider midiVolume;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TutorialPluginAudioProcessorEditor)
};
