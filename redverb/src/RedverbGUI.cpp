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
#include "redverbGUI.h"



//==============================================================================
RedverbGUI::RedverbGUI (RedverbEngine* const ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    // create our gain slider..
    addAndMakeVisible (gainSlider = new Slider (T("gain")));
    gainSlider->addListener (this);
    gainSlider->setRange (0.0, 1.0, 0.01);
    gainSlider->setTooltip (T("changes the volume of the audio that runs through the plugin.."));

	
    // get the gain parameter from the filter and use it to set up our slider
    gainSlider->setValue (ownerFilter->getParameter (0), false);

	// Create the feedback slider
	addAndMakeVisible (feedbackSlider = new Slider (T("feedback")));
    feedbackSlider->addListener (this);
    feedbackSlider->setRange (0.0, 1.0, 0.01);
    feedbackSlider->setTooltip (T("Adjusts the feedback of the delay effect."));

	feedbackSlider->setValue (ownerFilter->getParameter (1), false);

	addAndMakeVisible (delaySlider = new Slider (T("delay")));
    delaySlider->addListener (this);
    delaySlider->setRange (0.0, 1000.0, 0.01);
    delaySlider->setTooltip (T("Adjusts the length of the delay effect."));

	delaySlider->setValue (ownerFilter->getParameter (2), false);

	/** Custom Slider test **/
	addAndMakeVisible (customSlider = new Slider (T("custom")));
	customSlider->setLookAndFeel(new RedverbLookAndFeel());
	Slider::SliderStyle style;
	style = Slider::LinearVertical;
	customSlider->setSliderStyle(style);
    customSlider->addListener (this);
    customSlider->setRange (0.0, 1000.0, 0.01);
    customSlider->setTooltip (T("This is a custom slider instance."));

	customSlider->setValue (ownerFilter->getParameter (2),false);
	



    // add the triangular resizer component for the bottom-right of the UI
    addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
    resizeLimits.setSizeLimits (150, 150, 800, 300);

    // set our component's initial size to be the last one that was stored in the filter's settings
    setSize (ownerFilter->lastUIWidth,
             ownerFilter->lastUIHeight);

    // register ourselves with the filter - it will use its ChangeBroadcaster base
    // class to tell us when something has changed, and this will call our changeListenerCallback()
    // method.
    ownerFilter->addChangeListener (this);
}

RedverbGUI::~RedverbGUI()
{
    getFilter()->removeChangeListener (this);

    deleteAllChildren();
}

//==============================================================================
void RedverbGUI::paint (Graphics& g)
{
    // just clear the window
    g.fillAll (Colour::greyLevel (0.9f));
}

void RedverbGUI::resized()
{
	setBounds(0,0,600,350);
    gainSlider->setBounds (10, 10, 200, 22);

	feedbackSlider->setBounds(10, 40, 200, 22);

	delaySlider->setBounds(10, 70, 200, 22);

	customSlider->setBounds(240, 10, 22, 100);

    // if we've been resized, tell the filter so that it can store the new size
    // in its settings
    getFilter()->lastUIWidth = getWidth();
    getFilter()->lastUIHeight = getHeight();
}

//==============================================================================
void RedverbGUI::changeListenerCallback (void* source)
{
    // this is the filter telling us that it's changed, so we'll update our
    // display of the time, midi message, etc.
    updateParametersFromFilter();
}

void RedverbGUI::sliderValueChanged (Slider* slider)   
{
	if(slider->getName()=="gain")
	{
		getFilter()->setParameterNotifyingHost (0, (float) slider->getValue());
	}
	if(slider->getName()=="feedback")
	{
		getFilter()->setParameterNotifyingHost (1, (float) slider->getValue());
	}
	if(slider->getName()=="delay")
	{
		getFilter()->setParameterNotifyingHost (2, (float) slider->getValue());
	}
	if(slider->getName()=="custom")
	{
		getFilter()->setParameterNotifyingHost (2, (float) slider->getValue());
		customSlider->repaint();
	}
}

//==============================================================================
void RedverbGUI::updateParametersFromFilter()
{
    RedverbEngine* const filter = getFilter();

    // we use this lock to make sure the processBlock() method isn't writing to the
    // lastMidiMessage variable while we're trying to read it, but be extra-careful to
    // only hold the lock for a minimum amount of time..
    filter->getCallbackLock().enter();

    // take a local copy of the info we need while we've got the lock..
    const float newGain = filter->getParameter (0);
	const float newFeedback = filter->getParameter(1);
	const float newDelay = filter->getParameter(2);
	const float newCustom = filter->getParameter(2);

    // ..release the lock ASAP
    filter->getCallbackLock().exit();

    /* Update our slider.

       (note that it's important here to tell the slider not to send a change
       message, because that would cause it to call the filter with a parameter
       change message again, and the values would drift out.
    */
    gainSlider->setValue (newGain, false);
	feedbackSlider->setValue(newFeedback, false);
	delaySlider->setValue(newDelay,false);
	customSlider->setValue(newCustom, false);
	

    setSize (filter->lastUIWidth,
             filter->lastUIHeight);
}
