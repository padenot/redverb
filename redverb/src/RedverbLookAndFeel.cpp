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

#include "RedverbLookAndFeel.h"

void RedverbLookAndFeel::drawLinearSliderThumb (Graphics &g, int x, int y, int width, int height,
			 float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider)
{
	//Logger::writeToLog("DrawLinearSliderThumb");
}

void RedverbLookAndFeel::drawLinearSliderBackground (Graphics &g, int x, int y, int width, int height,
			 float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider)
{
	Colour c1(255,255,255);
	Colour c2(128,128,128);
	int rectHeight = slider.getValue()*height/(slider.getMaximum() - slider.getMinimum());

	g.setColour(c1);
	g.fillRect(x, -rectHeight + y+height, width, rectHeight);
	///g.drawRect(x, -rectHeight + y+height, width, rectHeight, 1);
	//String str;

	g.setColour(c1);
	
	//Logger::writeToLog(slider.getName());
	//Logger::writeToLog("slider.getMaxValue() : " + String(slider.getMaximum()));
	//Logger::writeToLog("slider.getMinValue() : " + String(slider.getMinimum()));
	//Logger::writeToLog("maxSliderPos : " + String(maxSliderPos, 2));
	//Logger::writeToLog("minSliderPos : " + String(minSliderPos, 2));
	//Logger::writeToLog("height :" + String(height));
	//Logger::writeToLog(String("slider.getValue() :") + String(slider.getValue()));
	//Logger::writeToLog(String("Draw LinearSlider : ") + String(-rectHeight + y + height));

}

void RedverbLookAndFeel::drawRotarySlider(Graphics &g, int x, int y, int width, int height,
		 		float sliderPosProportional, const float rotaryStartAngle, const float rotaryEndAngle,	Slider& slider)
{

}

