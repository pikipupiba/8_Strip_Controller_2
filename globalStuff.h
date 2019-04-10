#include "stdafx.h"

#ifndef __GLOBAL_STUFF_H
#define __GLOBAL_STUFF_H

//#define DEBUG_US

#if defined DEBUG_US
#  define D(x) x
#  define N(x)
#else
#  define D(x)
#  define N(x) x
#endif // DEBUG

// -- The core to run FastLED.show()
#define FASTLED_SHOW_CORE 1

// Define a quick and easy ARRAY_SIZE function.
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

// Define minimum and maximum values of some data types.
// TODO If using floats is best then these probably aren't needed.
#define uINT8_MIN	0
#define uINT8_MAX	255

#define INT16_MIN  -32768
#define INT16_MAX	32767

#define uINT16_MIN	0
#define uINT16_MAX	65535

#define INT32_MIN  -2147483648
#define INT32_MAX	2147483647
#define INT32_RANGE INT32_MAX - INT32_MIN

#define uINT32_MIN	0
#define uINT32_MAX	4294967295
#define uINT32_RANGE uINT32_MAX - uINT32_MIN

// ESP32 default pin settings
#define DATA_PIN_0 13
#define DATA_PIN_1 12
#define DATA_PIN_2 27
#define DATA_PIN_3 33
#define DATA_PIN_4 15
#define DATA_PIN_5 32
#define DATA_PIN_6 14
#define DATA_PIN_7 SCL

// Define a clock pin if your LEDs require it.
//#define CLK_PIN   4

// Define the standard properties of the LED strips I currently own.
#define LED_TYPE			WS2812B
#define COLOR_ORDER			GRB

// Set the maximum number of strips and leds per strip that might be used.
#define NUM_STRIPS			8
#define NUM_LEDS_PER_STRIP	300

// Calculate the total size needed for the led array to store data for all strips.
#define NUM_LEDS			NUM_LEDS_PER_STRIP * NUM_STRIPS

// Number of Paterns that can run on each strip
#define NUM_PATTERNS_PER_STRIP 10

// Set the size of the animation array dedicated to each pattern.
#define NUM_ANIMATIONS_PER_PATTERN	20

// IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)
#define MILLI_AMPS         60000 * NUM_STRIPS
// TODO I might not need this as my code certainly never runs TOO fast.
#define FRAMES_PER_SECOND  1000

// Define some enumerated classes.
enum class Shapes		{ Strip, Panel, Ring };			// The shape of a strip can effect how the animations are displayed.
enum class Textures		{ None, Dashed, Wavey, Strobe };// Textures are modifications of some variable based on where on the strip a pixel is.
enum class EndOfRanges	{ Continue, Bounce, Fade, Loop };		// This describes the behavior an animation will display when it reaches the end of its specified range.
enum class Direction	{ None, Forward, Reverse };


// -----------------------------------------------------------------------------------//
// ----------------------------GLOBAL ANIMATION VARIABLES-----------------------------//
// -----------------------------------------------------------------------------------//
// TODO Save and restore these settings from EEPROM.

// Define our master array of LEDs.
extern CRGBArray<NUM_LEDS> leds;

extern float gHue; // rotating "base color" used by many of the patterns
extern float gHueSpeed;
extern int gSpeed;

extern bool gPower;
extern float gBrightness;

// Variables used to calculate framerate and adjust animations accordingly.
extern float frameTime;
extern unsigned long lastFrameTime;
extern int newFrames;
extern float FPS;
extern float speedScaleFactor;

extern unsigned long sTime;
extern String functionName;

// Number of animations currently running. Used to measure performance.
extern int numObjects;
extern int numOscillators;

extern int debugDepth;


#endif