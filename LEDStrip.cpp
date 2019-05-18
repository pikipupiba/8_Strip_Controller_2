#pragma once

#include "LEDStrip.h"
#include "palettes.h"

LEDStrip::LEDStrip(CRGBSet* leds)
{
	D(startTime("LEDStrip::LEDStrip(CRGBSet leds)");)

		vars = {
			leds,		// CRGBSet
			leds->len,	// numLeds
			1,			// curPattern
			255,		// brightness
			0,			// hue
			1,			// hueSpeed
			0,			// hue2
			0,			// position
			1,			// speed
			10,			// size
			0,			// positionOffset
			0,			// clockOffset
			palettes[0],// palette
			palettes[0],	// tPalette
			false,
			5000,
			1,
			1
	};

	power = true;

	stripAutoplayTimeout = millis() + vars.autoplayDuration;

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

	if (vars.autoplay && (millis() > stripAutoplayTimeout)) {
		NextPattern();
		stripAutoplayTimeout = millis() + (vars.autoplayDuration);
	}

	D(endTime("LEDStrip::UpdateStrip()");)
}

void LEDStrip::UpdatePatternVars()
{
	D(startTime("LEDStrip::UpdatePatternVars()");)

		vars.hue += vars.hueSpeed * vars.hueScaleFactor;
		vars.position += vars.speed * vars.speedScaleFactor;

	D(endTime("LEDStrip::UpdatePatternVars()");)
}

// Reset the timeouts for the strip when autoplay is turned on or after setup.
void LEDStrip::ResetTimeouts()
{
	D(startTime("LEDStrip::ResetTimeouts()");)

	stripAutoplayTimeout = millis() + (vars.autoplayDuration);

	D(endTime("LEDStrip::ResetTimeouts()");)
}

void LEDStrip::NextPattern()
{
	D(startTime("LEDStrip::NextPattern()");)

	vars.curPattern = (vars.curPattern + 1) % patternCount;

	D(endTime("LEDStrip::NextPattern()");)
}

void LEDStrip::ChangeVars(float newSpeed, float newHueSpeed, int newOffset, float newHue)
{
	vars.speed = newSpeed;
	vars.hue = newHue;
	vars.hueSpeed = newHueSpeed;
	vars.positionOffset = newOffset;
}

void LEDStrip::PrintStripInfo()
{
	
}