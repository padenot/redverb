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
#include <set>
#include <vector>

#include <math.h>
#include "WaveFormDisplayWidget.h"

#define PI 3.14159265

#define max(a,b) (((a)>(b)?(a):(b) ))
#define min(a,b) (((a)<(b)?(a):(b) ))




//==============================================================================

	 
bool AdsrWidget::ltAdsrHandleWidgetPtr::operator()(const AdsrHandleWidget* s1, const AdsrHandleWidget* s2) const{
	return s1->getX() < s2->getX();
}




AdsrWidget::AdsrWidget (Component* theParent):parent(theParent)
		//:Component()//?required?
{
	//this->filter = ownerFilter;

    // set our component's initial size
    //setSize (20,20);
	setOpaque (! Desktop::canUseSemiTransparentWindows());
	rawImpulseDisplayWid = 0;
	modImpulseDisplayWid = 0;


}

AdsrWidget::~AdsrWidget()
{


    deleteAllChildren();//warning with the adsrHandleWidget
	


}

//==============================================================================
void AdsrWidget::paint (Graphics& g)
{
    // just clear the window
    //g.fillAll (Colours::whiter.withAlpha (0.2f));

	//draw somes axis
	Colour c1(128,128,128);
	g.setColour(c1);
	g.drawArrow(5,(float)(getHeight() -5),(float)(getWidth()-5),(float)(getHeight()-5),2,6,6);
	g.drawArrow(5,(float)(getHeight() -5),5,5,2,6,6);

	AdsrHandleSetType::iterator it;
	AdsrHandleSetType::iterator it2;

	for (it = it2 = adsrHandleSet.begin() ; it2 != adsrHandleSet.end(); ){
		it2 = it;
		it2++;
		if( it2 !=  adsrHandleSet.end()){
			int x = (*it)->getCenterX();
			int y = (*it)->getCenterY();
			it++;
			g.drawLine((float)x,(float)y,(float)(*it)->getCenterX(),(float)(*it)->getCenterY(),2);
		}
		
	
	}




}

void AdsrWidget::resized()
{
	//setBounds(0,0,600,350);

}







void AdsrWidget::setBaseADSR(){

	rawImpulseDisplayWid = new WaveFormDisplayWidget(this,getWidth(),getHeight(), Colours::black.withAlpha(0.5f),0,0);
	addChildComponent(rawImpulseDisplayWid);
	rawImpulseDisplayWid->setVisible(true);
	rawImpulseDisplayWid->repaint();

	//modImpulseDisplayWid = new WaveFormDisplayWidget(this,getWidth(),getHeight(), Colours::red.withAlpha(0.4f),0,0);
	//modImpulseDisplayWid = new WaveFormDisplayWidget(*rawImpulseDisplayWid);
	//addChildComponent(modImpulseDisplayWid);
//	modImpulseDisplayWid->SetColor(Colours::red.withAlpha(0.4f));
	//rawImpulseDisplayWid->repaint();

	adsrHandleSet.insert(new AdsrHandleWidget(this, TimeToPixel(0), GainToPixel(0.0f), AdsrHandleWidget::MOVE_HORIZONTAL));
	adsrHandleSet.insert(new AdsrHandleWidget(this, 7, GainToPixel(1.0f), AdsrHandleWidget::MOVE_HORIZONTAL|AdsrHandleWidget::MOVE_VERTICAL));
	adsrHandleSet.insert(new AdsrHandleWidget(this, getWidth()-7, GainToPixel(1.0f), AdsrHandleWidget::MOVE_HORIZONTAL|AdsrHandleWidget::MOVE_VERTICAL));
	adsrHandleSet.insert(new AdsrHandleWidget(this, getWidth()-5, GainToPixel(0.0f), AdsrHandleWidget::MOVE_HORIZONTAL));

	AdsrHandleSetType::iterator it;
	for (it=adsrHandleSet.begin(); it!=adsrHandleSet.end(); it++)
		addAndMakeVisible(*it);



		rawImpulseDisplayWid->SetRawWaveForm(0,0);
		//modImpulseDisplayWid->SetRawWaveForm(0,0);

}



std::vector<std::pair<float,float> > AdsrWidget::getValues(){
	std::vector<std::pair<float,float> > temp;
	return temp;
}



