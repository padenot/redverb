#include "verb.h"

//-------------------------------------------------------------------------------------------------------
AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return new Verb (audioMaster);
}

//-------------------------------------------------------------------------------------------------------
Verb::Verb (audioMasterCallback audioMaster)
: AudioEffectX (audioMaster, 1, 1)	// 1 program, 1 parameter only
{
	setNumInputs (2);		// stereo in
	setNumOutputs (2);		// stereo out
	setUniqueID ('verb');	// identify
	canProcessReplacing();	// supports replacing output
	canDoubleReplacing();	// supports double precision processing

	fGain = 1.f;			// default to 0 dB
	vst_strncpy (programName, progName, kVstMaxProgNameLen);	// default program name
}

//-------------------------------------------------------------------------------------------------------
Verb::~Verb ()
{
}

//-------------------------------------------------------------------------------------------------------
void Verb::setProgramName (char* name)
{
	vst_strncpy (programName, name, kVstMaxProgNameLen);
}

//-----------------------------------------------------------------------------------------
void Verb::getProgramName (char* name)
{
	vst_strncpy (name, programName, kVstMaxProgNameLen);
}

//-----------------------------------------------------------------------------------------
void Verb::setParameter (VstInt32 index, float value)
{
	fGain = value;
}

//-----------------------------------------------------------------------------------------
float Verb::getParameter (VstInt32 index)
{
	return fGain;
}

//-----------------------------------------------------------------------------------------
void Verb::getParameterName (VstInt32 index, char* label)
{
	vst_strncpy (label, "Gain", kVstMaxParamStrLen);
}

//-----------------------------------------------------------------------------------------
void Verb::getParameterDisplay (VstInt32 index, char* text)
{
	dB2string (fGain, text, kVstMaxParamStrLen);
}

//-----------------------------------------------------------------------------------------
void Verb::getParameterLabel (VstInt32 index, char* label)
{
	vst_strncpy (label, "dB", kVstMaxParamStrLen);
}

//------------------------------------------------------------------------
bool Verb::getEffectName (char* name)
{
	vst_strncpy (name, "Gain", kVstMaxEffectNameLen);
	return true;
}

//------------------------------------------------------------------------
bool Verb::getProductString (char* text)
{
	vst_strncpy (text, "Gain", kVstMaxProductStrLen);
	return true;
}

//------------------------------------------------------------------------
bool Verb::getVendorString (char* text)
{
	vst_strncpy (text, "Steinberg Media Technologies", kVstMaxVendorStrLen);
	return true;
}

//-----------------------------------------------------------------------------------------
VstInt32 Verb::getVendorVersion ()
{ 
	return 1000; 
}

//-----------------------------------------------------------------------------------------
void Verb::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

    while (--sampleFrames >= 0)
    {
        (*out1++) = (*in1++) * fGain;
        (*out2++) = (*in2++) * fGain;
    }
}

//-----------------------------------------------------------------------------------------
void Verb::processDoubleReplacing (double** inputs, double** outputs, VstInt32 sampleFrames)
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];
	double dGain = fGain;

    while (--sampleFrames >= 0)
    {
        (*out1++) = (*in1++) * dGain;
        (*out2++) = (*in2++) * dGain;
    }
}
