#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Impulse.h"

int Impulse::ms2int(int ms)
{
	return static_cast<int>((ms/1000.) * samplingFrequency);
}

int Impulse::applyADSR()
{
    //Linera version
    int i;
    for(i=0;i<attack;++i)
	treatedBuffer[i] = i * originalBuffer[i];
    for(i++;i<decay;++i)
	treatedBuffer[i] = -i * originalBuffer[i];
    for(i=release++;i<length;++i)
	treatedBuffer[i] = -i * originalBuffer[i];
}
