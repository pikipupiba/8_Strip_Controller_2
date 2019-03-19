#ifndef __GLOBAL_STUFF_H
#define __GLOBAL_STUFF_H



#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include<FastLED.h>

// -- The core to run FastLED.show()
#define FASTLED_SHOW_CORE 1

// Define minimum and maximum values of some data types.
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

// Set the size of the animation array dedicated to each strip.
#define NUM_ANIMATIONS_PER_STRIP	10

#define MILLI_AMPS         60000 * NUM_STRIPS // IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)
#define FRAMES_PER_SECOND  120

// Define some enumerated values.
enum class Shapes		{ Strip, Panel, Ring };		// The shape of a strip can effect how the animations are displayed.
enum class Textures		{ None, Dashed, Wavey, Strobe };	// Textures are modifications of some variable based on where on the strip a pixel is.
enum class EndOfRanges	{ Continue, Bounce, Fade };	// This describes the behavior an animation will display when it reaches the end of its specified range.

// -----------------------------------------------------------------------------------//
// ----------------------------GLOBAL ANIMATION VARIABLES-----------------------------//
// -----------------------------------------------------------------------------------//
// TODO Save and restore these settings from EEPROM.

extern uint8_t gHue; // rotating "base color" used by many of the patterns

// Define our master array of LEDs.
extern CRGBArray<NUM_LEDS> leds;

// Definitions for global variables.
extern bool gPower;
extern uint32_t gBrightness;
extern int gSpeed;

extern unsigned long frameTime;
extern unsigned long lastFrameTime;
extern uint32_t newFrames;
extern uint32_t FPS;

extern unsigned long sTime;
extern unsigned long mTime;
extern String functionName;

#endif