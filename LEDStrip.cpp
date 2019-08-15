#pragma once

#include "LEDStrip.h"
#include "palettes.h"

LEDStrip::LEDStrip(CRGBSet* leds)
{
	D(startTime("LEDStrip::LEDStrip(CRGBSet leds)");)

		vars = {
			leds,		// CRGBSet
			leds->len,	// numLeds on top
			6,			// curPattern
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
			0,			// paletteNum
			palettes[0],	// tPalette
			0,			// tPaletteNum
			false,		// autoplay
			15000,		//autoplayDuration
			false,		// cyclePalettes
			10000,		// paletteDuration
			1,			// hueSpeedFactor
			1,			// speedScaleFactor
			{0,0,0,0,0,0}, // Height
			{0,0,0,0,0,0}, // Impact Velocity
			{0,0,0,0,0,0}, // Time Since Last Bounce
			{0,0,0,0,0,0}, // Position
			{0,0,0,0,0,0}, // PrevPosition
			{0,0,0,0,0,0}, // Clock Time since last bounce
			{0,0,0,0,0,0}, // Dampening
			false,			// started
			true
	};

	if (vars.reflect)
	{
		vars.numLeds /= 2;
	}

	power = true;

	stripAutoplayTimeout = millis() + vars.autoplayDuration;
	stripPaletteTimeout = millis() + vars.paletteDuration;

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

	// reflect strip at center
	if (vars.reflect)
	{
		for (int i = 0; i < vars.numLeds; i++)
		{
			vars.leds[0][vars.numLeds * 2 - i - 1] = vars.leds[0][i];
		}
	}

	//if (vars.autoplay && (millis() > stripAutoplayTimeout)) {
	//	NextPattern();
	//	stripAutoplayTimeout = millis() + (vars.autoplayDuration);
	//}

	if (vars.cyclePalettes && (millis() > stripPaletteTimeout)) {
		NextPalette();
		stripPaletteTimeout = millis() + (vars.paletteDuration);
	}

	nblendPaletteTowardPalette(vars.palette, vars.targetPalette, 4);

	D(endTime("LEDStrip::UpdateStrip()");)
}

// advance position and hue based on speed and hueSpeed
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
	stripPaletteTimeout = millis() + vars.paletteDuration;

	D(endTime("LEDStrip::ResetTimeouts()");)
}

void LEDStrip::NextPattern()
{
	D(startTime("LEDStrip::NextPattern()");)

		vars.speed = 1;
	vars.hueSpeed = 1;

	vars.curPattern = (vars.curPattern + 1) % patternCount;

	D(endTime("LEDStrip::NextPattern()");)
}

void LEDStrip::PrevPattern()
{

	vars.speed = 1;
	vars.hueSpeed = 1;

	vars.curPattern = (vars.curPattern - 1);

	if (vars.curPattern < 0)
	{
		vars.curPattern = patternCount - 1;
	}

}

void LEDStrip::SetPattern(int newPatternNum)
{
	//vars.speed = 1;
	//vars.hueSpeed = 1;

	vars.curPattern = newPatternNum;
}

void LEDStrip::NextPalette()
{
	vars.targetPaletteNum = (vars.targetPaletteNum + 1) % paletteCount;
	vars.targetPalette = palettes[vars.targetPaletteNum];
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
