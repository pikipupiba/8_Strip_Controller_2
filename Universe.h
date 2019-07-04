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

	CRGBArray<NUM_LEDS> gLeds;		// global array of leds
	CRGBSet* ledSets[NUM_STRIPS];	// array of pointers to the CRGBSets in each strip
	LEDStrip* strips[NUM_STRIPS];	// array of LED strips

	// various messy variables that I needed.
	bool uPower;
	float uSpeed;
	float uHue;
	float uHueSpeed;
	int uOffset;

	
	unsigned long uAutoplayTimeout;
	int uAutoplayDuration;

public:
	// In my rush, I have broken encapsulation :(
	bool uAutoplay;
	int uBrightness;
	int uTempBrightness;

	int uStrobeTime;
	bool uStrobe;
	bool uFlash;

	Universe();
	~Universe();

	static Universe* CreateUniverse();	// Why should I do it like this!?!?!

	void Update();
	void NextPattern();
	void PrevPattern();
	void ToggleAutoplay();

	void Change(String label, int value);

	void RandomHue();
	void NextHue();
	void SetHue(int newHue);

	void ChangeOffset();
	void ChangeOffset(int newOffset);

	void ChangeHueFactor();
	void ChangeHueFactor(float newHueFactor);

	void ChangeSpeedFactor();
	void ChangeSpeedFactor(float newSpeedFactor);

	void PrintInfo();
};