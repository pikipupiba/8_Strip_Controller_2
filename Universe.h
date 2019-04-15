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

public:

	Universe();
	~Universe();

	static Universe* CreateUniverse();

	void Update();

	void PrintInfo();
};