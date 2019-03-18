#pragma once

// HELP!
// Are my design decisions in this section going to achieve what I want?

// Animation objects contain properties and rules for displaying a specific pattern to a CRGBSet.
// For an example of usage check out my AnimationClassTest Repo on GitHub.

// 32-bit int math is way faster than float math so I an using 32-bit integers and using normalizeValues.h to map them
// to a decimal value between 0...255 (for example 178.035) when the extra precision is needed. I think this
// will allow for fast math as well as very gradual modification ability. I use unsigned where applicable.

// The fractional parts are used to allow smooth transitions via fading features in and out as well as for antialiasing.

// Right now I think each animation object uses between 1 KB and 2 KB of memory. Not sure if that is a lot...
// With 8 strips each containing a maximum of 10 animations I potentially need room for 80 animation objects.

//#include <stdint.h>
//#include <FastLED.h>
//#include "defaultSettings.h"

class Animations
{
private:

protected:
	

public:
	// Public variables allow effect functions to be written easier and with less overhead.

	// The array of pixel values currently being used by the animation.
	struct CRGB animationLEDs[300];

	// The index position helps layer different animations together in the final step.
	uint32_t indexPosition;

	// Where on the strip the animation should start and end.
	uint32_t rangeStart;
	uint32_t rangeEnd;
	uint32_t rangeSize; // Automatically calculated rangeSize for easier to read code.

	Shapes animationShape;				// The shape of the strip the animation is playing on.
	Textures animationTexture;			// A modifier applied to the animation after values are calculated.
	EndOfRanges animationEndOfRange;	// How an animation acts when it approaches the end of its range.

	uint32_t brightness;
	uint32_t hue;			// Hue is the starting value used to calculate the various colors in an animation step.
	int hueSpeed;			// Hue speed is how much hue changes each step.
	int hueAcceleration;	// Hue acceleration is how much hue speed changes each step.

	uint32_t position;		// Position can either be where an object is in its range or the current step in a sequence it is on.
	int speed;				// How much position changes each step.
	int acceleration;		// How much speed changes each step.

	uint32_t featureSize;	// Used to describe the size of a "feature" of the animation. Usually equals end2 - end1.
	uint32_t end1;			// Keeps track of one end of a "feature."
	uint32_t end2;			// Keeps track of the other end of a "feature."

	uint32_t numRepeats;		// Used to copy a small animation to different positions in its range.
	int repeatPositionOffset;	// How much the position of each repeat is offset from the previous one.
	int repeatHueOffset;		// How much the hue of each repeat is offset from the previous one.

	// Constructors and destructors.
	Animations();
	~Animations();

	// Virtual functions that each child needs to implement to work.
	void UpdatePosition();
	void Update();	// Update the animation variables based on speeds, oscillators, etc.
	void Draw();	// Draw the animation into it's CRGB[] based on its parameters. 

};