// stripController.h
#pragma once

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
	 CRGBSet stripLEDs;

	 Shapes stripShape;					// The default shape of animations created on this strip.
	 Textures stripTexture;				// A modifier applied to the strip after values are calculated.
	 EndOfRanges stripEndOfRange;		// The default behavior of animations created on this strip.

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
	 StripController(uint32_t newIndex, uint32_t newNumLEDs, Shapes newShape);

	 void UpdateStrip();	// Updates each animation running on the strip and combines them to be displayed.
	 void ResetTimeouts();	// Resets the timeouts for auto preset and palette rotation.
	
	 void NextPattern();	// Advances the pattern playing on the strip. TODO replace with presets instead of simple patterns.
	 void NextPalette();	// Advances the palette being used by animations on the strip.

	 void AddAnimation(uint32_t newAnimationPreset); // Adds a new animation to start playing on the strip. Characteristics are set via preset.

	 void StackAnimations();// Combine all animation CRGB[]s into the strip's CRGBSet.

};