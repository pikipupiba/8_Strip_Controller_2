#pragma once

#include "LEDStrip.h"


LEDStrip::LEDStrip(CRGBSet leds)
{
	numLEDs = leds.len;

	power = true;

	stripAutoplay = false;
	stripAutoplayDuration = 10000;
}

LEDStrip::~LEDStrip()
{
}

void LEDStrip::UpdateStrip()
{
	curPattern->Update();

	if (stripAutoplay && (millis() > stripAutoPlayTimeout)) {
		NextPattern();
		stripAutoPlayTimeout = millis() + (stripAutoplayDuration);
	}
}

// Reset the timeouts for the strip when autoplay is turned on or after setup.
void LEDStrip::ResetTimeouts()
{
	stripAutoPlayTimeout = millis() + (stripAutoplayDuration);
}

// TODO will make this cycle through presets instead of patterns.
void LEDStrip::NextPattern()
{
	curPattern->Next();
}

void LEDStrip::PrintStripInfo()
{
	
}
