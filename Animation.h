#include "stdafx.h"

#pragma once



#include "globalStuff.h"
class StripController;

//class StripController;

#include "tasks.h"

extern StripController* strips[8];

class Animation
{
private:

protected:

	StripController* strip;

	int indexPosition;	// The index position helps layer different animations together in the final step.

	int rangeStart;	// Where on a strip an animation starts.
	int rangeEnd;		// Where on a strip an animation ends.
	int rangeSize;		// Automatically calculated rangeSize for easier to read code.

	Shapes animationShape;			// The shape of the strip the animation is playing on.
	Textures animationTexture;		// A modifier applied to the animation after values are calculated.
	EndOfRanges animationEndOfRange;// How an animation acts when it approaches the end of its range.

	float pBrightness;
	float brightness;		// The brightness of an animation before being scaled by strip and global brightness.
	float tBrightness;

	float pHue;
	float hue;				// Hue is the starting value used to calculate the various colors in an animation step.
	float tHue;

	float pHueSpeed;
	float hueSpeed;			// Hue speed is how much hue changes each step.
	float tHueSpeed;

	float pHueAcceleration;
	float hueAcceleration;	// Hue acceleration is how much hue speed changes each step.
	float tHueAcceleration;

	float pPosition;
	float position;		// Position can either be where an object is in its range or the current step in a sequence it is on.
	float tPosition;

	float pSpeed;
	float speed;		// How much position changes each step.
	float tSpeed;

	float pAcceleration;
	float acceleration;	// How much speed changes each step.
	float tAcceleration;

	float pFeatureSize;
	float featureSize;	// Used to describe the size of a "feature" of the animation. Usually equals end2 - end1.
	float tFeatureSize;

	float end1;			// Keeps track of one end of a "feature."
	float tEnd1;
	float end2;			// Keeps track of the other end of a "feature."
	float tEnd2;

	float numRepeats;			// Used to copy a small animation to different positions in its range.
	float repeatPositionOffset;	// How much the position of each repeat is offset from the previous one.
	float repeatHueOffset;		// How much the hue of each repeat is offset from the previous one.

	float changing;
	
public:	// Public variables allow effect functions to be written easier and with less overhead.

	// Constructors and destructors.
	Animation();
	virtual ~Animation();

	// Virtual functions that each child needs to implement to work.
	virtual void Update();
	virtual void Erase() = 0;
	virtual void Draw() = 0;

	void UpdatePosition();
	void Change();
	//void Randomize();
	void Randomize(String var);

	//void SetPrevVals();
	void SetPrevVals(String var);

	void SetRangeAbsolute(int newRangeStart, int newRangeEnd);
	void SetRangeOnStrip(int newRangeStart, int newRangeEnd);

	void GetBackToRange();
};