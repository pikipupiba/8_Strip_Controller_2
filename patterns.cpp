#pragma once

// All the weirdly specific values in this file are purely so that the an imations look good on my plant
// or to try to get their speeds to scale linearly with each other. Maybe in the future each pattern
// object could have it's own set of scaling factors to make the pattern code more readable and to easily
// modify various aspects of the pattern while knowing how the changes you make affect how the pattern looks.

#include "debug.h"
#include "patterns.h"
#include <FastLED.h>

void rainbow(PatternVars &vars)
{
	vars.hueSpeed = -2 * vars.speedScaleFactor;
	// FastLED's built-in rainbow generator
	vars.leds->fill_rainbow(vars.hue + vars.positionOffset/1.5, (vars.size / 4) * vars.speedScaleFactor);
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
	fadeToBlackBy(vars.leds[0], vars.numLeds, 10);
	int pos = random16(vars.numLeds);
	if (random8(10) < 5 * vars.speedScaleFactor)
	{
		vars.leds[0][pos] += CHSV(vars.hue + random8(64), 200, 255);
	}
}

void sinelon(PatternVars &vars)
{
	vars.speed = 1;

	// a colored dot sweeping back and forth, with fading trails
	vars.leds->fadeToBlackBy(5 * vars.speedScaleFactor + 1);
	//fadeToBlackBy(vars.leds[0], NUM_LEDS, 20);
	int pos = beatsin16((vars.speed * 60) * vars.speedScaleFactor / 5, 0, vars.numLeds - 1, vars.positionOffset * 50);

	CRGB color = HSVHue((int)vars.hue % 255);//ColorFromPalette(palettes[currentPaletteIndex], gHue, 255);

	for (int i = -5; i < 5; i++)
	{
		if (pos + i > 0 && pos + i < vars.numLeds)
		{
			vars.leds[0][pos + i] = CHSV(vars.hue, 255, vars.brightness);
		}
	}

}

void bpm(PatternVars &vars)
{
	// colored stripes pulsing at a defined Beats-Per-Minute (BPM)
	uint8_t beat = beatsin8(70 * vars.speedScaleFactor, 64, 255, 0, vars.positionOffset/1.5);
	//CRGBPalette16 palette = palettes[currentPaletteIndex];
	for (int i = 0; i < vars.numLeds; i++) {
		vars.leds[0][i] = CHSV(vars.hue + (i * 2), 255, beat - vars.hue + (i * 10));
	}
}

void juggle(PatternVars &vars) {
	// eight colored dots, weaving in and out of sync with each other
	fadeToBlackBy(vars.leds[0], vars.numLeds, 20);
	byte dothue = 0;
	for (int i = 0; i < 10; i++) {
		vars.leds[0][beatsin16((i + vars.speed + 1) * vars.speedScaleFactor, 0, vars.numLeds - 1,0,vars.positionOffset*200)] |= CHSV(dothue, 200, 255);
		dothue += 25;
	}
}

void showSolidColor(PatternVars &vars)
{
	//fill_solid(leds[0], NUM_LEDS, solidColor);
}

void showSolidColorChanging(PatternVars &vars)
{
	fill_solid(vars.leds[0], vars.numLeds, CHSV(vars.hue + vars.positionOffset/1.5, 255, 255));
	//vars.leds->fill_solid(CHSV(vars.hue,255,255));
}

// based on FastLED example Fire2012WithPalette: https://github.com/FastLED/FastLED/blob/master/examples/Fire2012WithPalette/Fire2012WithPalette.ino
void heatMap(PatternVars &vars, CRGBPalette16 palette, bool up)
{
#define cooling 40
#define sparking 50

	fill_solid(vars.leds[0], vars.numLeds, CRGB::Black);

	// Add entropy to random number generator; we use a lot of it.
	random16_add_entropy(random(256));

	// Array of temperature readings at each simulation cell
	static byte heat[300];

	byte colorindex;

	// Step 1.  Cool down every cell a little
	for (uint16_t i = 0; i < vars.numLeds; i++) {
		heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / vars.numLeds) + 2));
	}

	// Step 2.  Heat from each cell drifts 'up' and diffuses a little
	for (uint16_t k = vars.numLeds - 1; k >= 2; k--) {
		heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
	}

	// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
	if (random8() < sparking) {
		int y = random8(7);
		heat[y] = qadd8(heat[y], random8(160, 255));
	}

	// Step 4.  Map from heat cells to LED colors
	for (uint16_t j = 0; j < vars.numLeds; j++) {
		// Scale the heat value from 0-255 down to 0-240
		// for best results with color palettes.
		colorindex = scale8(heat[j], 190);

		CRGB color = ColorFromPalette(palette, colorindex);

		if (up) {
			vars.leds[0][j] = color;
		}
		else {
			vars.leds[0][(vars.numLeds - 1) - j] = color;
		}
	}
}

