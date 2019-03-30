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

	stripNumAnimations = 0;

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

	for (int i = 0; i < stripNumAnimations; i++)
	{
		stripAnimations[i]->Update();
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

void StripController::AddAnimation()
{
	D(startTime("StripController::AddAnimation()");)

	if (stripNumAnimations < NUM_ANIMATIONS_PER_STRIP)
	{
		
		// TODO Figure out how to initialize an animation object like this.
		// This has not been worked on at all yet.
		// Will probably use a similar system to the following taken from my AnimationClassTest.ino at line 42.
		// typedef void(*SimplePatternList[])();
		// SimplePatternList gPatterns = { pattern1, pattern2, pattern3};

		stripAnimations[stripNumAnimations] = new Mover(this);

		stripNumAnimations++;
	}

	D(endTime("StripController::AddAnimation()");)
}

void StripController::AddAnimation(String newAnimation, float newPosition, float newSpeed, float newHue, int newRangeStart, int newRangeEnd)
{
	D(startTime("StripController::AddAnimation(int stufff)");)

	if (newAnimation == "Mover")
	{
		if (stripNumAnimations < NUM_ANIMATIONS_PER_STRIP)
		{
			stripAnimations[stripNumAnimations] = new Mover(this, newPosition, newSpeed, newHue, newRangeStart, newRangeEnd);

			stripNumAnimations++;
		}
	}
	D(endTime("StripController::AddAnimation(int stufff)");)
}

void StripController::PrintStripInfo()
{
	D(startTime("StripController::PrintStripInfo()");)

	Serial.print("Strip Index #: ");
	Serial.println(stripIndex);
	Serial.print("Number of LEDs: ");
	Serial.println(stripNumLEDs);
	Serial.print("Num Animations: ");
	Serial.println(stripNumAnimations);

	D(endTime("StripController::PrintStripInfo()");)
}

void StripController::ClearAnimations()
{
	D(startTime("StripController::ClearAnimations()");)

	for (int i = stripNumAnimations - 1; i >= 0; i--)
	{
		if (stripAnimations[i] == NULL)
		{
		}
		else
		{
			delete stripAnimations[i];
			stripAnimations[i] = NULL;

			stripNumAnimations--;
		}
	}

	D(endTime("StripController::ClearAnimations()");)
}

/*void StripController::PoopyWorm1()
{
	D(startTime("poopyWorm1");)

		static int stage = 0;

	// TODO Move these to being time dependant like displaying the menu.
	switch (stage)
	{
	case 0:

		D(middleTime("Poopy worm 1 case 0");)

			ClearAnimations();

		for (int i = 0; i < NUM_ANIMATIONS_PER_STRIP; i++)
		{
			AddAnimation("Mover", stripRangeStart + 5, 0.2, i * (255 / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}
		stage++;
		break;

	case 1:

		D(middleTime("Poopy worm 1 case 1");)

			ClearAnimations();

		for (int i = 0; i < NUM_ANIMATIONS_PER_STRIP; i++)
		{
			AddAnimation("Mover", stripRangeEnd - 5, -0.2, i * (255 / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}
		stage = 0;
		break;
	}

	D(endTime("poopyWorm1");)
}

void StripController::PoopyWorm2()
{
	D(startTime("poopyWorm2");)

		static int stage = 0;


	switch (stage)
	{
	case 0:

		D(middleTime("Poopy worm 2 case 0");)

			ClearAnimations();

		for (int i = 0; i < NUM_ANIMATIONS_PER_STRIP / 2; i++)
		{
			AddAnimation("Mover", stripRangeStart + 5, 0.1, i * (255 / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}
		for (int i = NUM_ANIMATIONS_PER_STRIP / 2; i < NUM_ANIMATIONS_PER_STRIP; i++)
		{
			AddAnimation("Mover", stripRangeEnd - 5, -0.1, i * (255 / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}

		stage++;
		break;

	case 1:

		D(middleTime("Poopy worm 2 case 1");)

			ClearAnimations();

		for (int i = 0; i < NUM_ANIMATIONS_PER_STRIP / 2; i++)
		{
			AddAnimation("Mover", (stripRangeStart + stripRangeEnd) / 2, -0.1, i * (255 / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}
		for (int i = NUM_ANIMATIONS_PER_STRIP / 2; i < NUM_ANIMATIONS_PER_STRIP; i++)
		{
			AddAnimation("Mover", (stripRangeStart + stripRangeEnd) / 2, 0.1, i * (255 / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}

		stage = 0;
		break;
	}

	D(endTime("poopyWorm2");)
}
*/