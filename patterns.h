#pragma once

// These patterns were the sample patterns that came with the ESP32 Web server example by Jason Coon.
// My new patterns will create and destroy animation objects as needed to create the desired effect.
// The patterns will have access to the animation[] array of each strip and associated parameters.
// I haven't quite figured out how this will work but you can check out my AnimationClassTest repo to see how that worked out.

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
#include <FastLED.h>

typedef struct {

	CRGBSet* leds;
	int numLeds;

	int curPattern;

	float brightness;

	float hue;
	float hueSpeed;
	
	float hue2;

	float position;
	float speed;

	float size;

	int positionOffset;
	int clockOffset;

	CRGBPalette16 palette;
	CRGBPalette16 targetPalette;

	bool autoplay;
	int autoplayDuration;

	float hueScaleFactor;
	float speedScaleFactor;

} PatternVars;

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
void dripper			(PatternVars& vars);
void dripper2			(PatternVars& vars);
void twinkle			(PatternVars& vars);
void twinkleRain		(PatternVars& vars);
void plasma				(PatternVars& vars);
void meteor				(PatternVars& vars);


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
