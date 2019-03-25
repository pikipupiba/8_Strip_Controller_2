#pragma once

#include "Animations.h"
#include "display.h"


Animations::Animations()
{
	
}

Animations::~Animations()
{
}

void Animations::UpdatePosition()
{
	D(startTime("Animations::UpdatePostion()"); )

	hue += (hueSpeed * speedScaleFactor);
	hueSpeed += hueAcceleration;

	position += speed * speedScaleFactor;
	speed += acceleration;

	end1 = position - featureSize / 2;
	end2 = position + featureSize / 2;

	switch (animationEndOfRange)
	{
	case EndOfRanges::Bounce:

		if (end2 < rangeEnd && end1 > rangeStart)
		{ /* Put the most common occurance as the first
		  option even though it doesn't do anything*/}

		else if (end2 > rangeEnd)
		{
			//position = rangeEnd - featureSize / 2;

			if (speed > 0)
			{ speed = -speed; }
			if (tSpeed > 0)
			{ tSpeed = -tSpeed; }

			// Maybe if I don't reverse the acceleration 
			// on a bounce I can make a bounceing ball.
			//if (acceleration > 0)
			//{ acceleration = -acceleration; }
		}
		else if (end1 < rangeStart)
		{
			//position = rangeStart + featureSize / 2;

			if (speed < 0)
			{ speed = -speed; }
			if (tSpeed < 0)
			{ tSpeed = -tSpeed; }

			if (acceleration < 0)
			{ acceleration = -acceleration; }
		}
		break;
	
	case EndOfRanges::Loop:

		if (position > rangeEnd)
		{ position -= rangeSize; }

		else if (position < rangeStart)
		{ position += rangeSize; }

		if (end2 > rangeEnd)
		{ end2 -= rangeSize; }

		else if (end1 < rangeStart)
		{ end1 += rangeSize; }

		break;
	}

	end1 = position - featureSize / 2;
	end2 = position + featureSize / 2;

	D(endTime("Animations::UpdatePostion()");)
}

/* Update an animation's pixel values. Each animation 
should erase itself perfectly to work with the library. */
void Animations::Update()
{
	D(startTime("Animations::Update");)

	Erase();			// Erase previous frame.

	if (changing != 0) { Change(); }

	UpdatePosition();	// Update position and hue.
	Draw();				// Draw the new frame.

	D(endTime("Animations::Update");)
}

void Animations::Change()
{

	D(startTime("Animations::Change()");)

	fract8 eased = ease8InOutCubic((int)changing);

	brightness = pBrightness + (tBrightness - pBrightness) * eased / 256;
	hue = pHue + (tHue - pHue) * eased / 256;

	hueSpeed = pHueSpeed + (tHueSpeed - pHueSpeed) * eased / 256;
	//hueAcceleration = 0;

	featureSize = pFeatureSize + (tFeatureSize - pFeatureSize) * eased / 256;
	//position = rangeStart + rangeSize / 2;

	speed = pSpeed + (tSpeed - pSpeed) * eased / 256;
	//acceleration = 0;

	end1 = position - featureSize / 2;
	end2 = position + featureSize / 2;

	//numRepeats = 0;
	//repeatPositionOffset = 0;
	//repeatHueOffset = 0;

	changing += 1 * speedScaleFactor;

	if ((int)changing > 255) { changing = 0; }

	D(endTime("Animations::Change()");)

}

void Animations::Randomize()
{

	D(startTime("Animations::Randomize()");)

	SetPrevVals();

	tBrightness = (float)random8(40,200);
	tHue = (float)random8();

	tHueSpeed = (float)random16(0, 1000) / (float)500;
	//hueAcceleration = 0;

	tFeatureSize = (float)rangeSize / ((float)10000 / (float)random16(1, 1000));
	//position = rangeStart + rangeSize / 2;

	tSpeed = (float)random16(0, 1000) / (float)500 - 1;
	//acceleration = 0;

	//end1 = position - featureSize / 2;
	//end2 = position + featureSize / 2;

	//numRepeats = 0;
	//repeatPositionOffset = 0;
	//repeatHueOffset = 0;

	changing = 1;

	D(endTime("Animations::Randomize()");)

}

void Animations::SetPrevVals()
{
	pBrightness = brightness;
	pHue = hue;
	pHueSpeed = hueSpeed;
	pHueAcceleration = hueAcceleration;
	pPosition = position;
	pSpeed = speed;
	pAcceleration = acceleration;
	pFeatureSize = featureSize;
}
