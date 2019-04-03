#include "stdafx.h"

#pragma once

#include "stripController.h"
#include "display.h"
#include "Animation.h"
#include "Mover.h"

// This constructor assumes WS2812B LEDs and bases the data pin on the strip index and ESP32 controller.
StripController::StripController(int newIndex, int newNumLEDs)//, Shapes newShape)
{
	D(startTime("StripController::StripController(int newIndex, int newNumLEDs)");)

	stripNumLEDs = newNumLEDs;
	stripIndex = newIndex;

	stripRangeStart = stripIndex * NUM_LEDS_PER_STRIP;
	stripRangeEnd = stripIndex * NUM_LEDS_PER_STRIP + stripNumLEDs;

	//stripShape = newShape;

	// Default values used for the rest of the strip variables.
	stripPower = true;
	stripBrightness = 255;

	stripAutoplay = false;
	stripAutoplayDuration = 11;

	stripCyclePalettes = false;
	stripPaletteDuration = 10;

	stripPatternIndex = 0;
	stripPaletteIndex = 0;

	stripNumPatterns = 0;

	//curPalette = CRGBPalette16(CRGB::Black);
	//tarPalette = palettes[0];


	if (stripIndex == 0)
	{ FastLED.addLeds<LED_TYPE, DATA_PIN_0, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip); }

	else if (stripIndex == 1)
	{ FastLED.addLeds<LED_TYPE, DATA_PIN_1, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip); }

	else if (stripIndex == 2)
	{ FastLED.addLeds<LED_TYPE, DATA_PIN_2, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip); }

	else if (stripIndex == 3)
	{ FastLED.addLeds<LED_TYPE, DATA_PIN_3, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip); }

	else if (stripIndex == 4)
	{ FastLED.addLeds<LED_TYPE, DATA_PIN_4, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip); }

	else if (stripIndex == 5)
	{ FastLED.addLeds<LED_TYPE, DATA_PIN_5, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip); }

	else if (stripIndex == 6)
	{ FastLED.addLeds<LED_TYPE, DATA_PIN_6, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip); }

	else if (stripIndex == 7)
	{ FastLED.addLeds<LED_TYPE, DATA_PIN_7, COLOR_ORDER>(leds, stripIndex * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip); }

	D(endTime("StripController::StripController(int newIndex, int newNumLEDs)");)
}

StripController::~StripController()
{
}

void StripController::UpdateStrip()
{
	D(startTime("StripController::UpdateStrip()");)

		/*for (Animations* i : animation)
		{
			debugCounter();
			i->Update();

			for (int j = 0; j < 100; j++)
			{
				//stripLEDs[j] += i->animationLEDs[j];
			}
		}*/

		//stripPatternList[stripCurPattern](int preset);

	for (int i = 0; i < stripNumPatterns; i++)
	{
		stripPatterns[i]->Update();
	}

	//FastLEDshowESP32();

	// Call the current pattern function once, updating the 'leds[index]' array
	//patterns[curPattern].pattern(index);

	EVERY_N_MILLISECONDS(20) {
		// slowly blend the current palette to the next
		nblendPaletteTowardPalette(stripPalette, stripTarPalette, 8);
	}

	// Advance the pattern and palette if applicable.
	// TODO Should this only happen if POWER is on?
	if (stripAutoplay && (millis() > stripAutoPlayTimeout)) {
		NextPattern();
		stripAutoPlayTimeout = millis() + (stripAutoplayDuration);
	}

	if (stripCyclePalettes && (millis() > stripPaletteTimeout)) {
		NextPalette();
		stripPaletteTimeout = millis() + (stripPaletteDuration);
	}

	D(endTime("StripController::UpdateStrip()");)
}

// Reset the timeouts for the strip when autoplay is turned on or after setup.
void StripController::ResetTimeouts()
{
	stripAutoPlayTimeout = millis() + (stripAutoplayDuration);
	stripPaletteTimeout = millis() + (stripPaletteDuration);
}

// TODO will make this cycle through presets instead of patterns.
void StripController::NextPattern()
{
	//stripPatternIndex = (stripPatternIndex + 1) % ARRAY_SIZE(patterns);
}

void StripController::NextPalette()
{
	// add one to the current palette number and wrap around at the end
	//curPaletteIndex = (curPaletteIndex + 1) % paletteCount;
	//tarPalette = palettes[curPaletteIndex];
}

void StripController::AddPattern()
{
	D(startTime("StripController::AddAnimation()");)

	if (stripNumPatterns < NUM_PATTERNS_PER_STRIP)
	{
		
		// TODO Figure out how to initialize an animation object like this.
		// This has not been worked on at all yet.
		// Will probably use a similar system to the following taken from my AnimationClassTest.ino at line 42.
		// typedef void(*SimplePatternList[])();
		// SimplePatternList gPatterns = { pattern1, pattern2, pattern3};

		stripPatterns[stripNumPatterns] = new PatternClass(this, "Color Waves");

		stripNumPatterns++;
	}

	D(endTime("StripController::AddAnimation()");)
}

void StripController::AddPattern(String newAnimation, float newPosition, float newSpeed, float newHue, int newRangeStart, int newRangeEnd)
{
	D(startTime("StripController::AddAnimation(int stufff)");)

	if (newAnimation == "Mover")
	{
		if (stripNumPatterns < NUM_PATTERNS_PER_STRIP)
		{
			//stripPatterns[stripNumPatterns] = new Mover(this, newPosition, newSpeed, newHue, newRangeStart, newRangeEnd);

			stripNumPatterns++;
		}
	}
	D(endTime("StripController::AddAnimation(int stufff)");)
}

void StripController::PrintStripInfo()
{
	D(startTime("StripController::PrintStripInfo()");)

		Serial.println();

	Serial.print("Strip Index #: ");
	Serial.println(stripIndex);
	Serial.print("Number of LEDs: ");
	Serial.println(stripNumLEDs);

	Serial.print("Strip Range Start: ");
	Serial.println(stripRangeStart);
	Serial.print("Strip Range End: ");
	Serial.println(stripRangeEnd);

	Serial.print("Num Animations: ");
	Serial.println(stripNumPatterns);

	Serial.println();

	D(endTime("StripController::PrintStripInfo()");)
}

void StripController::ClearPatterns()
{
	D(startTime("StripController::ClearPatterns()");)

	for (int i = stripNumPatterns - 1; i >= 0; i--)
	{
		if (stripPatterns[i] == NULL)
		{
		}
		else
		{
			delete stripPatterns[i];
			stripPatterns[i] = NULL;

			stripNumPatterns--;
		}
	}

	D(endTime("StripController::ClearPatterns()");)
}