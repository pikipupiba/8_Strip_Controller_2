#include "stdafx.h"

#pragma once
#include "Animations.h"
#include "globalStuff.h"

// A Mover is just a section of pixels that moves along a strip and can either bounce
// off the end of it's range or loop back to the beginning. The ends are antialiased.

class Mover :
	public Animations
{
public:
	Mover(StripController* newStrip);
	Mover(StripController* newStrip, float position, float speed, float newHue, int rangeStart, int rangeEnd);
	~Mover();

	void Erase();
	void Draw();

};

