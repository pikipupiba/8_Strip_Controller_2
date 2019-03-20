#pragma once
#include "Animations.h"
#include "globalStuff.h"
#include "normalizeValues.h"
class Mover :
	public Animations
{
public:
	Mover();
	~Mover();

	void Update();
	void Draw();

};

