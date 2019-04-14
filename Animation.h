#include "stdafx.h"
#include "globalStuff.h"

#pragma once

class StripController;
extern StripController* strips[8];

// aniArg is a struct I made to help set animation variables with an array of values.
// Might not be needed any more if using public animation variables is fine.
// Either way there is definitely a faster way to do this than comparing these LONG strings.
typedef struct {
	String name;
	float val;
} aniArg;

// This is the parent class of all the animation objects.
// I'm gonna try to find some relevant aspect of all animations to assign to the generic variable names here.
class Animation
{
private:

	

protected:

public:	// Public variables allows PatternClass methods to be written easier and with less overhead.

	int rangeStart;		// Where on a strip an animation starts.
	int rangeEnd;		// Where on a strip an animation ends.
	int rangeSize;		// Automatically calculated rangeSize for easier to read code.

	Shapes animationShape;			// The shape of the strip the animation is playing on.
	Textures animationTexture;		// A modifier applied to the animation after values are calculated.
	EndOfRanges animationEndOfRange;// How an animation acts when it approaches the end of its range.

	// p = previous ---> Used to keep track when easing animation variables from previous to target value.
	// e = erase    ---> The value the variable had when the last frame was drawn so it can be erased even if it was changed somewhere.
	// t = target	---> The target value for the easing functions found in Changing()

	float pBrightness;
	float eBrightness;
	float brightness;		// The brightness of an animation before being scaled by strip and global brightness.
	float tBrightness;

	float pHue;
	float eHue;
	float hue;				// Hue is the starting value used to calculate the various colors in an animation step.
	float tHue;

	float pHueSpeed;
	float hueSpeed;			// Hue speed is how much hue changes each step.
	float tHueSpeed;

	float pHueAcceleration;
	float hueAcceleration;	// Hue acceleration is how much hue speed changes each step.
	float tHueAcceleration;

	float pPosition;
	float ePosition;
	float position;		// Position can either be where an object is in its range or the current step in a sequence it is on.
	float tPosition;

	float pSpeed;
	float speed;		// How much position changes each step.
	float tSpeed;

	float pAcceleration;
	float acceleration;	// How much speed changes each step.
	float tAcceleration;

	float pFeatureSize;
	float eFeatureSize;
	float featureSize;	// Used to describe the size of a "feature" of the animation. Usually equals end2 - end1.
	float tFeatureSize;

	float eEnd1;
	float end1;			// Keeps track of one end of a "feature."
	float tEnd1;

	float eEnd2;
	float end2;			// Keeps track of the other end of a "feature."
	float tEnd2;

	float numRepeats;			// Used to copy a small animation to different positions in its range.
	float repeatPositionOffset;	// How much the position of each repeat is offset from the previous one.
	float repeatHueOffset;		// How much the hue of each repeat is offset from the previous one.

	float changing;		// changing = 0 means its not currently easing any values from previous to target.

	StripController* strip;	// A pointer to the strip the animation is being displayed on.

	// Constructors and destructors.
	Animation();
	virtual ~Animation();

	// Uses an array of aniArgs to set the animation variables.
	// Might not need if public variables are the way to go.
	void AssignVals(aniArg aniArgs[]);

	// Virtual functions that each child needs to implement to work.
	virtual void Erase() = 0;
	virtual void Draw() = 0;

	void Update();
	void UpdatePosition();

	void Bounce(Direction dir);	// Bounces the mover in a particular direction.
	void BounceOffOther();		// Changes the sign of speed if one of the ends is touching a non black LED.
	void Loop();				// Loops the position back to either the start or end of the range when it goes off the end.

	void CheckRange();

	void Change();
	//void Randomize();
	void Randomize(String var);

	void SetEraseVals();
	//void SetPrevVals();
	void SetPrevVals(String var);

	void SetRangeAbsolute(int newRangeStart, int newRangeEnd);
	void SetRangeOnStrip(int newRangeStart, int newRangeEnd);

	void GetBackToRange();

	void PrintAnimationInfo(String ID);
};