void fire(PatternVars &vars)
{
	heatMap(vars, HeatColors_p, true);
}

void water(PatternVars &vars)
{
	heatMap(vars, IceColors_p, false);
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

	uint8_t sat8 = beatsin88(87 * vars.speedScaleFactor, 220, 250,0,vars.positionOffset*100);
	uint8_t brightdepth = beatsin88(341 * vars.speedScaleFactor, 96, 224, 0, vars.positionOffset * 100);
	uint16_t brightnessthetainc16 = beatsin88(203 * vars.speedScaleFactor, (25 * 256), (40 * 256), 0, vars.positionOffset * 100);
	uint8_t msmultiplier = beatsin88(147 * vars.speedScaleFactor, 23, 60, 0, vars.positionOffset * 100);

	uint16_t hue16 = sHue16;//gHue * 256;
	uint16_t hueinc16 = beatsin88(113 * vars.hueScaleFactor, 1, 3000, 0, vars.positionOffset * 100);

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

			//Serial.println(*vars.leds);
			//Serial.println(vars.numLeds);

		nblend(vars.leds[0][pixelnumber], newcolor, 64);
	}

	D(endTime("pride(PatternVars vars)");)
}

// ColorWavesWithPalettes by Mark Kriegsman: https://gist.github.com/kriegsman/8281905786e8b2632aeb
// This function draws color waves with an ever-changing,
// widely-varying set of parameters, using a color palette.
void colorwaves(CRGB* ledarray, uint16_t numleds, CRGBPalette16& palette)
{
	static uint16_t sPseudotime = 0;
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
	}
}

void colorWaves(PatternVars &vars)
{
	vars.cyclePalettes = true;

	colorwaves(vars.leds[0], vars.numLeds, vars.palette);
}

void colorWipe(PatternVars &vars)
{

	int pos = beatsin16(vars.speed, 0, vars.numLeds - 1);

	static int prevpos = 0;
	CRGB color = ColorFromPalette(vars.palette, vars.hue, 255);
	if (pos < prevpos) {
		fill_solid(vars.leds[0] + pos, (prevpos - pos) + 1, color);
	}
	else {
		fill_solid(vars.leds[0] + prevpos, (pos - prevpos) + 1, color);
	}
	prevpos = pos;
}

void continuousWipe(PatternVars &vars)
{

	if (vars.position >= vars.numLeds)
	{
		vars.position = 0;
	}

	static int prevpos = 0;
	CRGB color = ColorFromPalette(vars.palette, vars.hue, 255);

	fill_solid(vars.leds[0] + prevpos, (vars.position - prevpos) + 1, color);

	prevpos = vars.position;
}

void dripper(PatternVars &vars)
{
	D(startTime("dripper()");)

		if (vars.position <0 || vars.position > vars.numLeds)
		{
			vars.position = 0;
		}

	int tankSize = beatsin8(15 * vars.speedScaleFactor, vars.numLeds / 75, vars.numLeds * 0.75, 0, vars.positionOffset);
	int dripSize = 5;

	vars.leds->fadeToBlackBy(40);

	vars.hueSpeed = -1;

	for (int i = 0; i < tankSize; i++)
	{
		D(middleTime("dripper() " + String(i));)
		vars.leds[0][i] = CHSV(vars.hue + i * 2, 255, vars.brightness);
	}

	if (vars.position == 0)
	{
		//if (random8() < 10)
		//{
			vars.position = tankSize - 1;
			vars.speed = 0.1;
			vars.hue2 = vars.hue + (tankSize - 5) * 2;
		//}
	}
	else
	{
		D(middleTime("dripper() else");)
		vars.speed = (vars.position - tankSize)/120+0.2;

		dripSize *= vars.speed;

		if (vars.position + dripSize < vars.numLeds)
		{
			for (int i = vars.position; i < vars.position + dripSize - 1; i++)
			{
				vars.leds[0][i] = CHSV(vars.hue2, 255, vars.brightness);
			}
		}
		else if (vars.position < vars.numLeds)
		{
			for (int i = vars.position; i < vars.numLeds - 1; i++)
			{
				vars.leds[0][i] = CHSV(vars.hue2, 255, vars.brightness);
			}
		}
		else
		{
			vars.position = 0;
			vars.speed = 0;
		}
	}

	D(endTime("dripper()");)
}

