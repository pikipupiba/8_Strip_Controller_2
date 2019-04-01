#include "stdafx.h"

#pragma once

#include "Mover.h"
#include "display.h"
#include "stripController.h"


Mover::Mover(StripController* newStrip) // :Animations(newStrip) // TODO Figure out how initialization lists work.
{
	D(startTime("Mover::Mover(StripController* newStrip)");)

	// Keep track of how many objects are currently running.
	numObjects++;

	strip = newStrip;

	// Default Mover covers the whole strip.
	rangeStart = strip->stripRangeStart;
	rangeEnd = strip->stripRangeEnd;
	rangeSize = rangeEnd - rangeStart;

	animationShape = Shapes::Strip;
	animationTexture = Textures::None;
	animationEndOfRange = EndOfRanges::Bounce;

	brightness = 128;
	hue = 0;
	hueSpeed = 0.5;
	hueAcceleration = 0;

	featureSize = 10;
	position = rangeStart + rangeSize / 2;
	speed = 0.1;
	acceleration = 0;

	end1 = position - featureSize / 2;
	end2 = position + featureSize / 2;

	numRepeats = 0;
	repeatPositionOffset = 0;
	repeatHueOffset = 0;

	changing = 0;

	D(endTime("Mover::Mover(StripController* newStrip)");)
}

Mover::Mover(StripController * newStrip, float newPosition, float newSpeed, float newHue, int newRangeStart, int newRangeEnd)
{
	D(startTime("Mover::Mover(int stufff)");)

		// Keep track of how many objects are currently running.
	numObjects++;

	strip = newStrip;

	// Default Mover covers the whole strip.
	rangeStart = newRangeStart;
	rangeEnd = newRangeEnd;
	rangeSize = rangeEnd - rangeStart;

	animationShape = Shapes::Strip;
	animationTexture = Textures::None;
	animationEndOfRange = EndOfRanges::Bounce;

	brightness = 128;
	hue = newHue;
	hueSpeed = 0.5;
	hueAcceleration = 0;

	featureSize = 3;
	position = newPosition;
	speed = newSpeed;
	acceleration = 0;

	end1 = position - featureSize / 2;
	end2 = position + featureSize / 2;

	numRepeats = 0;
	repeatPositionOffset = 0;
	repeatHueOffset = 0;

	changing = 0;

	D(endTime("Mover::Mover(int stufff)");)
}


Mover::~Mover()
{
	Erase();
	numObjects--;
}

void Mover::Draw()
{
	D(startTime("Mover::Draw()");)

	// Extract integer values from floats.
	static int iEnd1 = (int)end1;
	static int iEnd2 = (int)end2;
	static int iHue = (int)hue;
	static int iBrightness = (int)brightness;

	iEnd1 = (int)end1;
	iEnd2 = (int)end2;
	iHue = (int)hue;
	iBrightness = (int)brightness;

	// The Mover is is within it's designated range.
	if (end1 < end2)
	{
		// Color in the Mover.
		for (int i = iEnd1 + 1; i < iEnd2; i++)	{ leds[i] += CHSV(iHue, 255, iBrightness); }
		//animationLEDs[iEnd1 + 1, iEnd2 - 1] = hue; // Use this when I figure out CRGBSets
	}
	// The Mover is split between the ends of its range.
	else
	{
		for (int i = rangeStart; i < iEnd2; i++)	{ leds[i] += CHSV(iHue, 255, iBrightness); }
		for (int i = iEnd1 + 1; i <= rangeEnd; i++)	{ leds[i] += CHSV(iHue, 255, iBrightness); }
	}

	// Draw the antialiased ends of the Mover.
	leds[iEnd1] += CHSV(iHue, 255, iBrightness * (1 - (end1 - iEnd1)));
	leds[iEnd2] += CHSV(iHue, 255, iBrightness * (end2 - iEnd2));

	D(endTime("Mover::Draw()"));
}


// The exact opposit of Draw()
void Mover::Erase()
{
	D(startTime("Mover::Erase()");)

	// Extract integer values from floats.
	static int iEnd1 = (int)end1;
	static int iEnd2 = (int)end2;
	static int iHue = (int)hue;
	static int iBrightness = (int)brightness;

	iEnd1 = (int)end1;
	iEnd2 = (int)end2;
	iHue = (int)hue;
	iBrightness = (int)brightness;

	// The Mover is is within it's designated range.
	if (end1 < end2)
	{
		// Color in the Mover.
		for (int i = iEnd1 + 1; i < iEnd2; i++) { leds[i] -= CHSV(iHue, 255, iBrightness); }
		//animationLEDs[iEnd1 + 1, iEnd2 - 1] = hue; // Use this when I figure out CRGBSets
	}
	// The Mover is split between the ends of its range.
	else
	{
		for (int i = rangeStart; i < iEnd2; i++) { leds[i] -= CHSV(iHue, 255, iBrightness); }
		for (int i = iEnd1 + 1; i <= rangeEnd; i++) { leds[i] -= CHSV(iHue, 255, iBrightness); }
	}

	// Draw the antialiased ends of the Mover.
	leds[iEnd1] -= CHSV(iHue, 255, iBrightness * (1 - (end1 - iEnd1)));
	leds[iEnd2] -= CHSV(iHue, 255, iBrightness * (end2 - iEnd2));

	D(endTime("Mover::Erase()"));
}