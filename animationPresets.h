#pragma once

// Animation presets store all the information required to pick an animation up right where it left off.

typedef struct
{
	string animationName;

	// The index position helps layer different animations together in the final step.
	uint32_t indexPosition;

	// Where on the strip the animation should start and end.
	uint32_t rangeStart;
	uint32_t rangeEnd;
	//uint32_t rangeSize; // Automatically calculated rangeSize for easier to read code.

	Shapes animationShape;				// The shape of the strip the animation is playing on.
	Textures animationTexture;			// A modifier applied to the animation after values are calculated.
	Overlays animationOverlay;			// A modifier applied to the animation after values are calculated.
	EndOfRanges animationEndOfRange;	// How an animation acts when it approaches the end of its range.

	uint32_t brightness;
	uint32_t hue;			// Hue is the starting value used to calculate the various colors in an animation step.
	int hueSpeed;			// Hue speed is how much hue changes each step.
	int hueAcceleration;	// Hue acceleration is how much hue speed changes each step.

	uint32_t position;		// Position can either be where an object is in its range or the current step in a sequence it is on.
	int speed;				// How much position changes each step.
	int acceleration;		// How much speed changes each step.

	uint32_t featureSize;	// Used to describe the size of a "feature" of the animation. Usually equals end2 - end1.
	//uint32_t end1;			// Keeps track of one end of a "feature."
	//uint32_t end2;			// Keeps track of the other end of a "feature."

	uint32_t numRepeats;		// Used to copy a small animation to different positions in its range.
	int repeatPositionOffset;	// How much the position of each repeat is offset from the previous one.
	int repeatHueOffset;		// How much the hue of each repeat is offset from the previous one.

	//Oscillators* curOscillators[];

}AnimationPreset;

AnimationPreset FunkyMovers = { "Mover",	0,			0,			uINT32_MAX,	// Name,		index,		rangeStart,		rangeEnd
								Strip,		None,		None,		Bounce,		// Shape,		Texture,	Overlay,		End of Range
								4294967295, 0,			200,		0,			// Brightness,	Hue,		Hue Speed,		Hue Acceleration
								0,			200000,		0,			1000000,		// Position,	Speed,		Acceleration,	Feature Size
								5,			uINT32_MAX/20,	1000000 };				// Num Repeats, Pos Offset,	Hue Offset