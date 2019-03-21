#pragma once

#include "Mover.h"
#include "display.h"



Mover::Mover()
{
	numObjects++;

	rangeStart = 0;
	rangeEnd = NUM_LEDS_PER_STRIP;
	rangeSize = rangeEnd - rangeStart; // Automatically calculated rangeSize for easier to read code.

	animationShape = Shapes::Strip;				// The shape of the strip the animation is playing on.
	animationTexture = Textures::None;			// A modifier applied to the animation after values are calculated.
	animationEndOfRange = EndOfRanges::Bounce;	// How an animation acts when it approaches the end of its range.

	brightness = 255;
	hue = 0;			// Hue is the starting value used to calculate the various colors in an animation step.
	hueSpeed = 0.5;			// Hue speed is how much hue changes each step.
	hueAcceleration = 0;	// Hue acceleration is how much hue speed changes each step.

	featureSize = 10;	// Used to describe the size of a "feature" of the animation. Usually equals end2 - end1.
	position = rangeStart + featureSize / 2 + 2;		// Position can either be where an object is in its range or the current step in a sequence it is on.
	speed = 0.2;				// How much position changes each step.
	acceleration = 0;		// How much speed changes each step.


	//featureSize = 10;	// Used to describe the size of a "feature" of the animation. Usually equals end2 - end1.
	end1 = position - featureSize / 2;			// Keeps track of one end of a "feature."
	end2 = position + featureSize / 2;			// Keeps track of the other end of a "feature."

	numRepeats = 0;		// Used to copy a small animation to different positions in its range.
	repeatPositionOffset = 0;	// How much the position of each repeat is offset from the previous one.
	repeatHueOffset = 0;
}


Mover::~Mover()
{
}

void Mover::Update()
{

	UpdatePosition();

	Draw();
	
}

void Mover::Draw()
{
	/*float fEnd1 = uint32_to_float(end1, 0, NUM_LEDS_PER_STRIP);
	float fEnd2 = uint32_to_float(end2, 0, NUM_LEDS_PER_STRIP);
	//Serial.println(fEnd1);
	//Serial.println(fEnd2);

	int iEnd1 = (int)fEnd1;
	int iEnd2 = (int)fEnd2;
	//Serial.println(iEnd1);
	//Serial.println(iEnd2);

	uint32_t curHue = uint32_to_uint32(hue, 0, 255);
	uint32_t curBrightness = uint32_to_uint32(brightness, 0, 255);*/

	

	int iEnd1 = (int)end1;
	int iEnd2 = (int)end2;
	int iHue = (int)hue;
	int iBrightness = (int)brightness;

	

	for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
	{
		animationLEDs[i] = CRGB::Black;
	}
	//animationLEDs[0, 300] = CRGB::Black;
	

	if (end1 < end2)
	{
	
		for (int i = iEnd1; i <= iEnd2; i++)
		{
			
			animationLEDs[i] = CHSV(iHue,255,iBrightness);
		}
		//animationLEDs[iEnd1, iEnd2] = hue;
		
	}
	else
	{

		for (int i = rangeStart; i <= iEnd2; i++)
		{
			animationLEDs[i] = CHSV(iHue, 255, iBrightness);
		}
		for (int i = iEnd1; i <= rangeEnd; i++)
		{
			animationLEDs[i] = CHSV(iHue, 255, iBrightness);
		}
		//animationLEDs[iEnd1, uint32_to_uint32(rangeEnd,0,300)];
		//animationLEDs[uint32_to_uint32(rangeStart, 0, 300), iEnd2];
	}
	
	animationLEDs[iEnd1] *= 1 - (end1 - iEnd1);
	animationLEDs[iEnd2] *= end2 - iEnd2;
	
}
