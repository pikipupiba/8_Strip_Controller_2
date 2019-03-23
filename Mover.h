#pragma once
#include "Animations.h"
#include "globalStuff.h"

class Mover :
	public Animations
{
public:
	Mover(StripController* newStrip);
	~Mover();

	void Draw(int scaleValues);

};

