#include "stdafx.h"

#pragma once

// These patterns were the sample patterns that came with the ESP32 Web server example by Jason Coon.
// My new patterns will create and destroy animation objects as needed to create the desired effect.
// The patterns will have access to the animation[] array of each strip and associated parameters.
// I haven't quite figured out how this will work but you can check out my AnimationClassTest repo to see how that worked out.

#include "stripController.h"
#include "Animations.h"
#include "Mover.h"

#include "display.h"

/*
   ESP32 FastLED WebServer: https://github.com/jasoncoon/esp32-fastled-webserver
   Copyright (C) 2017 Jason Coon

   Built upon the amazing FastLED work of Daniel Garcia and Mark Kriegsman:
   https://github.com/FastLED/FastLED

   ESP32 support provided by the hard work of Sam Guyer:
   https://github.com/samguyer/FastLED

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

void rainbow()
{
	// FastLED's built-in rainbow generator
	//fill_rainbow(leds[0], NUM_LEDS, gHue, speed/10);
}

void addGlitter(fract8 chanceOfGlitter)
{
	/*if (random8() < chanceOfGlitter) {
		leds[0][random16(NUM_LEDS)] += CRGB::White;
	}*/
}

void rainbowWithGlitter()
{
	// built-in FastLED rainbow, plus some random sparkly glitter
	//rainbow();
	//addGlitter(80);
}

void confetti()
{
	// random colored speckles that blink in and fade smoothly
	/*fadeToBlackBy(leds[0], NUM_LEDS, 10);
	int pos = random16(NUM_LEDS);
	leds[0][pos] += CHSV(gHue + random8(64), 200, 255);*/
}

void sinelon()
{
	// a colored dot sweeping back and forth, with fading trails
	/*fadeToBlackBy(leds[0], NUM_LEDS, 20);
	int pos = beatsin16(speed/10, 0, NUM_LEDS_PER_STRIP - 1);
	static int prevpos = 0;
	CRGB color = ColorFromPalette(palettes[currentPaletteIndex], gHue, 255);
	if (pos < prevpos) {
		fill_solid(leds[0] + pos, (prevpos - pos) + 1, color);
	}
	else {
		fill_solid(leds[0] + prevpos, (pos - prevpos) + 1, color);
	}
	prevpos = pos;*/
}

void bpm()
{
	// colored stripes pulsing at a defined Beats-Per-Minute (BPM)
	/*uint8_t beat = beatsin8(speed/1.5, 64, 255);
	CRGBPalette16 palette = palettes[currentPaletteIndex];
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[0][i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
	}*/
}

void juggle() {
	// eight colored dots, weaving in and out of sync with each other
	/*fadeToBlackBy(leds[0], NUM_LEDS, 20);
	byte dothue = 0;
	for (int i = 0; i < 8; i++) {
		leds[0][beatsin16(i + speed/20, 0, NUM_LEDS_PER_STRIP - 1)] |= CHSV(dothue, 200, 255);
		dothue += 32;
	}*/
}

void showSolidColor()
{
	//fill_solid(leds[0], NUM_LEDS, solidColor);
}

void showSolidColorChanging()
{
	//fill_solid(leds, gHue);
}

// based on FastLED example Fire2012WithPalette: https://github.com/FastLED/FastLED/blob/master/examples/Fire2012WithPalette/Fire2012WithPalette.ino
void heatMap(CRGBPalette16 palette, bool up)
{
	/*fill_solid(leds[0], NUM_LEDS_PER_STRIP, CRGB::Black);

	// Add entropy to random number generator; we use a lot of it.
	random16_add_entropy(random(256));

	// Array of temperature readings at each simulation cell
	static byte heat[NUM_LEDS_PER_STRIP];

	byte colorindex;

	// Step 1.  Cool down every cell a little
	for (uint16_t i = 0; i < NUM_LEDS_PER_STRIP; i++) {
		heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / NUM_LEDS) + 2));
	}

	// Step 2.  Heat from each cell drifts 'up' and diffuses a little
	for (uint16_t k = NUM_LEDS_PER_STRIP - 1; k >= 2; k--) {
		heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
	}

	// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
	if (random8() < sparking) {
		int y = random8(7);
		heat[y] = qadd8(heat[y], random8(160, 255));
	}

	// Step 4.  Map from heat cells to LED colors
	for (uint16_t j = 0; j < NUM_LEDS_PER_STRIP; j++) {
		// Scale the heat value from 0-255 down to 0-240
		// for best results with color palettes.
		colorindex = scale8(heat[j], 190);

		CRGB color = ColorFromPalette(palette, colorindex);

		if (up) {
			leds[0][j] = color;
		}
		else {
			leds[0][(NUM_LEDS_PER_STRIP - 1) - j] = color;
		}
	}*/
}

