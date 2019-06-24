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
	CRGBSet* ledSets[NUM_STRIPS * 2];
	LEDStrip* strips[NUM_STRIPS * 2];

	bool uPower;
	float uSpeed;
	float uHue;
	float uHueSpeed;
	int uOffset;

	
	unsigned long uAutoplayTimeout;
	int uAutoplayDuration;

public:
	bool uAutoplay;
	int uBrightness;

	int uStrobeTime;

	Universe();
	~Universe();

	static Universe* CreateUniverse();

	void Update();
	void NextPattern();
	void PrevPattern();
	void ToggleAutoplay();

	void Change(String label, int value);

	void RandomHue();
	void NextHue();

	void ChangeOffset();
	void ChangeOffset(int newOffset);

	void ChangeHueFactor();
	void ChangeHueFactor(float newHueFactor);

	void ChangeSpeedFactor();
	void ChangeSpeedFactor(float newSpeedFactor);

	void PrintInfo();
};