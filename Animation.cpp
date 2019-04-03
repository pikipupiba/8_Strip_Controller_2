#include "stdafx.h"

#pragma once

#include "Animation.h"
#include "display.h"
#include "stripController.h"

Animation::Animation()
{
	D(startTime("Animation::Animation()"); )

	// Keep track of how many objects are currently running.
	numObjects++;


	animationShape = Shapes::Strip;
	animationTexture = Textures::None;
	animationEndOfRange = EndOfRanges::Bounce;

	brightness = 128;
	hue = 0;
	hueSpeed = 0.5;
	hueAcceleration = 0;

	featureSize = 3;
	
	speed = 0.2;
	acceleration = 0;

	

	numRepeats = 0;
	repeatPositionOffset = 0;
	repeatHueOffset = 0;

	changing = 0;

	

	D(endTime("Animation::Animation()"); )
}

Animation::~Animation()
{
}

void Animation::AssignVals(aniArg aniArgs[])
{
	D(startTime("Animation::AssignVals(aniArg aniArgs[])"); )

		int i = 0;

	while(aniArgs[i].name != "")
	{
		//debugCounter();
		if (aniArgs[i].name == "rangeStart")
		{
			rangeStart = aniArgs[i].val;	// Where on a strip an animation starts.
		}
		else if (aniArgs[i].name == "rangeEnd")
		{
			rangeEnd = aniArgs[i].val;		// Where on a strip an animation ends.
		}
		else if (aniArgs[i].name == "brightness")
		{
			brightness = aniArgs[i].val;		// The brightness of an animation before being scaled by strip and global brightness.
		}
		else if (aniArgs[i].name == "hue")
		{
			hue = aniArgs[i].val;				// Hue is the starting value used to calculate the various colors in an animation step.
		}
		else if (aniArgs[i].name == "hueSpeed")
		{
			hueSpeed = aniArgs[i].val;			// Hue speed is how much hue changes each step.
		}
		else if (aniArgs[i].name == "hueAcceleration")
		{
			hueAcceleration = aniArgs[i].val;	// Hue acceleration is how much hue speed changes each step.
		}
		else if (aniArgs[i].name == "position")
		{
			position = aniArgs[i].val;		// Position can either be where an object is in its range or the current step in a sequence it is on.
		}
		else if (aniArgs[i].name == "speed")
		{
			speed = aniArgs[i].val;		// How much position changes each step.
		}
		else if (aniArgs[i].name == "acceleration")
		{
			acceleration = aniArgs[i].val;	// How much speed changes each step.
		}
		else if (aniArgs[i].name == "featureSize")
		{
			featureSize = aniArgs[i].val;	// Used to describe the size of a "feature" of the animation. Usually equals end2 - end1.
		}

		i++;
	}

	D(endTime("Animation::AssignVals(aniArg aniArgs[])"); )
}

void Animation::UpdatePosition()
{
	D(startTime("Animation::UpdatePostion()"); )

	//GetBackToRange();

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

	D(endTime("Animation::UpdatePostion()");)
}

/* Update an animation's pixel values. Each animation 
should erase itself perfectly to work with the library. */
void Animation::Update()
{
	D(startTime("Animation::Update");)

	Erase();			// Erase previous frame.

	if (changing != 0) { Change(); }

	UpdatePosition();	// Update position and hue.
	Draw();				// Draw the new frame.

	D(endTime("Animation::Update");)
}

void Animation::Change()
{

	D(startTime("Animation::Change()");)

	fract8 eased = ease8InOutCubic((int)changing);

	brightness = pBrightness + (tBrightness - pBrightness) * eased / 256;
	hue = pHue + (tHue - pHue) * eased / 256;

	hueSpeed = pHueSpeed + (tHueSpeed - pHueSpeed) * eased / 256;
	//hueAcceleration = 0;

	featureSize = pFeatureSize + (tFeatureSize - pFeatureSize) * eased / 256;
	position = pPosition + (tPosition - pPosition) * eased / 256;

	speed = pSpeed + (tSpeed - pSpeed) * eased / 256;
	//acceleration = 0;

	end1 = position - featureSize / 2;
	end2 = position + featureSize / 2;

	//numRepeats = 0;
	//repeatPositionOffset = 0;
	//repeatHueOffset = 0;

	changing += 1 * speedScaleFactor;

	if ((int)changing > 255) { changing = 0; }

	D(endTime("Animation::Change()");)

}

