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
			position = rangeEnd - featureSize / 2;

			if (speed > 0)
			{ speed = -speed; }

			// Maybe if I don't reverse the acceleration 
			// on a bounce I can make a bounceing ball.
			//if (acceleration > 0)
			//{ acceleration = -acceleration; }
		}
		else if (end1 < rangeStart)
		{
			position = rangeStart + featureSize / 2;

			if (speed < 0)
			{ speed = -speed; }

			if (acceleration < 0)
			{ acceleration = -acceleration; }
		}
		break;
	
	case EndOfRanges::Loop:

		if (position > rangeEnd)
		{ position -= rangeSize; }

		else if (position < rangeStart)
		{ position += rangeSize; }

		break;
	}

	end1 = position - featureSize / 2;
	end2 = position + featureSize / 2;

	if (end2 > rangeEnd)
	{ end2 -= rangeSize; }

	else if (end1 < rangeStart)
	{ end1 += rangeSize; }
}

/* Update an animation's pixel values. Each animation 
should erase itself perfectly to work with the library. */
void Animations::Update()
{
	Draw(-1);			// Erase previous frame.
	UpdatePosition();	// Update position and hue.
	Draw();				// Draw the new frame.
}

void Animations::Change()
{
	//brightness = 255;
	hue = random8();
	hueSpeed = 500.0 / (float)random16(1, 1000);
	//hueAcceleration = 0;

	featureSize = rangeSize / (100.0 / random16(1, 1000));
	//position = rangeStart + rangeSize / 2;
	speed = 500.0 / (float)random16(1, 1000);;
	//acceleration = 0;

	end1 = position - featureSize / 2;
	end2 = position + featureSize / 2;

	//numRepeats = 0;
	//repeatPositionOffset = 0;
	//repeatHueOffset = 0;
}
