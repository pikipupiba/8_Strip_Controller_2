#pragma once

#include "LEDStrip.h"


// This constructor assumes WS2812B LEDs and bases the data pin on the strip index and ESP32 controller.
LEDStrip::LEDStrip(CRGBSet* leds)//, Shapes newShape)
{
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
