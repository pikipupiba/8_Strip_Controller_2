#pragma once
#include "Animations.h"
#include "globalStuff.h"

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

