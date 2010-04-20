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
#include "AdsrWidget.h"



//==============================================================================
AdsrWidget::AdsrWidget (RedverbEngine* const ownerFilter)
		//:Component()//?required?
{
	this->filter = ownerFilter;

    // set our component's initial size
    //setSize (20,20);
	setOpaque (! Desktop::canUseSemiTransparentWindows());

    // register ourselves with the filter - it will use its ChangeBroadcaster base
    // class to tell us when something has changed, and this will call our changeListenerCallback()
    // method.

    filter->addChangeListener (this);

	addAndMakeVisible (attackAdsrHandle = new AdsrHandleWidget(this));
	
}

AdsrWidget::~AdsrWidget()
{
    filter->removeChangeListener (this);

    deleteAllChildren();//warning with the adsrHandleWidget
}

//==============================================================================
void AdsrWidget::paint (Graphics& g)
{
    // just clear the window
    g.fillAll (Colours::red.withAlpha (0.2f));

	//draw somes axis
	Colour c1(128,128,128);
	g.setColour(c1);
	g.drawArrow(5,(float)(getHeight()/2),(float)(getWidth()-5),(float)(getHeight()/2),2,6,6);

}

void AdsrWidget::resized()
{
	//setBounds(0,0,600,350);
	attackAdsrHandle->setBounds(20,20,10,10);
}

//==============================================================================
void AdsrWidget::changeListenerCallback (void* source)
{
    // this is the filter telling us that it's changed, so we'll update our
    // display of the time, midi message, etc.
    updateParametersFromFilter();
}


//==============================================================================
void AdsrWidget::updateParametersFromFilter()
{

    // we use this lock to make sure the processBlock() method isn't writing to the
    // lastMidiMessage variable while we're trying to read it, but be extra-careful to
    // only hold the lock for a minimum amount of time..
    filter->getCallbackLock().enter();

    // take a local copy of the info we need while we've got the lock..
 //   const float newGain = filter->getParameter (0);
	//const float newFeedback = filter->getParameter(1);
	//const float newDelay = filter->getParameter(2);
	//const float newDry = filter->getParameter(3);
	//const float newWet = filter->getParameter(4);

    // ..release the lock ASAP
    filter->getCallbackLock().exit();


}
