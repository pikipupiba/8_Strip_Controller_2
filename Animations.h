#pragma once


#include <FastLED.h>
#include "globalStuff.h"
class StripController;

#include "tasks.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Animations
{
private:

protected:
	
public:	// Public variables allow effect functions to be written easier and with less overhead.

	StripController* strip;

	uint32_t indexPosition;	// The index position helps layer different animations together in the final step.

	uint32_t rangeStart;	// Where on a strip an animation starts.
	uint32_t rangeEnd;		// Where on a strip an animation ends.
	uint32_t rangeSize;		// Automatically calculated rangeSize for easier to read code.

	Shapes animationShape;			// The shape of the strip the animation is playing on.
	Textures animationTexture;		// A modifier applied to the animation after values are calculated.
	EndOfRanges animationEndOfRange;// How an animation acts when it approaches the end of its range.

	float brightness;		// The brightness of an animation before being scaled by strip and global brightness.
	float hue;				// Hue is the starting value used to calculate the various colors in an animation step.
	float hueSpeed;			// Hue speed is how much hue changes each step.
	float hueAcceleration;	// Hue acceleration is how much hue speed changes each step.

	float position;		// Position can either be where an object is in its range or the current step in a sequence it is on.
	float speed;		// How much position changes each step.
	float acceleration;	// How much speed changes each step.

	float featureSize;	// Used to describe the size of a "feature" of the animation. Usually equals end2 - end1.
	float end1;			// Keeps track of one end of a "feature."
	float end2;			// Keeps track of the other end of a "feature."

	float numRepeats;			// Used to copy a small animation to different positions in its range.
	float repeatPositionOffset;	// How much the position of each repeat is offset from the previous one.
	float repeatHueOffset;		// How much the hue of each repeat is offset from the previous one.
	

	// Constructors and destructors.
	Animations();
	virtual ~Animations();

	// Virtual functions that each child needs to implement to work.
	void UpdatePosition();
	virtual void Update();	// Update the animation variables based on speeds, oscillators, etc.
	virtual void Draw(int scaleValues = 1) = 0;	// Draw the animation into it's CRGB[] based on its parameters.
};