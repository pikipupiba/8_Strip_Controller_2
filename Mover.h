#pragma once
#include "Animations.h"
class Mover :
	public Animations
{
public:
	Mover(uint32_t newPreset);
	~Mover();

	void Update();
	void Draw();

};

