// 
// 
// 

#include "stripController.h"

// This constructor assumes WS2812B LEDs and bases the data pin on the strip number and ESP32 controller.
StripController::StripController(uint8_t newIndex, uint16_t newNumLEDs, Shapes newShape)
{
	numLEDs = newNumLEDs;
	index = newIndex;

	shape = newShape;

	power = true;
	brightness = 255;

	curPos = 0;
	speed = 0;
	curHue = 0;
	hueSpeed = 0;

	bool autoplay = false;
	uint8_t autoplayDuration = 10;

	cyclePalettes = false;
	paletteDuration = 10;

	curPattern = 0;
	curPaletteIndex = 0;

	curPalette = CRGBPalette16(CRGB::Black);
	tarPalette = palettes[0];

	if (index == 0)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_0, COLOR_ORDER>(leds[index], 0, numLEDs).setCorrection(TypicalLEDStrip);
	}
	else if (index == 1)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_1, COLOR_ORDER>(leds[index], 0, numLEDs).setCorrection(TypicalLEDStrip);
	}
	else if (index == 2)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_2, COLOR_ORDER>(leds[index], 0, numLEDs).setCorrection(TypicalLEDStrip);
	}
	else if (index == 3)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_3, COLOR_ORDER>(leds[index], 0, numLEDs).setCorrection(TypicalLEDStrip);
	}
	else if (index == 4)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_4, COLOR_ORDER>(leds[index], 0, numLEDs).setCorrection(TypicalLEDStrip);
	}
	else if (index == 5)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_5, COLOR_ORDER>(leds[index], 0, numLEDs).setCorrection(TypicalLEDStrip);
	}
	else if (index == 6)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_6, COLOR_ORDER>(leds[index], 0, numLEDs).setCorrection(TypicalLEDStrip);
	}
	else if (index == 7)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_7, COLOR_ORDER>(leds[index], 0, numLEDs).setCorrection(TypicalLEDStrip);
	}

}

void StripController::updateStrip()
{
	// Call the current pattern function once, updating the 'leds[index]' array
	patterns[curPattern].pattern(index);

	EVERY_N_MILLISECONDS(20) {
		// slowly blend the current palette to the next
		nblendPaletteTowardPalette(curPalette, tarPalette, 8);
		curHue += hueSpeed;  // slowly cycle the "base color" through the rainbow
	}

	// Advance the pattern and palette if applicable.
	// TODO Should this only happen if POWER is on?
	if (autoplay && (millis() > autoPlayTimeout)) {
		nextPattern();
		autoPlayTimeout = millis() + (autoplayDuration * 1000);
	}

	if (cyclePalettes && (millis() > paletteTimeout)) {
		nextPalette();
		paletteTimeout = millis() + (paletteDuration * 1000);
	}
}

void StripController::resetTimeouts()
{
	autoPlayTimeout = millis() + (autoplayDuration * 1000);
	paletteTimeout = millis() + (paletteDuration * 1000);
}

void StripController::nextPattern()
{
	// add one to the current pattern number and wrap around at the end
	curPattern = (curPattern + 1) % patternCount;
}

void StripController::nextPalette()
{
	// add one to the current palette number and wrap around at the end
	curPaletteIndex = (curPaletteIndex + 1) % paletteCount;
	tarPalette = palettes[curPaletteIndex];
}

uint8_t StripController::getLength()
{
	return numLEDs;
}

int StripController::getSpeed()
{
	return int(speed);
}