void dripper2(PatternVars &vars)
{
	D(startTime("dripper2()");)

	int tankSize = beatsin8(15 * vars.speedScaleFactor, vars.numLeds/75, vars.numLeds * 0.75, 0, vars.positionOffset);
	int dripSize = 5;

	vars.leds->fadeToBlackBy(120);

	vars.speed = -6;
	vars.hueSpeed = 1;

	for (int i = 0; i < tankSize; i++)
	{
		D(middleTime("dripper2() " + String(i));)
			vars.leds[0][i] = CHSV(vars.hue - i * 3, 255, vars.brightness);
	}

	vars.hue2 = vars.hue - (tankSize) * 3;
	
	for (int i = tankSize - 1; i < vars.numLeds - 1; i++)
	{

		if (sin8(i - (i * i)/40 + vars.position) > 252)
		{
			vars.leds[0][vars.numLeds + tankSize - i] = CHSV(vars.hue2, 255, vars.brightness);
		}
	}


	D(endTime("dripper2()");)
}

void twinkle(PatternVars &vars)
{
	vars.leds->fadeToBlackBy(10);

	for (int i = 0; i < vars.numLeds; i++)
	{
		if (random16() < 256 * vars.speedScaleFactor)
		{
			vars.leds[0][i] = CRGB(255,255,255);
		}
	}
}

void twinkleRain(PatternVars &vars)
{
	vars.leds->fadeToBlackBy(60);

	vars.speed = (float)(beatsin8(5, 0, 255) - 50) / 30;

	int limit = beatsin8(5, 220, 253);
	int wave1 = beatsin8(4);
	int wave2 = beatsin8(1);

	for (int i = 0; i < vars.numLeds - 1; i++)
	{
		if (
			sin8( i * 6 - int(vars.position) + wave1) + 
			sin8(i * 2 - int(vars.position * 0.5) + wave2) 
			> limit)
		{
			vars.leds[0][i] = CHSV(vars.hue + i * 3, 255, vars.brightness);
		}
	}

	//addGlitter(80, vars);
}

void plasma(PatternVars &vars)
{
	vars.leds->fadeToBlackBy(80);

	vars.speed = (float)(beatsin8(5, 200, 255)) / 250;// (float)(beatsin8(5, 50, 180) + beatsin8(2, 50, 200)) / 120;

	//int limit = (beatsin8(3, 240, 245) + beatsin8(5, 240, 253) + beatsin8(1, 240, 247)) / 2;
	int limit = (beatsin8(3, 240, 245) + beatsin8(5, 240, 253) + beatsin8(1, 240, 247));
	int wave1 = beatsin8(1);
	int wave2 = beatsin8(2);
	int wave3 = beatsin8(3);
	int bright = 0;

	for (int i = 0; i < vars.numLeds - 1; i++)
	{
		/*if (
			sin8(i * 1 - int(vars.position) + wave1) +
			sin8(i * 3 - int(vars.position) + wave2) +
			sin8(i * 2 - int(vars.position) + wave3)
			//sin8(i * 5 - int(vars.position) + beatsin8(3)) +
			//sin8(i * 7 - int(vars.position) + beatsin8(4)) +
			//sin8(i * 9 - int(vars.position) + beatsin8(5))
			> limit
			)
		{*/
		bright = vars.brightness * (sin8(i * 1 - int(vars.position) + wave1) +
			sin8(i * 3 - int(vars.position) + wave2) +
			sin8(i * 2 - int(vars.position) + wave3)) / limit;

		if (bright > 255)
		{
			bright = 255 - (bright - 255);
		}

		vars.leds[0][i] = CHSV(vars.hue + i, 255, bright);
		//}


	}

	//addGlitter(80, vars);
}

