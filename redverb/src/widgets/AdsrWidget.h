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
class AdsrHandleWidget ;//WTF?!
#include "redverbEngine.h"
//#include "RedverbLookAndFeel.h"
#include "AdsrHandleWidget.h"


/**
 * @brief widget managing ADSR manipulations.
 *
 * This class handle the ADSR modification on the impulse. 
 */
class AdsrWidget   : public ChangeListener, public Component
                              
{
public:


    /** Constructor.

        When created, this will register itself with the filter for changes. It's
        safe to assume that the filter won't be deleted before this object is.
    */
    AdsrWidget (RedverbEngine* const ownerFilter);

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
    bool CanHandleMoveHere(AdsrHandleWidget* adsrHandlePtr ,int x, int y);

	/**
	 * @brief Remove if allowed this handle
	 */
    void RemoveHandle(AdsrHandleWidget* adsrHandlePtr);


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
	 * @brief A pointeur to the filtre itself
	 */
	RedverbEngine* filter;


};


#endif