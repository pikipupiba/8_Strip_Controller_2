#pragma once
#include "Animations.h"
#include "defaultSettings.h"
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