void plasma2(PatternVars& vars)
{
	vars.leds->fadeToBlackBy(80);

	vars.speed = (float)(beatsin8(5, 200, 255)) / 250;// (float)(beatsin8(5, 50, 180) + beatsin8(2, 50, 200)) / 120;

	//int limit = (beatsin8(3, 240, 245) + beatsin8(5, 240, 253) + beatsin8(1, 240, 247)) / 2;
	int limit = (beatsin8(3, 240, 245) + beatsin8(5, 240, 253) + beatsin8(1, 240, 247));
	int wave1 = beatsin8(1);
	int wave2 = beatsin8(2);
	int wave3 = beatsin8(3);
	int bright = 0;

	for (int i = 0; i < vars.numLeds - 1; i++)
	{
		/*if (
			sin8(i * 1 - int(vars.position) + wave1) +
			sin8(i * 3 - int(vars.position) + wave2) +
			sin8(i * 2 - int(vars.position) + wave3)
			//sin8(i * 5 - int(vars.position) + beatsin8(3)) +
			//sin8(i * 7 - int(vars.position) + beatsin8(4)) +
			//sin8(i * 9 - int(vars.position) + beatsin8(5))
			> limit
			)
		{*/
		bright = vars.brightness * (sin8(i * 1 - int(vars.position) + wave1) +
			sin8(i * 3 - int(vars.position) + wave2) +
			sin8(i * 2 - int(vars.position) + wave3)) / limit;

		if (bright > 255)
		{
			bright = 255 - (bright - 255);
		}

		vars.leds[0][i] = CHSV(vars.hue + i, 255, bright);
		//}


	}

	//addGlitter(80, vars);
}

void plasma3(PatternVars& vars)
{
	vars.leds->fadeToBlackBy(80);

	vars.speed = (float)(beatsin8(5, 200, 255)) / 250;// (float)(beatsin8(5, 50, 180) + beatsin8(2, 50, 200)) / 120;

	//int limit = (beatsin8(3, 240, 245) + beatsin8(5, 240, 253) + beatsin8(1, 240, 247)) / 2;
	int limit = (beatsin8(3, 240, 245) + beatsin8(5, 240, 253) + beatsin8(1, 240, 247));
	int wave1 = beatsin8(1);
	int wave2 = beatsin8(2);
	int wave3 = beatsin8(3);
	int bright = 0;

	for (int i = 0; i < vars.numLeds - 1; i++)
	{
		/*if (
			sin8(i * 1 - int(vars.position) + wave1) +
			sin8(i * 3 - int(vars.position) + wave2) +
			sin8(i * 2 - int(vars.position) + wave3)
			//sin8(i * 5 - int(vars.position) + beatsin8(3)) +
			//sin8(i * 7 - int(vars.position) + beatsin8(4)) +
			//sin8(i * 9 - int(vars.position) + beatsin8(5))
			> limit
			)
		{*/
		bright = vars.brightness * (sin8(i * 1 - int(vars.position) + wave1) +
			sin8(i * 3 - int(vars.position) + wave2) +
			sin8(i * 2 - int(vars.position) + wave3)) / limit;

		if (bright > 255)
		{
			bright = 255 - (bright - 255);
		}

		vars.leds[0][i] = CHSV(vars.hue + i, 255, bright);
		//}


	}

	//addGlitter(80, vars);
}

void meteor(PatternVars &vars)
{
	//startTime("meteor()");

	if (vars.position <0 || vars.position > vars.numLeds)
	{
		vars.position = 0;
	}

	byte meteorSize = 5;
	byte meteorTrailDecay = 100 * vars.speedScaleFactor;

	vars.hueSpeed = 0.25;

		// fade brightness all LEDs one step
		for (int j = 0; j < vars.numLeds; j++) {
			if (random8(100) > 78) {
				vars.leds[0][j].fadeToBlackBy(meteorTrailDecay);
			}
			if (j < vars.position - 100 || j > vars.position) {
				vars.leds[0][j].fadeToBlackBy(meteorTrailDecay * 0.05);
			}
		}

		if (vars.position < vars.numLeds + meteorSize)
		{
			for (int i = 0; i < meteorSize; i++)
			{
				if (vars.position - i > 0 && vars.position - i < vars.numLeds)
				{
					vars.leds[0][vars.position - i] = CHSV(vars.hue, 255, vars.brightness);
				}
			}
		}
		else
		{
			vars.position = 0;
		}
		//endTime("meteor()");
}

