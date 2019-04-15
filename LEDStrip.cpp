#pragma once

#include "LEDStrip.h"


LEDStrip::LEDStrip(CRGBSet* leds)
{
	vars = {
		leds,	// CRGBSet*
		0,		// curPattern
		255,	// brightness
		0,		// hue
		0,		// hueSpeed
		0,		// position
		0,		// speed
		0		// size
	};

	numLEDs = leds->len;

	power = true;

	stripAutoplay = false;
	stripAutoplayDuration = 10000;
}

LEDStrip::~LEDStrip()
{
}

void LEDStrip::UpdateStrip()
{
	UpdatePatternVars();

	patterns[vars.curPattern](vars);

	if (stripAutoplay && (millis() > stripAutoPlayTimeout)) {
		NextPattern();
		stripAutoPlayTimeout = millis() + (stripAutoplayDuration);
	}
}

void LEDStrip::UpdatePatternVars()
{
	/*with patternVars
	{
		hue += hueSpeed;
		position += speed;
	}*/
}

// Reset the timeouts for the strip when autoplay is turned on or after setup.
void LEDStrip::ResetTimeouts()
{
	stripAutoPlayTimeout = millis() + (stripAutoplayDuration);
}

void LEDStrip::NextPattern()
{
	vars.curPattern = (vars.curPattern + 1) % patternCount;
}

void LEDStrip::PrintStripInfo()
{
	
}