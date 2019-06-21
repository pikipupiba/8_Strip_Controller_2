#pragma once

#include <arduino.h>
#include <FastLED.h>

#include "debug.h"
#include "universeSettings.h"
#include "LEDStrip.h"

class Universe
{
private:

	int gNumLeds;

	CRGBArray<NUM_LEDS> gLeds;
	CRGBSet* ledSets[NUM_STRIPS];
	LEDStrip* strips[NUM_STRIPS];

	bool uPower;
	float uSpeed;
	float uHue;
	float uHueSpeed;
	int uOffset;

	bool uAutoplay;
	unsigned long uAutoplayTimeout;
	int uAutoplayDuration;

public:
	int uBrightness;

	Universe();
	~Universe();

	static Universe* CreateUniverse();

	void Update();
	void NextPattern();
	void ToggleAutoplay();

	void Change(String label, int value);
	void ChangeOffset();
	void ChangeHueFactor();
	void ChangeSpeedFactor();

	void PrintInfo();
};