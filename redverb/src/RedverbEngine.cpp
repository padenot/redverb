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

#include "includes.h"
#include "redverbEngine.h"
#include "redverbGUI.h"


//==============================================================================
/**
 * This must be implemented to create a new instance of the effect.
 */
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RedverbEngine();
}

//==============================================================================
RedverbEngine::RedverbEngine()
{
    gain = 1.0f;
	feedback = 0.5f;
	delay = 300.0f;
	cursor = 0;//??what is that
	dryGain = 1.0f;
	wetGain= 1.0f;

    lastUIWidth = 400;
    lastUIHeight = 140;

    zeromem (&lastPosInfo, sizeof (lastPosInfo));
    lastPosInfo.timeSigNumerator = 4;
    lastPosInfo.timeSigDenominator = 4;
    lastPosInfo.bpm = 120;

	log = new FileLogger(File("C:\\log.log"), String("OPENING"));
	Logger::setCurrentLogger(log);
}

RedverbEngine::~RedverbEngine()
{
	delete log;
}

//==============================================================================
const String RedverbEngine::getName() const
{
    return "Redverb";
}

int RedverbEngine::getNumParameters()
{
    return 5;
}

float RedverbEngine::getParameter (int index)
{
	switch(index)
	{
		case 0:
			return gain;
		case 1:
			return feedback;
		case 2:
			return delay;
		case 3:
			return dryGain;
		case 4:
			return wetGain;
	}
}

void RedverbEngine::setParameter (int index, float newValue)
{
	switch(index)
	{
	case 0:
		if (gain != newValue)
		{
			gain = newValue;
			sendChangeMessage (this);		
		}
		break;
	case 1:
		if(feedback != newValue)
		{
			feedback = newValue;
			sendChangeMessage(this);
		
		}
			break;
	case 2:
		if(delay != newValue)
		{
			delay = newValue;
			sendChangeMessage(this);
		
		}
			break;
	case 3:
		if(dryGain != newValue)
		{
			dryGain = newValue;
		//	Logger::writeToLog("Dry gain change (engine) : " + String(dryGain,2));
			sendChangeMessage(this);
		
		}
			break;
	case 4:
		if(wetGain != newValue)
		{
			wetGain = newValue;
			sendChangeMessage(this);
		//	Logger::writeToLog("Wet gain change (engine) : " + String(wetGain,2));
		}
			break;
	}
}

const String RedverbEngine::getParameterName (int index)
{
	switch(index)
	{
	case 0:
        return T("gain");
	case 1:
		return T("fb");
	case 2:
		return T("delay");
	case 3:
		return T("dryGain");
	case 4:
		return T("wetGain");
	default:
		 return String::empty;
	}
   
}

const String RedverbEngine::getParameterText (int index)
{
	switch(index)
	{
	case 0:
        return String (gain, 2);
	case 1:
		return String (feedback, 2);
	case 2:
		return String (delay, 2);
	case 3:
		return String (dryGain, 0);
	case 4:
		return String (wetGain, 0);
	default:
		return String::empty;
	}
}

const String RedverbEngine::getInputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

const String RedverbEngine::getOutputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

bool RedverbEngine::isInputChannelStereoPair (int index) const
{
    return true;
}

bool RedverbEngine::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool RedverbEngine::acceptsMidi() const
{
    return false;
}

bool RedverbEngine::producesMidi() const
{
    return false;
}

//==============================================================================
void RedverbEngine::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	// Maybe replace this by a memset ?
	bufferSize = static_cast<long>(delay / 1000. * sampleRate);
	accBuffer = new float[bufferSize];
	for(long i = 0; i < bufferSize; ++i)
	{
		accBuffer[i] = 0;
	}
}

void RedverbEngine::releaseResources()
{
	delete accBuffer;
}

void RedverbEngine::processBlock (AudioSampleBuffer& buffer,
                                   MidiBuffer& midiMessages)
{
    // for each of our input channels, we'll attenuate its level by the
    // amount that our volume parameter is set to.

	for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        buffer.applyGain (channel, 0, buffer.getNumSamples(), gain);
    }

	// Actual delay code :
	int samples = buffer.getNumSamples();
	int channels = buffer.getNumChannels();

	float* in1 = buffer.getSampleData(0);

	while (--samples >= 0)
	{
		float x1 = *in1;
		float y1 = accBuffer[cursor];
		*in1 = accBuffer[cursor];
		in1++;
		accBuffer[cursor++] = x1 + y1 * feedback;
		if(cursor >= bufferSize)
			cursor = 0;
	}

    // in case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
AudioProcessorEditor* RedverbEngine::createEditor()
{
    return new RedverbGUI (this);
}

//==============================================================================
void RedverbEngine::getStateInformation (MemoryBlock& destData)
{
    // you can store your parameters as binary data if you want to or if you've got
    // a load of binary to put in there, but if you're not doing anything too heavy,
    // XML is a much cleaner way of doing it - here's an example of how to store your
    // params as XML..

    // create an outer XML element..
    XmlElement xmlState (T("MYPLUGINSETTINGS"));

    // add some attributes to it..
    xmlState.setAttribute (T("pluginVersion"), 1);
    xmlState.setAttribute (T("gainLevel"), gain);
    xmlState.setAttribute (T("uiWidth"), lastUIWidth);
    xmlState.setAttribute (T("uiHeight"), lastUIHeight);

    // you could also add as many child elements as you need to here..


    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xmlState, destData);
}

void RedverbEngine::setStateInformation (const void* data, int sizeInBytes)
{
    // use this helper function to get the XML from this binary blob..
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);

    if (xmlState != 0)
    {
        // check that it's the right type of xml..
        if (xmlState->hasTagName (T("MYPLUGINSETTINGS")))
        {
            // ok, now pull out our parameters..
            gain = (float) xmlState->getDoubleAttribute (T("gainLevel"), gain);

            lastUIWidth = xmlState->getIntAttribute (T("uiWidth"), lastUIWidth);
            lastUIHeight = xmlState->getIntAttribute (T("uiHeight"), lastUIHeight);

            sendChangeMessage (this);
        }

        delete xmlState;
    }
}
