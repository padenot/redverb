#include "Impulse.h"
#include "includes.h"

using namespace juce;

Impulse::Impulse(String path)
:needsProcessing(false)
{
	File theFile(path);
	FileInputStream* stream = theFile.createInputStream();
	WavAudioFormat audioFormat;
	AudioFormatReader* audioFormatReader = audioFormat.createReaderFor(stream, false);
	internalBufferOriginal = new AudioSampleBuffer(audioFormatReader->numChannels,audioFormatReader->lengthInSamples ); // FIXME
	internalBuffer = new AudioSampleBuffer(*internalBufferOriginal);
//	internalBuffer = new AudioSampleBuffer(*internalBufferOriginal);
	delete stream;
	delete audioFormatReader;
}

Impulse::~Impulse(void)
{
	delete internalBuffer;
	delete internalBufferOriginal;
	delete internalBufferBackup;
}



float** Impulse::GetRawData(int channel)
{
	if(needsProcessing)
	{
		applyFilters();
		needsProcessing = false;
	}
	if(channel == 0) // means the user wants all the channels
		return internalBuffer->getArrayOfChannels();
	else
		return &(internalBuffer->getArrayOfChannels()[channel]);
}

float** Impulse::GetRawDataUnprocessed(int channel)
{
	if(channel == 0) // means the user wants all the channels
		return internalBufferOriginal->getArrayOfChannels();
	else
		return &(internalBufferOriginal->getArrayOfChannels()[channel]);
}

double Impulse::Normalize(float gain)
{
	// The minimum value of the current channel
	float min;
	// The maximum value of the current channel
	float max;
	// The gain finally applied to the buffers
	float gainToApply = 0;
	// The maximum value of the buffer after the normalization
	float maxValueAfterNormalization = (1.0f-gain);

	for(int i = 0; i < internalBuffer->getNumChannels(); ++i)
	{
		internalBuffer->findMinMax(i,0,internalBuffer->getNumSamples(),min, max);
		
		float normalizationGain = maxValueAfterNormalization / max;

		// Get the lower normalization possible to prevent clipping.
		if(gainToApply < normalizationGain)
			gainToApply =  normalizationGain; 
	}

	// Apply the gain
	for(int i = 0; i < internalBuffer->getNumChannels(); ++i)
		internalBuffer->applyGain(0, internalBuffer->getNumChannels(), gainToApply);

	// return the gain applied, to show the value.
	return gainToApply;
}

void Impulse::applyFilters()
{
	// For the moment, all the processing are recomputed from
	// the original impulse. This has to be lazy evaluated, 
	// in the future.

	// Swap the buffers
	AudioSampleBuffer* tmp = internalBufferBackup;
	internalBufferBackup = internalBuffer;
	internalBuffer = tmp;

	for(int i = 0; i < internalBufferOriginal->getNumChannels(); ++i)
		internalBuffer->copyFrom(i, 0, *internalBufferOriginal, i, 0, internalBufferOriginal->getNumSamples());

	float** data = internalBuffer->getArrayOfChannels();

	// Reverse
	if(isReversed)
	{
		
		float tmp;
		int numSamples = internalBuffer->getNumSamples();
		for(int channel = 0; channel < internalBuffer->getNumChannels() ; ++channel)
		{
			for(int i = 0; i < numSamples / 2 ; ++i)
			{
				tmp = data[channel][i];
				data[channel][i] = data[channel][numSamples - i - 1]; 
				data[channel][numSamples - i - 1] = tmp;
			}
		}
	}		

	// ADSR :
	for(int channel = 0; channel < internalBuffer->getNumChannels() ; ++channel)
	{
		// Attack
		internalBuffer->applyGainRamp(channel, 0, attackTime, 0.0, attack); 
		// Decay
		internalBuffer->applyGainRamp(channel, attackTime+1, decayTime - attackTime, attack, decay); 
		// Sustain
		internalBuffer->applyGainRamp(channel, decayTime+1, sustainTime - decayTime, decay, sustain);
		// Release (constant Gain)
		internalBuffer->applyGainRamp(channel, sustainTime+1, releaseTime - sustainTime, sustain, sustain);
		// Decay
		internalBuffer->applyGainRamp(channel, releaseTime+1, internalBuffer->getNumSamples(), sustain, 0.0f);
	}
}
