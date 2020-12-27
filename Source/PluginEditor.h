/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Plugdisto1AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Plugdisto1AudioProcessorEditor (Plugdisto1AudioProcessor&);
    ~Plugdisto1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Plugdisto1AudioProcessor& processor;

	ScopedPointer<Slider> driveKnob;
	ScopedPointer<Slider> rangeKnob;
	ScopedPointer<Slider> blendKnob;
	ScopedPointer<Slider> volumeKnob;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> volumeAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Plugdisto1AudioProcessorEditor)
};
