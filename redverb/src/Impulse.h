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

#ifndef IMPULSE_H
#define IMPULSE_H

#include "includes.h"



enum ImpulseParameters
{
	pStart,
	pEnd,
	pGain,
	pReverse,
	pAttack,
	pDecay,
	pSutain,
	pRelease,
	pAttackTime,
	pDecayTime,
	pSutainTime,
	pReleaseTime,
	pIsReversed,
	pIsADSREnabled,
	PARAM_COUNT
};

String ImpulseParameters_Strings[PARAM_COUNT] = 
{
	"pStart",
		"pEnd",
		"pGain",
		"pReverse",
		"pAttack",
		"pDecay",
		"pSutain",
		"pDecay",
		"pAttackTime",
		"pDecayTime",
		"pSutainTime",
		"pDecayTime",
		"pIsReversed",
		"pIsADSREnabled",
};

/**
 * @brief Container for an audio impulse.
 *
 * Container for an audio impulse, that is a short audio clip which
 * will be convolved with the input signal. This class handles
 * the effects that can be applied to an impulse : gain, ADSR filter
 * croping, and maybe EQ (which is not implemented at the moment).
 */
class Impulse
{

protected:
	/**
	 * @brief The audio buffer.
	 *
	 * This stores the actual data of the file loaded.
	 */
	AudioSampleBuffer* internalBuffer;
	
	/**
	 * The begining of the impulse, in samples.
	 */
	long start;
	/**
	 * The end of the impulse, in sample.
	 */
	long end;
	/**
	 * The values of the ADSR filter, in dB.
	 */
	float attack; ///< Attack, in dB.
	float decay; ///< Decay, in dB.
	float sustain; ///< Sustain, in dB.
	float release; ///< Release, in dB.
	/**
	 * The positions of the ADSR filter, in samples.
	 */
	long attackTime; ///< Attack time, in samples.
	long decayTime; ///< Decay time, in samples.
	long sustainTime; ///< Sustain time, in samples.
	long releaseTime; ///< Release time, in samples.
	/**
	 * Flag which is true if the impulse is reversed.
	 */
	bool isReversed;
	/**
	 * Flag which is true if the ADSR filter is enabled.
	 */
	bool isADSREnabled;
	/**
	 * Gain value, applied to the impulse.
	 *
	 * @see Normalize()
	 */
public:
	/**
	 * @brief Constructor. 
	 *
	 * This loads the file of path <path>.
	 *
	 * @param path The path of the file to be load.
	 */
	Impulse(String path = String());
	/**
	 * @brief Destructor.
	 */
	virtual ~Impulse();
	/**
	 * @brief Get the raw data.
	 *
	 * The array returned is processed by all the effects enabled.
	 * 
	 * @param channel The channel that has to be returned. Is channel == 0, all
	 *                will be returned.
	 * @return The raw data of the channel(s) specified.
	 */
	float** GetRawData(int channel = 0);
	/**
	 * @brief Get the raw data, unprocessed.
	 *
	 * The array returned corresponds to the internalBuffer values, 
	 * as if all the effects were turned off.
	 *
	 * @param channel The channel that has to be returned. Is channel == 0, all
	 *                will be returned.
	 * @return The raw data of the channel(s) specified.
	 */
	float** GetRawDataUnprocessed(int channel = 0);
	/**
	 * @brief Normalize the impulse.
	 *
	 * Applies a gain, in a way that the maximum value of the internalBuffer
	 * will be equal to gain.
	 *
	 * @param gain The headroom wanted, i.e. the value to normalize to
	 *	           This shall be a negative floating point number, and 
	 *			   is expressed id dB.
	 */
	double Normalize(float gain = 0.0f);
	/*********** Getters // Setters ************/
	long getStart()
	{
		return start;
	}

	void setStart(long value)
	{
		if(value >= 0 && value < end)
		{
			start = value;
		}
		else
		{
			Logger::writeToLog(String("unexpected negative value or greater than end")
							   + String(__LINE__)
							   + String(__FILE__)
							   );
		}
	}

	long getEnd()
	{
		return end;
	}

	void setEnd(long value)
	{
		if( (value > 0) && (value > start)		)
		{
			end = value;
		}
		else
		{
			Logger::writeToLog(String("unexpected negative value or lower than start ")
							   + String(__LINE__)
							   + String(__FILE__)
							   );
		}
	}

	float getAttack()
	{
		return attack;
	}

	float getDecay()
	{
		return decay;
	}

	float getSustain()
	{
		return sustain;
	}

	float getRelease()
	{
		return release;
	}

	void setAttack(float value)
	{
		if(value >= 0 && value <= 1)
			attack = value;
		else
		{
			Logger::writeToLog(String("unexpected negative value ")
							   + String(__LINE__)
							   + String(__FILE__)
							   );
		}
	}

	void setDecay(float value)
			{
		if(value >= 0 && value <= 1)
			decay = value;
		else
		{
			Logger::writeToLog(String("unexpected negative value ")
							   + String(__LINE__)
							   + String(__FILE__)
							   );
		}
	}
	void setSustain(float value)
	{
		if(value >= 0 && value <= 1)
			sustain = value;
		else
		{
			Logger::writeToLog(String("unexpected negative value ")
							   + String(__LINE__)
							   + String(__FILE__)
							   );
		}
	}
	void setRelease(float value)
	{
		if(value >= 0 && value <= 1)
			release = value;
		else
		{
			Logger::writeToLog(String("unexpected negative value ")
							   + String(__LINE__)
							   + String(__FILE__)
							   );
		}
	}
	long getAttackTime()
	{
		return attackTime;
	}
	long getDecayTime()
	{
		return decayTime;
	}

	long getSustainTime()
	{
		return sustainTime;
	}

	long getReleaseTime()
	{
		return releaseTime;
	}

	void setAttackTime(long value)
	{
		if(value >= 0)
			attackTime = value;
		else
		{
			Logger::writeToLog(String("unexpected negative value ")
							   + String(__LINE__)
							   + String(__FILE__)
							   );
		}
	}

	void setDecayTime(long value)
	{
		if(value >= 0 && value >= attackTime)
			decayTime = value;
		else
		{
			Logger::writeToLog(String("unexpected negative value ")
							   + String(__LINE__)
							   + String(__FILE__)
							   );
		}		
	}

	void setSustainTime(long value)
	{
		if(value >= 0 && value >= decayTime)
			sustainTime = value;
		else
		{
			Logger::writeToLog(String("unexpected negative value ")
							   + String(__LINE__)
							   + String(__FILE__)
							   );
		}		
	}
	void setReleaseTime(long value)
	{
		if(value >= 0 && value >= sustainTime)
			releaseTime = value;
		else
		{
			Logger::writeToLog(String("unexpected negative value ")
							   + String(__LINE__)
							   + String(__FILE__)
							   );
		}		
	}
	void setReversed(bool value)
	{
		isReversed = value;
	}

	bool getReversed()
	{
		return isReversed;
	}
	bool getADSREnabled()
	{
		return isADSREnabled;
	}
	void setADSREnabled(bool value)
	{
		isADSREnabled = value;
	}
};

#endif