void fire()
{
	//heatMap(HeatColors_p, true);
}

void water()
{
	/*heatMap(IceColors_p, false);*/
}

// Pride2015 by Mark Kriegsman: https://gist.github.com/kriegsman/964de772d64c502760e5
// This function draws rainbows with an ever-changing,
// widely-varying set of parameters.
void pride()
{
	/*
	static uint16_t sPseudotime = 0;
	static uint16_t sLastMillis = 0;
	static uint16_t sHue16 = 0;

	uint8_t sat8 = beatsin88(87, 220, 250);
	uint8_t brightdepth = beatsin88(341, 96, 224);
	uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
	uint8_t msmultiplier = beatsin88(147, 23, 60);

	uint16_t hue16 = sHue16;//gHue * 256;
	uint16_t hueinc16 = beatsin88(113, 1, 3000);

	uint16_t ms = millis();
	uint16_t deltams = ms - sLastMillis;
	sLastMillis = ms;
	sPseudotime += deltams * msmultiplier;
	sHue16 += deltams * beatsin88(400, 5, 9);
	uint16_t brightnesstheta16 = sPseudotime;

	for (uint16_t i = 0; i < NUM_LEDS; i++) {
		hue16 += hueinc16;
		uint8_t hue8 = hue16 / 256;

		brightnesstheta16 += brightnessthetainc16;
		uint16_t b16 = sin16(brightnesstheta16) + 32768;

		uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
		uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
		bri8 += (255 - brightdepth);

		CRGB newcolor = CHSV(hue8, sat8, bri8);

		uint16_t pixelnumber = i;
		pixelnumber = (NUM_LEDS - 1) - pixelnumber;

		nblend(leds[0][pixelnumber], newcolor, 64);
	}*/
}

// ColorWavesWithPalettes by Mark Kriegsman: https://gist.github.com/kriegsman/8281905786e8b2632aeb
// This function draws color waves with an ever-changing,
// widely-varying set of parameters, using a color palette.
void colorwaves(CRGB* ledarray, uint16_t numleds, CRGBPalette16& palette)
{
	/*static uint16_t sPseudotime = 0;
	static uint16_t sLastMillis = 0;
	static uint16_t sHue16 = 0;

	// uint8_t sat8 = beatsin88( 87, 220, 250);
	uint8_t brightdepth = beatsin88(341, 96, 224);
	uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
	uint8_t msmultiplier = beatsin88(147, 23, 60);

	uint16_t hue16 = sHue16;//gHue * 256;
	uint16_t hueinc16 = beatsin88(113, 300, 1500);

	uint16_t ms = millis();
	uint16_t deltams = ms - sLastMillis;
	sLastMillis = ms;
	sPseudotime += deltams * msmultiplier;
	sHue16 += deltams * beatsin88(400, 5, 9);
	uint16_t brightnesstheta16 = sPseudotime;

	for (uint16_t i = 0; i < numleds; i++) {
		hue16 += hueinc16;
		uint8_t hue8 = hue16 / 256;
		uint16_t h16_128 = hue16 >> 7;
		if (h16_128 & 0x100) {
			hue8 = 255 - (h16_128 >> 1);
		}
		else {
			hue8 = h16_128 >> 1;
		}

		brightnesstheta16 += brightnessthetainc16;
		uint16_t b16 = sin16(brightnesstheta16) + 32768;

		uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
		uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
		bri8 += (255 - brightdepth);

		uint8_t index = hue8;
		//index = triwave8( index);
		index = scale8(index, 240);

		CRGB newcolor = ColorFromPalette(palette, index, bri8);

		uint16_t pixelnumber = i;
		pixelnumber = (numleds - 1) - pixelnumber;

		nblend(ledarray[pixelnumber], newcolor, 128);
	}*/
}

void colorWaves()
{
	/*colorwaves(leds[0], NUM_LEDS, currentPalette);*/
}

void colorWipe()
{

	/*int pos = beatsin16(speed/5, 0, NUM_LEDS_PER_STRIP - 1);
	
	static int prevpos = 0;
	CRGB color = ColorFromPalette(palettes[currentPaletteIndex], gHue, 255);
	if (pos < prevpos) {
		fill_solid(leds[0] + pos, (prevpos - pos) + 1, color);
	}
	else {
		fill_solid(leds[0] + prevpos, (pos - prevpos) + 1, color);
	}
	prevpos = pos;*/
}
void continuousWipe()
{
	/*static int pos = 0;
	pos += speed / 10;

	if (pos >= NUM_LEDS_PER_STRIP && copyStrip == 1)
	{
		pos = 0;
	}
	else if (pos >= NUM_LEDS && copyStrip == 0)
	{
		pos = 0;
	}

	static int prevpos = 0;
	CRGB color = ColorFromPalette(palettes[currentPaletteIndex], gHue, 255);

	fill_solid(leds[0] + prevpos, (pos - prevpos) + 1, color);

	prevpos = pos;*/
}

