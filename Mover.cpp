#include "stdafx.h"

#pragma once

#include "Mover.h"
#include "display.h"
#include "stripController.h"

Mover::Mover(StripController* newStrip)
{
	D(startTime("Mover::Mover(int stufff)");)

		strip = newStrip;

	// Default Mover covers the whole strip.
	rangeStart = strip->stripRangeStart;
	rangeEnd = strip->stripRangeEnd;
	rangeSize = rangeEnd - rangeStart;

	position = rangeStart + rangeSize / 2;
	
	end1 = position - featureSize / 2;
	end2 = position + featureSize / 2;

	Draw();

	SetEraseVals();

	D(endTime("Mover::Mover(int stufff)");)
}


Mover::~Mover()
{
	Erase();
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
		for (int i = iEnd1 + 1; i < iEnd2; i++) { leds[i] += CHSV(iHue, 255, iBrightness); }
	}
		//animationLEDs[iEnd1 + 1, iEnd2 - 1] = hue; // Use this when I figure out CRGBSets
	
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
	static int iEnd1 = (int)eEnd1;
	static int iEnd2 = (int)eEnd2;
	static int iHue = (int)eHue;
	static int iBrightness = (int)eBrightness;

	iEnd1 = (int)eEnd1;
	iEnd2 = (int)eEnd2;
	iHue = (int)eHue;
	iBrightness = (int)eBrightness;

	// The Mover is is within it's designated range.
	if (iEnd1 < iEnd2)
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
	leds[iEnd1] -= CHSV(iHue, 255, iBrightness * (1 - (eEnd1 - iEnd1)));
	leds[iEnd2] -= CHSV(iHue, 255, iBrightness * (eEnd2 - iEnd2));

	D(endTime("Mover::Erase()"));
}