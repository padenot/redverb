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



//==============================================================================
AdsrHandleWidget::AdsrHandleWidget (Component* theParent):parent(theParent)
{
	
    // set our component's initial size
    setSize (10,10);



}

AdsrHandleWidget::~AdsrHandleWidget()
{
	//nothing to do
}

//==============================================================================
void AdsrHandleWidget::paint (Graphics& g)
{

	//draw somes axis
	Colour c1(255,0,0);
	g.setColour(c1);
	g.drawEllipse(2,2,(float)getWidth()-4,(float)getHeight()-4,3);

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
    dragger.startDraggingComponent (this, 0);
}

void AdsrHandleWidget::mouseDrag (const MouseEvent& e)
{
     MouseEvent e2 (e.getEventRelativeTo (parent));
	 int y = getY();
	 if(e2.getPosition().getX() > 0){
		 dragger.dragComponent (this, e);
		 setBounds(getX(),y,getWidth(),getHeight());
	 }
}
//==============================================================================

