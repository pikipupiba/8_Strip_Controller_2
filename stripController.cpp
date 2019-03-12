#pragma once

#include "stripController.h"

// This constructor assumes WS2812B LEDs and bases the data pin on the strip index and ESP32 controller.
StripController::StripController(uint32_t newIndex, uint32_t newNumLEDs, Shapes newShape)
{
	stripNumLEDs = newNumLEDs;
	stripIndex = newIndex;

	stripShape = newShape;

	// Default values used for the rest of the strip variables.
	stripPower = true;
	stripBrightness = 255;

	autoplay = false;
	autoplayDuration = 10;

	cyclePalettes = false;
	paletteDuration = 10;

	curPattern = 0;
	curPaletteIndex = 0;

	curPalette = CRGBPalette16(CRGB::Black);
	tarPalette = palettes[0];


	if (stripIndex == 0)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_0, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
		stripLEDs = leds(stripIndex * NUM_LEDS_PER_STRIP, stripIndex * NUM_LEDS_PER_STRIP + stripNumLEDs);
	}
	else if (stripIndex == 1)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_1, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
		stripLEDs = leds(stripIndex * NUM_LEDS_PER_STRIP, stripIndex * NUM_LEDS_PER_STRIP + stripNumLEDs);
	}
	else if (stripIndex == 2)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_2, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
		stripLEDs = leds(stripIndex * NUM_LEDS_PER_STRIP, stripIndex * NUM_LEDS_PER_STRIP + stripNumLEDs);
	}
	else if (stripIndex == 3)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_3, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
		stripLEDs = leds(stripIndex * NUM_LEDS_PER_STRIP, stripIndex * NUM_LEDS_PER_STRIP + stripNumLEDs);
	}
	else if (stripIndex == 4)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_4, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
		stripLEDs = leds(stripIndex * NUM_LEDS_PER_STRIP, stripIndex * NUM_LEDS_PER_STRIP + stripNumLEDs);
	}
	else if (stripIndex == 5)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_5, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
		stripLEDs = leds(stripIndex * NUM_LEDS_PER_STRIP, stripIndex * NUM_LEDS_PER_STRIP + stripNumLEDs);
	}
	else if (stripIndex == 6)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_6, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
		stripLEDs = leds(stripIndex * NUM_LEDS_PER_STRIP, stripIndex * NUM_LEDS_PER_STRIP + stripNumLEDs);
	}
	else if (stripIndex == 7)
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN_7, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
		stripLEDs = leds(stripIndex * NUM_LEDS_PER_STRIP, stripIndex * NUM_LEDS_PER_STRIP + stripNumLEDs);
	}

}

void StripController::UpdateStrip()
{

	for (Animations* i : animation)
	{
		i->Update();
	}
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

// Reset the timeouts for the strip when autoplay is turned on or after setup.
void StripController::ResetTimeouts()
{
	autoPlayTimeout = millis() + (autoplayDuration * 1000);
	paletteTimeout = millis() + (paletteDuration * 1000);
}

// TODO will make this cycle through presets instead of patterns.
void StripController::NextPattern()
{
	// add one to the current pattern number and wrap around at the end
	curPattern = (curPattern + 1) % patternCount;
}

void StripController::NextPalette()
{
	// add one to the current palette number and wrap around at the end
	curPaletteIndex = (curPaletteIndex + 1) % paletteCount;
	tarPalette = palettes[curPaletteIndex];
}

void StripController::AddAnimation(uint32_t newAnimationPreset)
{
	if (numAnimations < NUM_ANIMATIONS_PER_STRIP)
	{
		numAnimations++;
		
		// TODO Figure out how to initialize an animation object like this.
		// This has not been worked on at all yet.
		// Will probably use a similar system to the following taken from my AnimationClassTest.ino at line 42.
		// typedef void(*SimplePatternList[])();
		// SimplePatternList gPatterns = { pattern1, pattern2, pattern3};

		animation[numAnimations] = new animationPreset[newAnimationPreset];
	}
}
