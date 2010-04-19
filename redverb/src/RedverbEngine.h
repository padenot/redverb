/**
 *  This file is part of RedVerb.
 *
 *  RedVerb is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of
 *  the License, or (at your option) any later version.
 *
 *  RedVerb is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with RedVerb.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef REDVERBENGINE_H
#define REDVERBENGINE_H


//==============================================================================
/**
 * @brief Not yet a convolution engine, but a nice delay effect :p
 */
class RedverbEngine  : public AudioProcessor,
                        public ChangeBroadcaster
{
public:
    //==============================================================================
    RedverbEngine();
    ~RedverbEngine();

    //==============================================================================
    /**
	 * @brief Called juste before the playback starts.
	 */
	void prepareToPlay (double sampleRate, int samplesPerBlock);
	/**
	 * @brief Called just after the playback stops.
	 */
    void releaseResources();

	/**
	 * @brief The method that process the audio.
	 *
	 * @param buffer The audio buffer.
	 * @param midiMessages The midi events.
	 */
    void processBlock (AudioSampleBuffer& buffer,
                       MidiBuffer& midiMessages);

    //==============================================================================
	/**
	 * @brief Creates the GUI.
	 */
    AudioProcessorEditor* createEditor();

    //==============================================================================
    /**
	 * @brief Accessor for the name of the plugin.
	 */
	const String getName() const;

	/**
	 * @brief Get the number of parameters.
	 */
    int getNumParameters();

	/**
	 * @brief Get the value of the parameter.
	 * @param index Use the enum provided.
	 */
    float getParameter (int index);
	/**
	 * @brief Set the value of a parameter.
	 * @param index Use the enum provided.
	 * @param newValue The new value for this param.
	 */
    void setParameter (int index, float newValue);

	/**
	 * @brief Get the name of the parameter
	 * @param index Use the enum provided.
	 */
    const String getParameterName (int index);
    /**
	 * @brief Get the value of the parameter (in text).
	 * @param index Use the enum provided.
	 */
    const String getParameterText (int index);

    const String getInputChannelName (const int channelIndex) const;
    const String getOutputChannelName (const int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;

    //==============================================================================
    int getNumPrograms()                                        { return 0; }
    int getCurrentProgram()                                     { return 0; }
    void setCurrentProgram (int index)                          { }
    const String getProgramName (int index)                     { return String::empty; }
    void changeProgramName (int index, const String& newName)   { }

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    AudioPlayHead::CurrentPositionInfo lastPosInfo;

    // these are used to persist the UI's size - the values are stored along with the
    // filter's other parameters, and the UI component will update them when it gets
    // resized.
    int lastUIWidth, lastUIHeight;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    /// The gain.
    float gain;
	/// The feedback.
	float feedback;
	/// The delay, in ms
	float delay;
	/// The dryGain
	float dryGain;
	/// The wetGain
	float wetGain;




	/// The delay buffer
	float* accBuffer;
	/// The delay cursor
	long cursor;
	/// The delay, in samples
	long bufferSize;

	

	/// The logger !
	FileLogger* log;
};


#endif
