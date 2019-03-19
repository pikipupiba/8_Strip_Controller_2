// stripController.h
#pragma once
//#include <stdint.h>
#include <FastLED.h>
//#include "defaultSettings.h"
#include "Animations.h"
#include "Mover.h"

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

extern CRGBArray<2400> leds;

// HELP!
// Is my whole paradigm of using strip controller objects to combine animation objects onto a strip a good one?
// If this is the way to go, are my design decisions taking me in the right direction?

// Each strip controller consists of a CRGBSet containing it's subset of LEDs, strip variables inherited
// by each animatioin playing on it, and an array of animations currently running on the strip.
class StripController
{
 protected:
	 // The index of the strip determines its output pin.
	 uint32_t stripIndex;

	 // The real number of LEDs contained by the strip.
	 // There are 300 reserved LEDs in the CRGBArray leds for each strip regaurdless of actual size.
	 // TODO Find our if I can change the master CRGBArray during excecution to only store the necessary number of LEDs.
	 uint32_t stripNumLEDs;

	 // The CRGBSet containing the number of LEDs on this strip.
	 struct CRGB stripLEDs[300];

	 //Shapes stripShape;					// The default shape of animations created on this strip.
	 //Textures stripTexture;				// A modifier applied to the strip after values are calculated.
	 //EndOfRanges stripEndOfRange;		// The default behavior of animations created on this strip.

	 bool stripPower;					// If FALSE then the strip brightness is temporarily set to 0.
	 float stripBrightness;				// The strip brightness is adjusted to this value after LEDs are written, maintaining relative animation brightnesses.

	 // HELP!
	 // Is it necessary or wise to use a vector instead of this fixed size array for this purpose?
	 Animations* animation[NUM_ANIMATIONS_PER_STRIP];	// Array of animations currently active on this strip.
	 uint32_t numAnimations;			// Current number of animations active on this strip.

	 bool autoplay;						// If TRUE then the current pattern (or preset!) will change every autoplayDuration seconds.
	 uint32_t autoplayDuration;
	 unsigned long autoPlayTimeout;

	 bool cyclePalettes;				// If TRUE then the current palette will change every paletteDuration seconds.
	 uint32_t paletteDuration;
	 unsigned long paletteTimeout;

	 uint8_t curPattern;
	 uint8_t curPaletteIndex;
	 CRGBPalette16 curPalette;
	 CRGBPalette16 tarPalette;

 public:

	 // Constructor specifies strip index, number of LEDs, and shape of strip.
	 StripController(uint32_t newIndex, uint32_t newNumLEDs);//, Shapes newShape);

	 void UpdateStrip();	// Updates each animation running on the strip and combines them to be displayed.
	 void ResetTimeouts();	// Resets the timeouts for auto preset and palette rotation.
	
	 void NextPattern();	// Advances the pattern playing on the strip. TODO replace with presets instead of simple patterns.
	 void NextPalette();	// Advances the palette being used by animations on the strip.

	 void AddAnimation(); // Adds a new animation to start playing on the strip. Characteristics are set via preset.

	 //void StackAnimations();// Combine all animation CRGB[]s into the strip's CRGBSet.

};