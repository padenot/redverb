#include "Impulse.h"
#include "includes.h"

using namespace juce;

Impulse::Impulse(String path)
{
	File theFile(path);
	FileInputStream* stream = theFile.createInputStream();
	WavAudioFormat audioFormat;
	AudioFormatReader* audioFormatReader = audioFormat.createReaderFor(stream, false);
	internalBuffer = new AudioSampleBuffer(audioFormatReader->numChannels,audioFormatReader->lengthInSamples ); // FIXME
}

Impulse::~Impulse(void)
{
}
