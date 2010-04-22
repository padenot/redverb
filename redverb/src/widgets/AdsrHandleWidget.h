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

#ifndef ADSRHANDLEWIDGET_H
#define ADSRHANDLEWIDGET_H

//#include "redverbEngine.h"
//#include "RedverbLookAndFeel.h"
#include "AdsrWidget.h"
class AdsrWidget ;//WTF?!

/**
 * @brief widget managing ADSR manipulations.
 *
 * This class handle the ADSR modification on the impulse. 
 */
class AdsrHandleWidget   : public Component
                              
{
public:





	/** 
	 * @brief Flag definition for the allowed movements
	 */
	enum{
		MOVE_NONE = 0,
		MOVE_HORIZONTAL = 1,
		MOVE_VERTICAL = 2
	};


    /** Constructor.

        When created, this will register itself with the filter for changes. It's
        safe to assume that the filter won't be deleted before this object is.
    */
	AdsrHandleWidget (AdsrWidget* theParent, int x, int y, int moves = MOVE_HORIZONTAL | MOVE_VERTICAL);

	AdsrHandleWidget (const AdsrHandleWidget& other);

    /** Destructor. */
    ~AdsrHandleWidget();

	bool operator< (const AdsrHandleWidget& other) const ;

	AdsrWidget* getParent() const ;

	int getMoveLiberty() const ;

    //==============================================================================

	void mouseDown (const MouseEvent& e);

    void mouseDrag (const MouseEvent& e);

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
	 * @brief returns the center's x coordonate
	 */
	int getCenterX();
	/**
	 * @brief returns the center's y coordonate
	 */
	int getCenterY();


private:
    //==============================================================================
	
	/**
	 * @brief To constraint the window size.
	 */
    ComponentBoundsConstrainer resizeLimits;


	/**
	 * @brief Parent Component.
	 */
	AdsrWidget* parent;



	/** 
	 * @brief allowed move direction of the handle
	 */
	int moveLiberty;



	/**
	 * @brief Dragger usefull to allow to drag the handle.
	 */
	ComponentDragger dragger;

};


#endif