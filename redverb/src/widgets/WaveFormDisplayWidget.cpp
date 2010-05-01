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
#include "WaveFormDisplayWidget.h"

#define max(a,b) (((a)>(b)?(a):(b) ))
#define min(a,b) (((a)<(b)?(a):(b) ))

#define PI 3.14159265



//==============================================================================
WaveFormDisplayWidget::WaveFormDisplayWidget (Component* theParent, int width, int height, Colour c, int x, int y )
:parent(theParent), color(c)
{
    setBounds(x,y,width,height);
    sampleCount = width-10;
  	dataForPreview = 0;


}

WaveFormDisplayWidget::WaveFormDisplayWidget (const WaveFormDisplayWidget& other)

{
	parent = other.GetParent();
	setBounds(other.getX(),other.getY(),other.getWidth(),other.getHeight());
	sampleCount = other.GetSampleCount();


	dataForPreview = new float[sampleCount];


	for(int i = 0; i<sampleCount; i++)
		dataForPreview[i] = other.GetDataForPreview()[i];


}

WaveFormDisplayWidget::~WaveFormDisplayWidget()
{
	delete[] dataForPreview;

}


//==============================================================================
void WaveFormDisplayWidget::paint (Graphics& g)
{
	/*g.setColour(color);
	for(int i = 0; i < sampleCount; i++)
		g.drawVerticalLine(i + 5, (float) GainToPixel(dataForPreview[i]) , (float) GainToPixel(0));
	*/
	


}

void WaveFormDisplayWidget::resized()
{
	//nothing to do
}

//==============================================================================

/** set the waveforme to display */
void WaveFormDisplayWidget::SetRawWaveForm(float** waveForm, int sizeInSamples)  {
	
	if(sizeInSamples == 0) { //default case! set default values for testing purpose
		sizeInSamples = 4096;
		waveForm = new float*[2];
		waveForm[0] = new float[4096];
		waveForm[1] = new float[4096];
		for(int i = 0; i<sizeInSamples;i++){
			waveForm[0][i] = sin (2*PI*i/(sizeInSamples/4));
			waveForm[1][i] = sin (2*PI*i/(sizeInSamples/4));
		}
	}


	if( !dataForPreview ){//already have an impulse loaded, forget it
		delete[] dataForPreview;
	}

	int ratio = sizeInSamples / sampleCount ;

	dataForPreview = new float[sampleCount] ;
	
	for (int i = 0; i < sampleCount; i++){
		dataForPreview[i] = 0;
		for (int j = 0; j < ratio ; j++){
			if (  waveForm[0][i*ratio+j] > 0)
				dataForPreview[i] = max ( dataForPreview[i] , waveForm[0][i*ratio+j] );
			else
				dataForPreview[i] = max ( dataForPreview[i] , -waveForm[0][i*ratio+j] );

			if (  waveForm[1][i*ratio+j] > 0)
				dataForPreview[i] = max ( dataForPreview[i] , waveForm[1][i*ratio+j] );
			else
				dataForPreview[i] = max ( dataForPreview[i] , -waveForm[1][i*ratio+j] );
		}
	}
}

/** set the new preview samples to display */
void WaveFormDisplayWidget::SetDataForPreview(float* someData, int sizeInSample) {

	if (sizeInSample){
		if( dataForPreview ){
			delete[] dataForPreview;
			dataForPreview = new float[sizeInSample];
		}		

		for(int i= 0; i < sizeInSample; i++)
			dataForPreview[i] = someData[i];
			
	}


}





//==============================================================================

