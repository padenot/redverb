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

#ifndef ADSRWIDGET_H
#define ADSRWIDGET_H
#include <set>
#include <vector>
class AdsrHandleWidget ;//WTF?!
#include "redverbEngine.h"
//#include "RedverbLookAndFeel.h"
#include "AdsrHandleWidget.h"


const float MAXGAIN = 1.25f;

/**
 * @brief widget managing ADSR manipulations.
 *
 * This class handle the ADSR modification on the impulse. 
 */
class AdsrWidget   : public ChangeListener, public Component, public ChangeBroadcaster
                              
{
public:


    /** Constructor.

        When created, this will register itself with the filter for changes. It's
        safe to assume that the filter won't be deleted before this object is.
    */
    AdsrWidget (/*RedverbEngine* const ownerFilter*/ Component* theParent);

    /** Destructor. */
    ~AdsrWidget();

    //==============================================================================

	/**
	 * @brief Called when the user wants to add an handle.
	 */
	void mouseDoubleClick (const MouseEvent& e);


	/**
	 * @brief Called when parameter change occur.
	 */
    void changeListenerCallback (void* source);


	/**
	 * @brief sets the envelope to a classic ADSR
	 */
	void setBaseADSR();

	/**
	 * @brief sets the raw impulse for preview
	 */
	void setRawImpulse(int sizeInSamples = 0 ,float** data = 0);

	
	/**
	 * @brief gets the pairs of values of our handles
	 */
	std::vector<std::pair<float,float>> getValues();


    //==============================================================================
    /**
	 * @brief Callback for painting.
	 */
    void paint (Graphics& g);

    /**
	 * @brief Callback for resize.
	 */
    void resized();

	/**
	 * @brief Test if the handle is allowed to move at this coordonates.
	 */
    void MoveHandleHereIfPossible(AdsrHandleWidget* adsrHandlePtr ,int x, int y, const MouseEvent& e);

	/**
	 * @brief Remove if allowed this handle
	 */
    void RemoveHandle(AdsrHandleWidget* adsrHandlePtr);

int AdsrWidget::GainToPixel( float gain ){
	return (int) (getHeight() - 5 -  gain/ MAXGAIN * ( getHeight() - 10));
	//return (int) getHeight() - gain/maxGain * ( getHeight() - 10);
	//return 30;
	//return  getHeight() - 5;
}

	
inline float AdsrWidget::PixelToGain( int pixel ){
	if(pixel >=5 && pixel<= getHeight() - 5)
		return (float) (MAXGAIN * (getHeight() - 5 - pixel) / (getHeight() - 10));
	else
		return -1;//error
}

	
inline int AdsrWidget::TimeToPixel( float time ){
	//return 5 + time/impulseLength * (getWidth() -10 ) ;
	return (int) (5 +  time/5.0f * (getWidth() -10 ) );
	return 30;
}

	
inline float AdsrWidget::PixelToTime( int pixel ){
	if(pixel >=5 && pixel<= getWidth() - 5)
		return 5.0f * (pixel - 5) / (getWidth() - 10);
	else
		return -1;//error
}




private:
    //==============================================================================

	/** 
	 * @brief Comparator tool to compare pointers of AdsrHandleWidget
	 */
	struct ltAdsrHandleWidgetPtr{
		bool operator()(const AdsrHandleWidget* s1, const AdsrHandleWidget* s2) const;
	};

	/**
	 * @brief Array of handles
	 */
	typedef std::set<AdsrHandleWidget*, ltAdsrHandleWidgetPtr> AdsrHandleSetType;
	AdsrHandleSetType adsrHandleSet;


	/**
	 * @brief To constraint the window size.
	 */
    ComponentBoundsConstrainer resizeLimits;
	/**
	 * @brief To add useful tooltips.
	 */ 
    TooltipWindow tooltipWindow;

	/**
     * @brief Get new parameters from filter.
	 */
    void updateParametersFromFilter();



	/**
     * @brief recomputes the ImpulsePreview with the envelope
	 */
    void recomputeModulation();/*think about adding a paramteter to lower computation needs. */


	/**
     * @brief draw the untouched Impulse
	 */
    void drawRawImpulse(Graphics& g);

	/**
     * @brief draw the modulated Impulse
	 */
    void drawModulatedImpulse(Graphics& g);





	/**
	 * @brief This is true 
	 */
    bool impulseDataNeedsRedrawing;

	/**
	 * @brief A pointeur to the filtre itself
	 */
	RedverbEngine* filter;

	/**
	 * @brief A int array for the raw Impulse
	 */
	float* rawImpulse;

	/**
	 * @brief A int array for the envelope-modulated Impulse
	 */
	float* modulatedImpulse;



	/**
	 * @brief the maximum gain
	 */
	//const static float maxGain  = 1.25f;

	/**
	 * @brief the impulse length in seconds
	 */
	//const static float impulseLength  = 10.0f;

	Component* parent;



};


#endif