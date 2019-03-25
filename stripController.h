// stripController.h
#pragma once
//#include <stdint.h>
#include <FastLED.h>
//#include "defaultSettings.h"
#include "Animations.h"
#include "Mover.h"

#include "globalStuff.h"
#include "tasks.h"

extern CRGBArray<NUM_LEDS> leds;

// HELP!
// Is my whole paradigm of using strip controller objects to combine animation objects onto a strip a good one?
// If this is the way to go, are my design decisions taking me in the right direction?

// Each strip controller consists of a CRGBSet containing it's subset of LEDs, strip variables inherited
// by each animatioin playing on it, and an array of animations currently running on the strip.
class StripController
{
protected:
	
 public:

	 // The index of the strip determines its output pin.
	 int stripIndex;
	 // The strip's physical location within the master array of LEDs.
	 int stripRangeStart;
	 int stripRangeEnd;

	 // The real number of LEDs contained by the strip.
	 // There are 300 reserved LEDs in the CRGBArray leds for each strip regaurdless of actual size.
	 // TODO Find our if I can change the master CRGBArray during excecution to only store the necessary number of LEDs.
	 int stripNumLEDs;

	 // The CRGBSet containing the number of LEDs on this strip.
	 //struct CRGB stripLEDs[300];

	 Shapes stripShape;					// The default shape of animations created on this strip.
	 Textures stripTexture;				// A modifier applied to the strip after values are calculated.
	 EndOfRanges stripEndOfRange;		// The default behavior of animations created on this strip.

	 bool stripPower;					// If FALSE then the strip brightness is temporarily set to 0.
	 float stripBrightness;				// The strip brightness is adjusted to this value after LEDs are written, maintaining relative animation brightnesses.

										// HELP!
										// Is it necessary or wise to use a vector instead of this fixed size array for this purpose?
	 Animations* animation[NUM_ANIMATIONS_PER_STRIP];	// Array of animations currently active on this strip.
	 int numAnimations;			// Current number of animations active on this strip.

	 bool autoplay;						// If TRUE then the current pattern (or preset!) will change every autoplayDuration seconds.
	 int autoplayDuration;
	 unsigned long autoPlayTimeout;

	 bool cyclePalettes;				// If TRUE then the current palette will change every paletteDuration seconds.
	 int paletteDuration;
	 unsigned long paletteTimeout;

	 uint8_t curPattern;
	 uint8_t curPaletteIndex;
	 CRGBPalette16 curPalette;
	 CRGBPalette16 tarPalette;

	 // Constructor specifies strip index, number of LEDs, and shape of strip.
	 StripController(int newIndex, int newNumLEDs);//, Shapes newShape);

	 void UpdateStrip();	// Updates each animation running on the strip and combines them to be displayed.
	 void ResetTimeouts();	// Resets the timeouts for auto preset and palette rotation.
	
	 void NextPattern();	// Advances the pattern playing on the strip. TODO replace with presets instead of simple patterns.
	 void NextPalette();	// Advances the palette being used by animations on the strip.

	 void AddAnimation(); // Adds a new animation to start playing on the strip. Characteristics are set via preset.
	 void AddAnimation(String newAnimation, float position, float speed, float newHue, int rangeStart, int rangeEnd);

	 void PrintStripInfo();

	 //void StackAnimations();// Combine all animation CRGB[]s into the strip's CRGBSet.

};