void bouncingBalls(PatternVars &vars)
{
	vars.leds->fadeToBlackBy(120);


	int BallCount = 3;
	float Gravity = -0.8;
	int StartHeight = 1;

	float ImpactVelocityStart = sqrt(-2 * Gravity * StartHeight);

	if (!vars.started)
	{
		for (int i = 0; i < BallCount; i++) {
			vars.ClockTimeSinceLastBounce[i] = millis();
			vars.Height[i] = StartHeight;
			vars.Position[i] = 0;
			vars.PrevPosition[i] = vars.Position[i];
			vars.ImpactVelocity[i] = ImpactVelocityStart;
			vars.TimeSinceLastBounce[i] = 0;
			vars.Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);

			vars.hueSpeed = 0.08;
		}
		vars.started = true;
	}

	for (int i = 0; i < BallCount; i++) {

		vars.PrevPosition[i] = vars.Position[i];

		vars.TimeSinceLastBounce[i] = millis() - vars.ClockTimeSinceLastBounce[i];
		vars.Height[i] = 0.5 * Gravity * pow(vars.TimeSinceLastBounce[i] / 1000, 2.0) + vars.ImpactVelocity[i] * vars.TimeSinceLastBounce[i] / 1000;

		if (vars.Height[i] < 0) {
			vars.Height[i] = 0;
			vars.ImpactVelocity[i] = vars.Dampening[i] * vars.ImpactVelocity[i];
			vars.ClockTimeSinceLastBounce[i] = millis();

			if (vars.ImpactVelocity[i] < 0.01) {
				vars.ImpactVelocity[i] = ImpactVelocityStart;
			}
		}
		vars.Position[i] = round(vars.Height[i] * (vars.numLeds - 3) / StartHeight);
	}

	for (int i = 0; i < BallCount; i++) {
		
		vars.leds[0][vars.numLeds - vars.Position[i] - 1] += CHSV(vars.hue + i * 92, 255, vars.brightness);

		for (int j = vars.PrevPosition[i]; j < vars.Position[i]; j++)
		{
			vars.leds[0][vars.numLeds - j - 1] += CHSV(vars.hue + i * 92, 255, vars.brightness);
		}
		for (int j = vars.PrevPosition[i]; j > vars.Position[i]; j--)
		{
			vars.leds[0][vars.numLeds - j - 1] += CHSV(vars.hue + i * 92, 255, vars.brightness);
		}
	}

}

void dancingSisters(PatternVars& vars)
{
	//int size = beatsin8(10 * vars.speedScaleFactor+1, 2, vars.numLeds/2 - 1);
	int  position = beatsin16(10 * vars.speedScaleFactor, vars.numLeds/2, vars.numLeds);

	vars.leds->fadeToBlackBy(84);

	for (int i = vars.numLeds / 2; i < position; i++)
	{
		vars.leds[0][i] += CHSV(vars.hue, 255, vars.brightness);
		vars.leds[0][vars.numLeds - i] += CHSV(vars.hue + 128, 255, vars.brightness);
	}

	/*
	vars.leds->fadeToBlackBy(255);

	for (int i = position; i < position + size - 1; i++)
	{
		Serial.println(i);
		vars.leds[i][0] += CHSV(vars.hue, 255, vars.brightness);
		vars.leds[vars.numLeds/2 - i][0] += CHSV(vars.hue * 2, 255, vars.brightness);
		Serial.println(i);
	}
	*/
}

PatternList patterns = {	rainbow,
							rainbowWithGlitter, 
							bpm,
							sinelon,
							juggle,
							confetti,
							colorWaves,
							pride,
							//continuousWipe,
							//colorWipe, 
							showSolidColorChanging,
							//fire,
							//water,
							dripper,
							dripper2,
							twinkle,
							twinkleRain,
							plasma,
							//plasma2,
							//plasma3,
							meteor,
							bouncingBalls,
							//dancingSisters
						};

/*PatternAndNameList patternsAndNames = {
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
};*/

const uint8_t patternCount = ARRAY_SIZE(patterns);