/*void Animation::Randomize()
{

	D(startTime("Animation::Randomize()");)

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

	D(endTime("Animation::Randomize()");)

}*/

void Animation::Randomize(String var = "")
{
	D(startTime("Randomize()");)

	if (var == "" || var == "brightness")
	{
		tBrightness = (float)random8(40, 200);
	}
	if (var == "" || var == "hue")
	{
		tHue = (float)random8();
	}
	if (var == "" || var == "hueSpeed")
	{
		tHueSpeed = (float)random16(0, 1000) / (float)500;
	}
	if (var == "" || var == "featureSize")
	{
		tFeatureSize = (float)rangeSize / ((float)10000 / (float)random16(1, 1000));
	}
	if (var == "" || var == "speed")
	{
		tSpeed = (float)random16(0, 1000) / (float)500 - 1;
	}

	D(endTime("Randomize()");)
}

void Animation::SetPrevVals(String var = "")
{
	D(startTime("SetPrevVals()");)

	if (var == "" || var == "brightness")
	{
		pBrightness = brightness;
	}
	if (var == "" || var == "hue")
	{
		pHue = hue;
	}
	if (var == "" || var == "hueSpeed")
	{
		pHueSpeed = hueSpeed;
	}
	if (var == "" || var == "hueAcceleration")
	{
		pHueAcceleration = hueAcceleration;
	}
	if (var == "" || var == "position")
	{
		pPosition = position;
	}
	if (var == "" || var == "speed")
	{
		pSpeed = speed;
	}
	if (var == "" || var == "acceleration")
	{
		pAcceleration = acceleration;
	}
	if (var == "" || var == "featureSize")
	{
		pFeatureSize = featureSize;
	}

	D(endTime("SetPrevVals()");)
}

void Animation::SetRangeAbsolute(int newRangeStart = 0, int newRangeEnd = 0)
{
	if (newRangeStart == 0 && newRangeEnd == 0)
	{
		rangeStart = strips[0]->stripRangeStart;
		rangeEnd = strips[NUM_STRIPS - 1]->stripRangeEnd;
	}
	else if (newRangeEnd == 0)
	{
		rangeStart = strips[0]->stripRangeStart + newRangeStart;
		rangeEnd = strips[NUM_STRIPS - 1]->stripRangeEnd;
	}
	else if (newRangeEnd > 0)
	{
		rangeStart = strips[0]->stripRangeStart + newRangeStart;
		rangeEnd = strips[NUM_STRIPS - 1]->stripRangeStart + newRangeEnd;
	}
	else if (newRangeEnd < 0)
	{
		rangeStart = strips[0]->stripRangeStart + newRangeStart;
		rangeEnd = strips[NUM_STRIPS - 1]->stripRangeEnd - newRangeEnd;
	}
}

void Animation::SetRangeOnStrip(int newRangeStart = 0, int newRangeEnd = 0)
{
	D(startTime("SetRangeOnStrip()");)

	if (newRangeStart == 0 && newRangeEnd == 0)
	{
		rangeStart = strip->stripRangeStart;
		rangeEnd = strip->stripRangeEnd;
	}
	else if (newRangeEnd == 0)
	{
		rangeStart = strip->stripRangeStart + newRangeStart;
		rangeEnd = strip->stripRangeEnd;
	}
	else if (newRangeEnd > 0)
	{
		rangeStart = strip->stripRangeStart + newRangeStart;
		rangeEnd = strip->stripRangeStart + newRangeEnd;
	}
	else if (newRangeEnd < 0)
	{
		rangeStart = strip->stripRangeStart + newRangeStart;
		rangeEnd = strip->stripRangeEnd - newRangeEnd;
	}

	D(endTime("SetRangeOnStrip()");)
}

void Animation::GetBackToRange()
{
	D(startTime("GetBackToRange()");)

	if (changing == 0)
	{
		if (tPosition < rangeStart)
		{
			//tPosition = rangeStart;
			tSpeed = abs(speed);
		}
		else if (position > rangeEnd)
		{
			//tPosition = rangeEnd;
			tSpeed = -abs(speed);
		}

		SetPrevVals();

		changing = 1;
	}

	D(endTime("GetBackToRange()");)
}

void Animation::PrintAnimationInfo(String ID = "")
{
	Serial.println();

	Serial.print("Animation ID: ");
	Serial.println(ID);

	Serial.print("Animation Range Start: ");
	Serial.println(rangeStart);
	Serial.print("Animation Range End: ");
	Serial.println(rangeEnd);

	Serial.println();
}
