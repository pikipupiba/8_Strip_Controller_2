#pragma once

#include "Mover.h"
//#include "normalizeValues.h"


Mover::Mover()
{
	rangeStart = 0;
	rangeEnd = uINT32_MAX;
	rangeSize = rangeEnd - rangeStart; // Automatically calculated rangeSize for easier to read code.

	animationShape = Strip;				// The shape of the strip the animation is playing on.
	animationTexture = None;			// A modifier applied to the animation after values are calculated.
	animationEndOfRange = Bounce;	// How an animation acts when it approaches the end of its range.

	brightness = uINT32_MAX;
	hue = 0;			// Hue is the starting value used to calculate the various colors in an animation step.
	hueSpeed = uINT32_MAX / 2000;			// Hue speed is how much hue changes each step.
	hueAcceleration = 0;	// Hue acceleration is how much hue speed changes each step.

	position = (rangeStart + rangeEnd) / 2;		// Position can either be where an object is in its range or the current step in a sequence it is on.
	speed = 0;				// How much position changes each step.
	acceleration = 0;		// How much speed changes each step.

	featureSize = rangeSize / 20;	// Used to describe the size of a "feature" of the animation. Usually equals end2 - end1.
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
	float fEnd1 = uint32_to_float(end1, 0, 300);
	float fEnd2 = uint32_to_float(end2, 0, 300);

	int iEnd1 = (int)fEnd1;
	int iEnd2 = (int)fEnd2;

	animationLEDs[0, 300] = CRGB::Black;

	if (end1 < end2)
	{
		animationLEDs[iEnd1, iEnd2] = hue;
	}
	else
	{
		animationLEDs[iEnd1, uint32_to_uint32(rangeEnd,0,300)];
		animationLEDs[uint32_to_uint32(rangeStart, 0, 300), iEnd2];
	}

	animationLEDs[(int)fEnd1] *= 1 - fEnd1 + iEnd1;
	animationLEDs[(int)fEnd2] *= fEnd2 - iEnd2;

}
