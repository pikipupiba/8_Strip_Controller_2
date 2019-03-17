#pragma once
#include "Animations.h"
class Mover :
	public Animations
{
public:
	Mover();
	~Mover();

	void Update();
	void Draw();

};

