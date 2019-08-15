// The Universe class is responsible for keeping track of global variables as well as LED data.

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
	float uSpeed;
	float uHue;
	float uHueSpeed;
	int uOffset;

	
	unsigned long uAutoplayTimeout;
	int uAutoplayDuration;

public:
	// In my rush, I have broken encapsulation :(
	// Although the next version will fix this :)

	bool uPower;			// Turn off the LEDs if false
	bool uAutoplay;			// Auto cycle patterns
	int uBrightness;		// current global brightness
	int uTempBrightness;	// temporary brightness if using strobe or flash

	int uStrobeTime;		// Beats per minute of the strobe
	bool uStrobe;			// if true strobe is active
	bool uFlash;			// if true flash is active
	bool uSlow;				// if true slow or 'stutter' is active
	long int uSlowStart;	// the time that the stutter began
	int uPrevSpeed;
	int uSlowDelay;			// how much the stutter slows the program

	Universe();
	~Universe();

	static Universe* CreateUniverse();

	void Update();			// Generate the next frame
	void NextPattern();
	void PrevPattern();
	void SetPattern(int newPatternNum);
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

	void ChangeReflect();

	void PrintInfo();
};