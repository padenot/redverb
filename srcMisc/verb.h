#ifndef __VERB__H
#define __VERB__H

#include "public.sdk/source/vst2.x/audioeffectx.h"

const char* progName = "Verb";
class Verb : public AudioEffectX
{
public:
	Verb (audioMasterCallback audioMaster);
	~Verb ();

	// Processing
	virtual void processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames);
	virtual void processDoubleReplacing (double** inputs, double** outputs, VstInt32 sampleFrames);

	// Program
	virtual void setProgramName (char* name);
	virtual void getProgramName (char* name);

	// Parameters
	virtual void setParameter (VstInt32 index, float value);
	virtual float getParameter (VstInt32 index);
	virtual void getParameterLabel (VstInt32 index, char* label);
	virtual void getParameterDisplay (VstInt32 index, char* text);
	virtual void getParameterName (VstInt32 index, char* text);

	virtual bool getEffectName (char* name);
	virtual bool getVendorString (char* text);
	virtual bool getProductString (char* text);
	virtual VstInt32 getVendorVersion ();

protected:
	std::vector<Impulse> impulses;
	float fGain;
	char programName[kVstMaxProgNameLen + 1];
};

#endif
