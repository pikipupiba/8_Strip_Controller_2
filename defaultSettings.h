#pragma once

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
enum Shapes		{ Strip, Panel, Ring };		// The shape of a strip can effect how the animations are displayed.
enum Textures	{ None, Dashed, Wavey, Strobe };	// Textures are modifications of some variable based on where on the strip a pixel is.
enum EndOfRanges{ Continue, Bounce, Fade };	// This describes the behavior an animation will display when it reaches the end of its specified range.

// Set the master variables to their starting values.
bool masterPower = true;
uint8_t masterBrightness = 128;

// Define our master array of LEDs.
CRGBArray<NUM_LEDS> leds;

uint32_t frameTime = 0;
long lastFrameTime = 0;
uint32_t newFrames = 0;
uint32_t FPS = 0;