#include "stdafx.h"

#pragma once

#include "ColorWave.h"
#include "display.h"
#include "stripController.h"



ColorWave::ColorWave(StripController* newStrip)
{
}

ColorWave::ColorWave(StripController * newStrip, aniArg newAniArgs[])
{
	D(startTime("ColorWave::ColorWave(StripController * newStrip, aniArg newAniArgs[])");)

		strip = newStrip;

	// Default Mover covers the whole strip.
	rangeStart = strip->stripRangeStart;
	rangeEnd = strip->stripRangeEnd;
	rangeSize = rangeEnd - rangeStart;

	position = rangeStart + rangeSize / 2;

	end1 = position - featureSize / 2;
	end2 = position + featureSize / 2;

	AssignVals(newAniArgs);

	D(endTime("ColorWave::ColorWave(StripController * newStrip, aniArg newAniArgs[])");)
}


ColorWave::~ColorWave()
{
	Erase();
	numObjects--;
}

void ColorWave::Erase()
{
	for (int i = (int)rangeStart; i < (int)rangeEnd; i++)
	{
		leds[i] -= CHSV(((int)((eHue + i) * eFeatureSize)) % 255, 255, (int)eBrightness);
	}
}

void ColorWave::Draw()
{
	for (int i = (int)rangeStart; i < (int)rangeEnd; i++) 
	{
		leds[i] += CHSV( ( (int)((hue + i) * featureSize) ) % 255, 255, (int)brightness);
	}
}
