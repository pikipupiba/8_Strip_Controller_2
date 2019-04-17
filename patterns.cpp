#pragma once

// These patterns were the sample patterns that came with the ESP32 Web server example by Jason Coon.
// My new patterns will create and destroy animation objects as needed to create the desired effect.
// The patterns will have access to the animation[] array of each strip and associated parameters.
// I haven't quite figured out how this will work but you can check out my AnimationClassTest repo to see how that worked out.

#include "debug.h"
#include "patterns.h"
#include <FastLED.h>


void rainbow(PatternVars &vars)
{
	// FastLED's built-in rainbow generator
	vars.leds->fill_rainbow(vars.hue, vars.size / 10);
	//fill_rainbow(leds[0], NUM_LEDS, gHue, speed/10);
}

void addGlitter(fract8 chanceOfGlitter, PatternVars &vars)
{
	if (random8() < chanceOfGlitter) {
		vars.leds[0][random16(vars.numLeds)] += CRGB::White;
	}
}

void rainbowWithGlitter(PatternVars &vars)
{
	// built-in FastLED rainbow, plus some random sparkly glitter
	rainbow(vars);
	addGlitter(80, vars);
}

void confetti(PatternVars &vars)
{
	// random colored speckles that blink in and fade smoothly
	/*fadeToBlackBy(leds[0], NUM_LEDS, 10);
	int pos = random16(NUM_LEDS);
	leds[0][pos] += CHSV(gHue + random8(64), 200, 255);*/
}

void sinelon(PatternVars &vars)
{
	// a colored dot sweeping back and forth, with fading trails
	vars.leds->fadeToBlackBy(20);
	//fadeToBlackBy(vars.leds[0], NUM_LEDS, 20);
	int pos = beatsin16(vars.speed/5, 0, vars.numLeds - 1);

	static int prevpos = 0;
	CRGB color = HSVHue((int)vars.hue % 255);//ColorFromPalette(palettes[currentPaletteIndex], gHue, 255);
	if (pos < prevpos) {
		//vars.leds->fill_solid(vars.hue);
		fill_solid(&vars.leds[0][pos], (prevpos - pos) + 1, color);
	}
	else {
		fill_solid(vars.leds[0] + prevpos, (pos - prevpos) + 1, color);
	}
	prevpos = pos;
}

void bpm(PatternVars &vars)
{
	// colored stripes pulsing at a defined Beats-Per-Minute (BPM)
	uint8_t beat = beatsin8(vars.speed/1.5, 64, 255);
	//CRGBPalette16 palette = palettes[currentPaletteIndex];
	for (int i = 0; i < vars.numLeds; i++) {
		vars.leds[0][i] = CHSV(vars.hue + (i * 2), 255, beat - vars.hue + (i * 10));
	}
}

void juggle(PatternVars &vars) {
	// eight colored dots, weaving in and out of sync with each other
	/*fadeToBlackBy(leds[0], NUM_LEDS, 20);
	byte dothue = 0;
	for (int i = 0; i < 8; i++) {
		leds[0][beatsin16(i + speed/20, 0, NUM_LEDS_PER_STRIP - 1)] |= CHSV(dothue, 200, 255);
		dothue += 32;
	}*/
}

void showSolidColor(PatternVars &vars)
{
	//fill_solid(leds[0], NUM_LEDS, solidColor);
}

void showSolidColorChanging(PatternVars &vars)
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

void fire(PatternVars &vars)
{
	//heatMap(HeatColors_p, true);
}

void water(PatternVars &vars)
{
	/*heatMap(IceColors_p, false);*/
}

// Pride2015 by Mark Kriegsman: https://gist.github.com/kriegsman/964de772d64c502760e5
// This function draws rainbows with an ever-changing,
// widely-varying set of parameters.
void pride(PatternVars &vars)
{
	D(startTime("pride(PatternVars vars)");)

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

	for (uint16_t i = 0; i < vars.numLeds; i++) {

		hue16 += hueinc16;
		uint8_t hue8 = hue16 / 256;

		brightnesstheta16 += brightnessthetainc16;
		uint16_t b16 = sin16(brightnesstheta16) + 32768;

		uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
		uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
		bri8 += (255 - brightdepth);

		CRGB newcolor = CHSV(hue8, sat8, bri8);

		uint16_t pixelnumber = i;
		pixelnumber = (vars.numLeds - 1) - pixelnumber;

		D(middleTime("pride(PatternVars vars)");)

			Serial.println(*vars.leds);
			//Serial.println(vars.numLeds);

		vars.leds[pixelnumber].nblend( newcolor, 64);

		//nblend(vars.leds[0][pixelnumber], newcolor, 64);
	}

	D(endTime("pride(PatternVars vars)");)
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

void colorWaves(PatternVars &vars)
{
	//colorwaves(vars.leds[0], NUM_LEDS, currentPalette);
}

void colorWipe(PatternVars &vars)
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

void continuousWipe(PatternVars &vars)
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

PatternList patterns = { rainbow, rainbowWithGlitter, bpm, sinelon };

PatternAndNameList patternsAndNames = {
	// TODO Things to add to web list.
	//{ poopyWorm,		"Poopy Worm"}
	//{ continuousWipe,	"Continuous Wipe"},
	//{ colorWipe,		"Color Wipe"},


	{ pride,              "Pride" },
	{ colorWaves,         "Color Waves" },

	//{ drawTwinkles,		"Twinkles" },

	//{ fire, "Fire" },
	//{ water, "Water" },

	// DemoReel100 patterns
	{ rainbow, "rainbow" },
	//{ rainbowWithGlitter, "rainbowWithGlitter" },
	//{ confetti, "confetti" },
	//{ sinelon, "sinelon" },
	//{ juggle, "juggle" },
	{ bpm, "bpm" }

	//{ showSolidColor,         "Solid Color" }
};

const uint8_t patternCount = ARRAY_SIZE(patterns);
