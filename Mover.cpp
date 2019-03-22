#pragma once

#include "Mover.h"
#include "display.h"



Mover::Mover()
{
	// Keep track of how many objects are currently running.
	numObjects++;

	// Default Mover covers the whole strip.
	rangeStart = 0;
	rangeEnd = NUM_LEDS_PER_STRIP;
	rangeSize = rangeEnd - rangeStart;

	animationShape = Shapes::Strip;
	animationTexture = Textures::None;
	animationEndOfRange = EndOfRanges::Bounce;

	brightness = 255;
	hue = 0;
	hueSpeed = 0.5;
	hueAcceleration = 0;

	featureSize = 10;
	position = rangeStart + featureSize / 2 + 2;
	speed = 0.2;
	acceleration = 0;

	end1 = position - featureSize / 2;
	end2 = position + featureSize / 2;

	numRepeats = 0;
	repeatPositionOffset = 0;
	repeatHueOffset = 0;
}


Mover::~Mover()
{
	numObjects--;
}

void Mover::Update()
{
	// TODO Implement ErasePrevFrame() so only the pixels used are modified. Speed bonus x1000 I'll bet.
	UpdatePosition();
	Draw();
}

void Mover::Draw()
{
	// Extract integer values from floats.
	int iEnd1 = (int)end1;
	int iEnd2 = (int)end2;
	int iHue = (int)hue;
	int iBrightness = (int)brightness;

	for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
	{
		animationLEDs[i] = CRGB::Black;
	}
	//animationLEDs[0, 300] = CRGB::Black;
	
	// The Mover is is within it's designated range.
	if (end1 < end2)
	{
		// Color in the Mover.
		for (int i = iEnd1; i <= iEnd2; i++)	{ animationLEDs[i] = CHSV(iHue, 255, iBrightness); }
		//animationLEDs[iEnd1, iEnd2] = hue; // Use this when I figure out CRGBSets
	}
	// The Mover is split between the ends of its range.
	else
	{
		for (int i = rangeStart; i <= iEnd2; i++)	{ animationLEDs[i] = CHSV(iHue, 255, iBrightness); }
		for (int i = iEnd1; i <= rangeEnd; i++)		{ animationLEDs[i] = CHSV(iHue, 255, iBrightness); }
	}

	animationLEDs[iEnd1] = CHSV(iHue, 255, iBrightness * (1 - (end1 - iEnd1)));
	animationLEDs[iEnd2] = CHSV(iHue, 255, iBrightness * (end2 - iEnd2));
}