// -----------------------------------------------------------------------------------//
// ---------------------THE BEGINNINGS OF MY ANINMATION LIBRARY-----------------------//
// -----------------------------------------------------------------------------------//

// I want the logistics of the animations to be handled in this file.
void poopyWorm1(StripController* strip)
{
	D(startTime("poopyWorm1");)

	static int stage = 0;


	// TODO Move these to being time dependant like displaying the menu.
	switch (stage)
	{
	case 0:

		D(middleTime("Poopy worm 1 case 0");)

			strip->ClearAnimations();

		for (int i = 0; i < NUM_ANIMATIONS_PER_STRIP; i++)
		{
			strip->AddAnimation("Mover", 5, 0.1, i * (255 / NUM_ANIMATIONS_PER_STRIP), i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}
		stage++;
		break;

	case 1:

		D(middleTime("Poopy worm 1 case 1");)

			strip->ClearAnimations();

		for (int i = 0; i < NUM_ANIMATIONS_PER_STRIP; i++)
		{
			strip->AddAnimation("Mover", NUM_LEDS_PER_STRIP - 5, -0.1, i * (255 / NUM_ANIMATIONS_PER_STRIP), i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}
		stage = 0;
		break;
	}

	D(endTime("poopyWorm1");)
}

void poopyWorm2(StripController* strip)
{
	D(startTime("poopyWorm2");)

		static int stage = 0;

	switch (stage)
	{
	case 0:

		D(middleTime("Poopy worm 2 case 0");)

			strip->ClearAnimations();

		for (int i = 0; i < NUM_ANIMATIONS_PER_STRIP / 2; i++)
		{
			strip->AddAnimation("Mover", 5, 0.1, i * (255 / NUM_ANIMATIONS_PER_STRIP), i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}
		for (int i = NUM_ANIMATIONS_PER_STRIP / 2; i < NUM_ANIMATIONS_PER_STRIP; i++)
		{
			strip->AddAnimation("Mover", NUM_LEDS_PER_STRIP - 5, -0.1, i * (255 / NUM_ANIMATIONS_PER_STRIP), i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}

		stage++;
		break;

	case 1:

		D(middleTime("Poopy worm 2 case 1");)

			strip->ClearAnimations();

		for (int i = 0; i < NUM_ANIMATIONS_PER_STRIP / 2; i++)
		{
			strip->AddAnimation("Mover", NUM_LEDS_PER_STRIP / 2, -0.1, i * (255 / NUM_ANIMATIONS_PER_STRIP), i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}
		for (int i = NUM_ANIMATIONS_PER_STRIP / 2; i < NUM_ANIMATIONS_PER_STRIP; i++)
		{
			strip->AddAnimation("Mover", NUM_LEDS_PER_STRIP / 2, 0.1, i * (255 / NUM_ANIMATIONS_PER_STRIP), i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}

		stage = 0;
		break;
	}

	D(endTime("poopyWorm2");)
}

typedef void(*PatternList[])(StripController* strip);
PatternList patterns = { poopyWorm1, poopyWorm2 };

/*typedef Pattern PatternList[];
typedef struct {
	Pattern pattern;
	String name;
} PatternAndName;
typedef PatternAndName PatternAndNameList[];*/

/*PatternAndNameList patterns = {
	// TODO Things to add to web list.
	{ poopyWorm,		"Poopy Worm"}
	{ continuousWipe,	"Continuous Wipe"},
	{ colorWipe,		"Color Wipe"},


  { pride,              "Pride" },
  { colorWaves,         "Color Waves" },

	// TwinkleFOX patterns
	//{ drawTwinkles,		"Twinkles" },

	// Fire & Water
	{ fire, "Fire" },
	{ water, "Water" },

	// DemoReel100 patterns
	{ rainbow, "rainbow" },
	{ rainbowWithGlitter, "rainbowWithGlitter" },
	{ confetti, "confetti" },
	{ sinelon, "sinelon" },
	{ juggle, "juggle" },
	{ bpm, "bpm" },

	{ showSolidColor,         "Solid Color" }
};*/

const uint8_t patternCount = ARRAY_SIZE(patterns);
