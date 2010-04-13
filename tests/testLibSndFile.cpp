#include <sndfile.h>
#include <iostream>
#include <cstdio>


using namespace std;

void process(double *in, double *out, int count)

{
	const int DELAY = 10;
	double feedback = 0.5;
	int cursor = 0;
	double buffer[DELAY] = {0};
	while(--count >= 0)
	{
		double x = *in++;
		double y = buffer[cursor];
		buffer[cursor++] = x + y * feedback;
		if (cursor >= DELAY)
			cursor = 0;
		*out++ = y;
	}
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cerr << "Usage : " << argv[0] << " input.wav output.wav" << endl;
		return EXIT_FAILURE;
	}
	SF_INFO infos;
	SNDFILE *file = sf_open(argv[1], SFM_READ, &infos);
	if (file == NULL)
	{
		cerr << sf_strerror(file) << endl;
		return EXIT_FAILURE;
	}
	// Création du fichier de sortie
	// Fichier wav au format PCM 16 bits, mono et de fréquence d'échantillonage 44100
	SF_INFO infosWrite;
	infosWrite.samplerate = 44100;
	infosWrite.channels = 1;
	infosWrite.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
	if (sf_format_check(&infosWrite) == 0)
	{
		cerr << "Error while checking output file format." << endl;
		return EXIT_FAILURE;
	}
	SNDFILE *fileToWrite = sf_open(argv[2], SFM_WRITE, &infosWrite);
	if (fileToWrite == NULL)
	{
		cerr << sf_strerror(fileToWrite) << endl;
		return EXIT_FAILURE;
	}
	// Buffers
	int countFrames = infos.frames;
	double *in = new double[countFrames * infos.channels];
	double *out = new double[countFrames];
	// Traitement
	sf_count_t count = sf_readf_double(file, in, countFrames);
	process(in, out, countFrames);
	sf_close(file);
	// Ecriture dans le fichier de sortie
	sf_count_t countWrite = sf_writef_double(fileToWrite, out, countFrames);
	if (countWrite != countFrames)
		cerr << "Error while writing samples: " << countWrite << " written instead of " << countFrames << endl;
	if (sf_close(fileToWrite) != 0)
		cerr << "Error while closing the file." << endl;
	delete[] in;
	delete[] out;
	return EXIT_SUCCESS;
}

