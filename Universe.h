#pragma once

#include <arduino.h>
#include <FastLED.h>

#include "universeSettings.h"
#include "LEDStrip.h"

class Universe
{
private:

	int gNumLeds;

	CRGBArray<NUM_LEDS> gLeds;
	LEDStrip* strips[NUM_STRIPS];

public:

	Universe();
	~Universe();

	static Universe* CreateUniverse();

	void Update();

	void PrintInfo();
};