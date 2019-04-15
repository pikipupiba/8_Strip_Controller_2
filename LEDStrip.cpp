#pragma once

#include "LEDStrip.h"


LEDStrip::LEDStrip(CRGBSet* leds)
{
	D(startTime("LEDStrip::LEDStrip(CRGBSet leds)");)

	vars = {
		leds,		// CRGBSet
		leds->len,	// numLeds
		0,			// curPattern
		255,		// brightness
		0,			// hue
		0,			// hueSpeed
		0,			// position
		0,			// speed
		0			// size
	};

	power = true;

	stripAutoplay = false;
	stripAutoplayDuration = 10000;

	D(endTime("LEDStrip::LEDStrip(CRGBSet leds)");)
}

LEDStrip::~LEDStrip()
{
}

void LEDStrip::UpdateStrip()
{
	D(startTime("LEDStrip::UpdateStrip()");)

	UpdatePatternVars();

	patterns[vars.curPattern](vars);

	if (stripAutoplay && (millis() > stripAutoPlayTimeout)) {
		NextPattern();
		stripAutoPlayTimeout = millis() + (stripAutoplayDuration);
	}

	D(endTime("LEDStrip::UpdateStrip()");)
}

void LEDStrip::UpdatePatternVars()
{
	D(startTime("LEDStrip::UpdatePatternVars()");)

	/*with patternVars
	{
		hue += hueSpeed;
		position += speed;
	}*/

	D(endTime("LEDStrip::UpdatePatternVars()");)
}

// Reset the timeouts for the strip when autoplay is turned on or after setup.
void LEDStrip::ResetTimeouts()
{
	D(startTime("LEDStrip::ResetTimeouts()");)

	stripAutoPlayTimeout = millis() + (stripAutoplayDuration);

	D(endTime("LEDStrip::ResetTimeouts()");)
}

void LEDStrip::NextPattern()
{
	D(startTime("LEDStrip::NextPattern()");)

	vars.curPattern = (vars.curPattern + 1) % patternCount;

	D(endTime("LEDStrip::NextPattern()");)
}

void LEDStrip::PrintStripInfo()
{
	
}