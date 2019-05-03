#pragma once

#include "LEDStrip.h"
#include "palettes.h"

LEDStrip::LEDStrip(CRGBSet* leds)
{
	D(startTime("LEDStrip::LEDStrip(CRGBSet leds)");)

	vars = {
		leds,		// CRGBSet
		leds->len,	// numLeds
		14,			// curPattern
		120,		// brightness
		0,			// hue
		1,			// hueSpeed
		0,			// hue2
		0,			// position
		1,			// speed
		10,			// size
		0,			// clockOffset
		palettes[0],// palette
		palettes[0]	// tPalette
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

		vars.hue += vars.hueSpeed;
		vars.position += vars.speed;

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