#include "stdafx.h"

#pragma once
#include "Animation.h"
#include "globalStuff.h"

// A Mover is just a section of pixels that moves along a strip and can either bounce
// off the end of it's range or loop back to the beginning. The ends are antialiased.

class Mover :
	public Animation
{
public:
	Mover(StripController* newStrip);
	Mover(StripController* newStrip, aniArg newAniArgs[]);
	~Mover();

	void Erase();
	void Draw();

};

