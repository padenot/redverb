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

#ifndef WAVEFORMDISPLAYWIDGET_H
#define WAVEFORMDISPLAYWIDGET_H

//#include "redverbEngine.h"
//#include "RedverbLookAndFeel.h"
//#include "AdsrWidget.h"
//class AdsrWidget ;//WTF?!

const float MAXGAIN = 1.25f;

/**
 * @brief widget managing ADSR manipulations.
 *
 * This class handle the ADSR modification on the impulse. 
 */
class WaveFormDisplayWidget  : public Component
                              
{
public:



    /** Constructor.

        When created, this will register itself with the filter for changes. It's
        safe to assume that the filter won't be deleted before this object is.
    */
	WaveFormDisplayWidget (Component* theParent, int width, int heigt, Colour c,int x = 0, int y = 0);

	/** Copy Constructor. */
	WaveFormDisplayWidget (const WaveFormDisplayWidget& other);

    /** Destructor. */
    ~WaveFormDisplayWidget();





    //==============================================================================

	/** Obtain Parent */
	inline Component* GetParent() const {
		return parent;
	}

	/** Obtain sampleCount */
	inline int GetSampleCount() const {
		return sampleCount;
	}

	/** Obtain sampleCount */
	inline float* GetDataForPreview() const {
		return dataForPreview;
	}

	/** set the waveforme to display */
	void SetRawWaveForm(float** waveForm, int sizeInSamples = 0)  ;

	/** set the new preview samples to display */
	void SetDataForPreview(float* someData, int sizeInSamples = 0) ;



	
	inline int WaveFormDisplayWidget::GainToPixel( float gain ){
		return (int) (getHeight() - 5 -  gain/ MAXGAIN * ( getHeight() - 10));
		//return (int) getHeight() - gain/maxGain * ( getHeight() - 10);
		//return 30;
		//return  getHeight() - 5;
	}

		
	inline float WaveFormDisplayWidget::PixelToGain( int pixel ){
		if(pixel >=5 && pixel<= getHeight() - 5)
			return (float) (MAXGAIN * (getHeight() - 5 - pixel) / (getHeight() - 10));
		else
			return -1;//error
	}

		
	inline int WaveFormDisplayWidget::TimeToPixel( float time ){
		//return 5 + time/impulseLength * (getWidth() -10 ) ;
		return (int) (5 +  time/5.0f * (getWidth() -10 ) );
		
	}

	inline float WaveFormDisplayWidget::PixelToTime( int pixel ){
		if(pixel >=5 && pixel<= getWidth() - 5)
			return 5.0f * (pixel - 5) / (getWidth() - 10);
		else
			return -1;//error
	}




    //==============================================================================
    /**
	 * @brief Callback for painting.
	 */
    void paint (Graphics& g);

    /**
	 * @brief Callback for resize.
	 */
    void resized();

	

private:
    //==============================================================================
	
	/**
	 * @brief To constraint the window size.
	 */
    ComponentBoundsConstrainer resizeLimits;


	/**
	 * @brief Parent Component.
	 */
	Component* parent;


	/**
	 * @brief Colour of the component
	 */
	Colour color;

	/**
	 * @brief WaveForme Datas
	 */
	float* dataForPreview;

	/**
	 * @brief Sample count
	 */
	int sampleCount;



};


#endif