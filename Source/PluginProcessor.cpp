/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Plugdisto1AudioProcessor::Plugdisto1AudioProcessor()
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
	state = new AudioProcessorValueTreeState(*this, nullptr);
	state->createAndAddParameter("drive", "Drive", "Drive", NormalisableRange<float>(0.0, 1.0, 0.0001), 1.0, nullptr, nullptr);
	state->createAndAddParameter("range", "Range", "Range", NormalisableRange<float>(0.0, 3000.0, 0.0001), 1.0, nullptr, nullptr);
	state->createAndAddParameter("blend", "Blend", "Blend", NormalisableRange<float>(0.0, 1.0, 0.0001), 1.0, nullptr, nullptr);
	state->createAndAddParameter("volume", "Volume", "Volume", NormalisableRange<float>(0.0, 8.0, 0.0001), 1.0, nullptr, nullptr);

	state->state = ValueTree("drive");
	state->state = ValueTree("range");
	state->state = ValueTree("blend");
	state->state = ValueTree("volume");


}

Plugdisto1AudioProcessor::~Plugdisto1AudioProcessor()
{
}

//==============================================================================
const String Plugdisto1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Plugdisto1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Plugdisto1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Plugdisto1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Plugdisto1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Plugdisto1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Plugdisto1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Plugdisto1AudioProcessor::setCurrentProgram (int index)
{
}

const String Plugdisto1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Plugdisto1AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Plugdisto1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Plugdisto1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Plugdisto1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Plugdisto1AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
	float drive = *state->getRawParameterValue("drive");
	float range = *state->getRawParameterValue("range");
	float blend = *state->getRawParameterValue("blend");
	float volume = *state->getRawParameterValue("volume");



    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

		for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
			
			//****pour clipper(je pense)****
				*channelData *= volume;//drive; //*range
				//*channelData = (2.0/ float_Pi)* atan(*channelData);//<<-- je pense que c est mieux de mettre le *volume ici avec le (*channelData * volume)

			//test sur les bornes du float
			if (*channelData <  -0.999f || *channelData > 0.999f) {
				if (*channelData < -0.999f) { *channelData = -0.999f; }
				if (*channelData > 0.999f) { *channelData = 0.999f; }

			}

			/*float cleanSig = *channelData;
			*channelData *= drive * range;
			*channelData = (((((2.0/ float_Pi)* atan(*channelData))*blend) + (cleanSig * (1.0 - blend)))/2.0) *volume;
			*/
			channelData++;
		}
    }
}

AudioProcessorValueTreeState& Plugdisto1AudioProcessor::getState() {
	return *state;
}


//==============================================================================
bool Plugdisto1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Plugdisto1AudioProcessor::createEditor()
{
    return new Plugdisto1AudioProcessorEditor (*this);
}

//==============================================================================
void Plugdisto1AudioProcessor::getStateInformation (MemoryBlock& destData)
{
	MemoryOutputStream stream(destData, false);
	state->state.writeToStream(stream);
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Plugdisto1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	ValueTree tree = ValueTree::readFromData(data, sizeInBytes);

	if (tree.isValid()) {
		state->state = tree;
	}
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Plugdisto1AudioProcessor();
}
