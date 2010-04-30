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
#include "widgets/AdsrWidget.h"
#include "Ressources/ressources.h"

#define Pi 3.14159265358979323846 

//==============================================================================
RedverbGUI::RedverbGUI (RedverbEngine* const ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
	// create our information Label
	addAndMakeVisible(infoLabel = new Label(T("infoLabel"), "labelText") );
	infoLabel->setColour(Label::textColourId, Colour(255,255,255));
	// create our predelay knob.. TODO
    addAndMakeVisible(rotaryPreDelay = new Slider (T("gain"))); //TODO change that "gain" stuff here, i actually use it to check the knob's value...
	rotaryPreDelay->setSliderStyle(Slider::Rotary);
	rotaryPreDelay->setTextBoxStyle(Slider::NoTextBox,true, 0,0);
	rotaryPreDelay->setRotaryParameters(-4*Pi/5, 4*Pi/5, true);
	rotaryPreDelay->setLookAndFeel(new RedverbLookAndFeel());
    rotaryPreDelay->addListener (this);
    rotaryPreDelay->setRange (0.0, 1000.0, 0.01);
	rotaryPreDelay->setTooltip (T("changes the pre-delay parameter.."));

    // create our gain slider..
    addAndMakeVisible (gainSlider = new Slider (T("gain")));
    gainSlider->addListener (this);
    gainSlider->setRange (0.0, 1000.0, 0.01);
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

	/** Custom Slider DRY**/
	addAndMakeVisible (drySlider = new Slider (T("dryGain")));
	drySlider->setLookAndFeel(new RedverbLookAndFeel());
	Slider::SliderStyle dryStyle;
	dryStyle = Slider::LinearVertical;
	drySlider->setSliderStyle(dryStyle);
    drySlider->addListener (this);
    drySlider->setRange (0, 1.25, 0.01);
	drySlider->setDoubleClickReturnValue(true,1.0);
    drySlider->setTooltip (T("This slider sets the dry gain ratio."));

	drySlider->setValue (ownerFilter->getParameter (3),false);

	/** Custom Slider WET **/
	addAndMakeVisible (wetSlider = new Slider (T("wetGain")));
	wetSlider->setLookAndFeel(new RedverbLookAndFeel());
	Slider::SliderStyle wetStyle;
	wetStyle = Slider::LinearVertical;
	wetSlider->setSliderStyle(wetStyle);
    wetSlider->addListener (this);
    wetSlider->setRange (0, 1.25, 0.01);
	wetSlider->setDoubleClickReturnValue(true,1.0);
    wetSlider->setTooltip (T("This slider sets the wet gain ratio."));


	wetSlider->setValue (ownerFilter->getParameter(4),false);

	/** ADSRwidget **/
	addAndMakeVisible (adsrWid = new AdsrWidget (this));
	adsrWid->addChangeListener(this);


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
	background = ImageFileFormat::loadFrom(Ressources::fond2_png, Ressources::fond2_pngSize);

//	addAndMakeVisible (fileChooserButton = new DrawableButton(T("FileChooserButton"), DrawableButton::ImageRaw));
//	fileChooserButton->addComponentListener(this);
//	fileChooserButton->setImages(Ressources::loadimpulsenormal_png, Ressources::loadimpulseover_png, Ressources::loadimpulsedown_png);
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
    //g.fillAll (Colour::greyLevel (0.9f));

	// blit the background
	g.drawImageAt(background,0,0);
	//prefere to load from an input stream, and add the image directly in binary code.
	//prevents loading time
	//g.drawImageAt(ImageFileFormat::loadFrom(THE_INPUT_STREAM)),0,0);
}

void RedverbGUI::resized()
{
	setBounds(0,0,600,350);
	
	infoLabel->setBounds(10,320, 560, 30 );
	setInfoLabelText(File::getCurrentWorkingDirectory().getFullPathName());

    gainSlider->setBounds (10, 10, 200, 22);

	rotaryPreDelay->setBounds (529, 97, 55, 55);

	feedbackSlider->setBounds(10, 40, 200, 22);

	delaySlider->setBounds(10, 75, 200, 22);

	//fileChooserButton->setBounds(400, 70, 10, 10);

	/*
	leftDryVolume->setBounds(535, 173, 5, 115);
	rightDryVolume->setBounds(550, 173, 5, 115);
	leftWetVolume->setBounds(570, 173, 5, 115);
	rightWetVolume->setBounds(595, 173, 5, 115);
	*/
	drySlider->setBounds(540, 173, 10, 115);
	wetSlider->setBounds(575, 173, 10, 115);

	adsrWid->setBounds(10,90,495,225);//this dimension correspond to the display zone.
	//adsrWid->setBaseADSR();
	adsrWid->setRawImpulse();

    // if we've been resized, tell the filter so that it can store the new size
    // in its settings
    getFilter()->lastUIWidth = getWidth();
    getFilter()->lastUIHeight = getHeight();
}

void RedverbGUI::setInfoLabelText(juce::String newText)
{
	infoLabel->setText(newText, false);
}


//==============================================================================
void RedverbGUI::changeListenerCallback (void* source)
{
	//warning ! change message might arrive from either the filtre OR the ADSR widget : TEST THAT

	setInfoLabelText("changeListenerCallback called");
	if(source == getFilter()){

		// this is the filter telling us that it's changed, so we'll update our
		// display of the time, midi message, etc.
		updateParametersFromFilter();
	}else if (source == adsrWid){
		//getFilter()->setParameterNotifyingHost (0, adsrWid->getValues());
		setInfoLabelText("handleChanged");
		
		
	}
}

void RedverbGUI::sliderValueChanged (Slider* slider)   
{
	if(slider->getName()=="gain")
	{
		getFilter()->setParameterNotifyingHost (0, (float) slider->getValue());
	}
	else if(slider->getName()=="feedback")
	{
		getFilter()->setParameterNotifyingHost (1, (float) slider->getValue());
	}
	else if(slider->getName()=="delay")
	{
		getFilter()->setParameterNotifyingHost (2, (float) slider->getValue());
	}
	else if(slider->getName()=="dryGain")
	{
		getFilter()->setParameterNotifyingHost (3, (float) slider->getValue());
	}
	else if(slider->getName()=="wetGain")
	{
		getFilter()->setParameterNotifyingHost (4, (float) slider->getValue());
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
	const float newDry = filter->getParameter(3);
	const float newWet = filter->getParameter(4);

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
	drySlider->setValue(newDry, false);
	wetSlider->setValue(newWet, false);
	

    setSize (filter->lastUIWidth,
             filter->lastUIHeight);
}
