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
/**
 * @brief Customize the look and feel of the plugin.
 * 
 * Please refer to the juce documentation for the member description.
 */
class RedverbLookAndFeel : public LookAndFeel
{
	void drawLinearSliderThumb (Graphics &g,
								int x,
								int y,
								int width,
								int height,
								float sliderPos,
								float minSliderPos,
								float maxSliderPos,
								const Slider::SliderStyle style,
								Slider &slider);

	void drawLinearSliderBackground (Graphics &g,
		       						 int x,
									 int y,
									 int width,
									 int height,
									 float sliderPos,
									 float minSliderPos,
									 float maxSliderPos,
									 const Slider::SliderStyle style,
									 Slider &slider);

	void drawRotarySlider( Graphics &g,
						   int x,
						   int y,
						   int width,
						   int height,
						   float sliderPosProportional,
						   const float rotaryStartAngle,
						   const float rotaryEndAngle,
   						   Slider& slider);
};

