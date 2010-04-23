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
#include "AdsrHandleWidget.h"
#include "AdsrWidget.h"



//==============================================================================
AdsrHandleWidget::AdsrHandleWidget (AdsrWidget* theParent,int x, int y, int moves)
:parent(theParent),moveLiberty(moves)
{
	
  setBounds(x-5,y-5,10,10);
  addChangeListener(parent);
   
}

AdsrHandleWidget::AdsrHandleWidget (const AdsrHandleWidget& other)

{
	parent = other.getParent();
	moveLiberty = other.getMoveLiberty();
	setBounds(other.getX()-5,other.getY()-5,10,10);
	addChangeListener(other.getParent());

  
}

AdsrHandleWidget::~AdsrHandleWidget()
{
	//nothing to do
}


bool AdsrHandleWidget::operator< (const AdsrHandleWidget& other) const{
	return getX() < other.getX();
}


AdsrWidget* AdsrHandleWidget::getParent() const {
	return parent;
}

int AdsrHandleWidget::getMoveLiberty() const {
	return moveLiberty;
}
/*
ComponentDragger& AdsrHandleWidget::getDragger(){
	return dragger;
}*/

//==============================================================================
void AdsrHandleWidget::paint (Graphics& g)
{

	//draw somes axis
	Colour c1(255,0,0);
	g.setColour(c1);
	g.drawEllipse(2,2,(float)getWidth()-4,(float)getHeight()-4,2);

}

void AdsrHandleWidget::resized()
{
	//setBounds(0,0,600,350);
 //   gainSlider->setBounds (10, 10, 200, 22);

	//feedbackSlider->setBounds(10, 40, 200, 22);

	//delaySlider->setBounds(10, 70, 200, 22);

	//drySlider->setBounds(552, 183, 6, 144);
	//wetSlider->setBounds(579, 183, 6, 144);

    // if we've been resized, tell the filter so that it can store the new size
    // in its settings
    //getFilter()->lastUIWidth = getWidth();
    //getFilter()->lastUIHeight = getHeight();
}

//==============================================================================

void AdsrHandleWidget::mouseDown (const MouseEvent& e)
{
	if(e.mods.isRightButtonDown()){
		//delete me
		parent->RemoveHandle(this);

	}else if (e.mods.isLeftButtonDown()){
		//dragger.startDraggingComponent (this, 0);
	}
}

void AdsrHandleWidget::mouseDrag (const MouseEvent& e)
{
     MouseEvent e2 (e.getEventRelativeTo (parent));
	 int x= e2.getPosition().getX();
	 int y= e2.getPosition().getY();

	 if(!(moveLiberty & MOVE_VERTICAL))
		y = getY();		
	 if(!(moveLiberty & MOVE_HORIZONTAL))
		x = getX();

	 /*if( parent->CanHandleMoveHere(this, x, y)){
		 dragger.dragComponent (this, e);
		 setBounds(x,y,getWidth(),getHeight());
	 }*/
	 parent->MoveHandleHereIfPossible(this, x, y, e);

	 parent->repaint();
}

void AdsrHandleWidget::mouseUp (const MouseEvent& e)
{
	//just let the parent know it is interesting to refresh the filter's info
	//if( ! e.mods.isRightButtonDown()){
		sendChangeMessage(this);
	//}
		
}

int AdsrHandleWidget::getCenterX(){
	return getX()+getWidth()/2;
}

int AdsrHandleWidget::getCenterY(){
	return getY()+getHeight()/2;
}

//==============================================================================

