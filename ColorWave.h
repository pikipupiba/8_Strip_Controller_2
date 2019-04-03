#include "stdafx.h"

#pragma once
#include "Animation.h"
#include "globalStuff.h"

class ColorWave :
	public Animation
{
public:
	ColorWave(StripController* newStrip);
	ColorWave(StripController * newStrip, aniArg newAniArgs[]);
	~ColorWave();

	void Erase();
	void Draw();
};

