#pragma once

// Some of these patterns were the sample patterns that came with the ESP32 Web server example by Jason Coon.
// I have had to modify them to accept a variable containing all the animation variables for a certain strip.
// this list of variables has gotten pretty bloated and I think it's time for a change.

// Just a few arrays chould be available to the patterns including an array of positions, speeds, hues,
// hue speeds, sizes, offsets, palettes, etc. This information will be specific to a strip and patterns
// will use the ones that they need.

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
#include <FastLED.h>
#include "palettes.h"

typedef struct {

	CRGBSet* leds;		// Pointer to the CRGBSet containing the leds on this strip.
	int numLeds;		// number of leds in that set

	int curPattern;		// the current pattern being played

	float brightness;

	float hue;
	float hueSpeed;		// how quickly the hue changes
	
	float hue2;			// used by a couple animations

	float position;		// used for tracking the current state of a pattern

	float speed;		// how quickly the position changes

	float size;			// will be used to track the size of a pattern feature

	int positionOffset;	// how far each strip's position is offset from the prev one's
	int clockOffset;	// not used quite yet but seems like it might be needed someday

	CRGBPalette16 palette;			// probably don't need both palette and paletteNum.
	int paletteNum;					// Can probably just keep track of the number, or
	CRGBPalette16 targetPalette;	// use a different palette struct.
	int targetPaletteNum;

	bool autoplay;
	int autoplayDuration;

	bool cyclePalettes;
	int paletteDuration;

	// Both of these could be done away with better pattern code that scales properly.
	float hueScaleFactor;	// Used to change the hue speed easily
	float speedScaleFactor;	// Used to change the speed easily

	// These are just used for the bouncing balls.
	float Height[6];
	float ImpactVelocity[6];
	float TimeSinceLastBounce[6];
	int   Position[6];
	int	  PrevPosition[6];
	long  ClockTimeSinceLastBounce[6];
	float Dampening[6];

	bool started;	// Lets a pattern know if it needs to initialize variables or use what's already there.

} PatternVars;

// Pass PatternVars vars by reference so it doesn't get copied in memory!

void rainbow			(PatternVars &vars);
//void addGlitter			(fract8 chanceOfGlitter);
void rainbowWithGlitter	(PatternVars &vars);
void confetti			(PatternVars &vars);
void sinelon			(PatternVars &vars);
void bpm				(PatternVars &vars);
void juggle				(PatternVars &vars);
void showSolidColor		(PatternVars &vars);
void showSolidColorChanging(PatternVars &vars);
//void heatMap			(CRGBPalette16 palette, bool up);
void fire				(PatternVars &vars);
void water				(PatternVars &vars);
void pride				(PatternVars &vars);
//void colorwaves			(CRGB* ledarray, uint16_t numleds, CRGBPalette16& palette);
void colorWaves			(PatternVars &vars);
void colorWipe			(PatternVars &vars);
void continuousWipe		(PatternVars &vars);
void dripper			(PatternVars &vars);
void dripper2			(PatternVars &vars);
void twinkle			(PatternVars &vars);
void twinkleRain		(PatternVars &vars);
void plasma				(PatternVars &vars);
void meteor				(PatternVars &vars);
void bouncingBalls		(PatternVars &vars);

// I think this is the best way to do this??
typedef void(*Pattern)(PatternVars &vars);
typedef Pattern PatternList[];

extern PatternList patterns;

typedef struct {
	Pattern pattern;
	String name;
} PatternAndName;

typedef PatternAndName PatternAndNameList[];

extern PatternAndNameList patternsAndNames;

extern const uint8_t patternCount;