void AdsrWidget::MoveHandleHereIfPossible(AdsrHandleWidget* adsrHandlePtr, int x, int y, const MouseEvent& e){
	//remember, the goal of the method is to determine whether the handle can move where it is asked or not.
	//causes that might block the handle :
		// going outside the widget
		// going after the next handle or before the previous one.
		// for the first, going before the time origine
		// for the last, goind after the end of the impulse.

	if(y < 5){ //5 pixels far from the top edge of the widget
		y = 5;
	}

	if(y > getHeight() - 5){ //5 pixels far from the bottom edge of the widget
		y = getHeight() - 5;
	}

	if (adsrHandlePtr == *adsrHandleSet.begin()){
		//cannot go after the second handle
		AdsrHandleSetType::iterator next = adsrHandleSet.begin();
		next ++;
		x = max(0,min( (*next)->getX() -5 , x)) ;

	}else if (adsrHandlePtr == *adsrHandleSet.rbegin()){
		//cannot go before the previous one
		AdsrHandleSetType::reverse_iterator next = adsrHandleSet.rbegin();
		next ++;
		x = max((*next)->getX() +5,min( getWidth() - 10 , x)) ;

	} else{//any other handle
		AdsrHandleSetType::iterator previous;
		AdsrHandleSetType::iterator self;
		AdsrHandleSetType::iterator next;
		for (previous = self = adsrHandleSet.begin() ; *self != adsrHandlePtr; ){
			self = previous;
			self++;
			if( *self !=  adsrHandlePtr){
				previous++;	
			}else{
				next = self;
				next++;
			}
		}
		x = max((*previous)->getX() +5,min( (*next)->getX() - 5 , x)) ;
	}
	//adsrHandlePtr->getDragger().dragComponent (adsrHandlePtr, e);
	adsrHandlePtr->setBounds(x,y,adsrHandlePtr->getWidth(),adsrHandlePtr->getHeight());
}



void AdsrWidget::RemoveHandle(AdsrHandleWidget* adsrHandlePtr){
	//should test in order not to remove the first and the last handle
	if (adsrHandlePtr == *adsrHandleSet.begin()){
		//nothing to do, shouldn't delete the first handle
	}else if (adsrHandlePtr == *adsrHandleSet.rbegin()){
		//nothing to do, shouldn't delete the last handle
	}else{ //delete that handle
		adsrHandleSet.erase(adsrHandlePtr);
		delete adsrHandlePtr;
		repaint();
	}
}

//==============================================================================

void AdsrWidget::mouseDoubleClick (const MouseEvent& e){

	if(e.getPosition().getX() <= (*(adsrHandleSet.begin()))->getX()){
		//refuse to add that point
	}else if(e.getPosition().getX() >= (*(adsrHandleSet.rbegin()))->getX()){
		//refuse to add that point
	}else{
		AdsrHandleWidget* temp = new AdsrHandleWidget(this, e.getPosition().getX(), e.getPosition().getY(), AdsrHandleWidget::MOVE_HORIZONTAL|AdsrHandleWidget::MOVE_VERTICAL);
		
		AdsrHandleSetType::iterator it = (adsrHandleSet.insert(temp)).first;
		addAndMakeVisible (*it);
		
		repaint();
	}
}



void AdsrWidget::changeListenerCallback (void* source)
{
    //we received a change message from one of the handles!
	//send a change message to the GUI
	sendChangeMessage(this);
	//recomputeModulation();
	//repaint();
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


/*
void AdsrWidget::recomputeModulation(){
	//need to compute the values of the modulatedImpulse.

	int i = 5;
	AdsrHandleSetType::iterator it = adsrHandleSet.begin();

	for(;i<=(*it)->getCenterX();i++){
		modulatedImpulse[i-5] = 0;
	}
	//utiliser le code de tracage de trait entre 2 poignées pour parcourir les liens entre poignées
	//recuperer les infos necessaires.
	//appliquer la modulation


	for(int j = (*(adsrHandleSet.rbegin()))->getCenterX() ;j<getWidth()-5;j++){
		modulatedImpulse[j-5] = 0;
	}
	repaint();
}
*/



// Gain2pixel and al have been inlined.



