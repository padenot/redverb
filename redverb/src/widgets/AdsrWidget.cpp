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

	addAndMakeVisible (adsrHandleArray[0] = new AdsrHandleWidget(this,0,AdsrHandleWidget::MOVE_HORIZONTAL));
	addAndMakeVisible (adsrHandleArray[1]= new AdsrHandleWidget(this,1,AdsrHandleWidget::MOVE_HORIZONTAL|AdsrHandleWidget::MOVE_VERTICAL));
	addAndMakeVisible (adsrHandleArray[2] = new AdsrHandleWidget(this,2,AdsrHandleWidget::MOVE_HORIZONTAL|AdsrHandleWidget::MOVE_VERTICAL));
	addAndMakeVisible (adsrHandleArray[3] = new AdsrHandleWidget(this,3,AdsrHandleWidget::MOVE_HORIZONTAL|AdsrHandleWidget::MOVE_VERTICAL));
	addAndMakeVisible (adsrHandleArray[4] = new AdsrHandleWidget(this,4,AdsrHandleWidget::MOVE_HORIZONTAL));
	
	adsrHandleArray[0]->setBounds(20,20,10,10);
	adsrHandleArray[1]->setBounds(40,20,10,10);
	adsrHandleArray[2]->setBounds(60,20,10,10);
	adsrHandleArray[3]->setBounds(80,20,10,10);
	adsrHandleArray[4]->setBounds(100,20,10,10);


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

}



bool AdsrWidget::CanHandleMoveHere(int handleIndex, int x, int y){
	//remember, the goal of the method is to determine whether the handle can move where it is asked or not.
	//causes that might block the handle :
		// going outside the widget
		// going after the next handle or before the previous one.
		// for the first, going before the time origine
		// for the last, goind after the end of the impulse.

	if(x < 5){ //5 pixels far from the left edge of the widget
		return false;
	}

	if(x > getWidth() - 5){ //5 pixels far from the right edge of the widget
		return false;
	}
	
	if(y < 5){ //5 pixels far from the top edge of the widget
		return false;
	}

	if(y > getHeight() - 5){ //5 pixels far from the bottom edge of the widget
		return false;
	}


	

	return true;
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
