#pragma once

#include <arduino.h>
#include <FastLED.h>
#include "patterns.h"

class PatternClass
{
private:
	
	int curPattern;

	float hue
	float hueSpeed;
	float position;
	float speed;
	float size;
	
	CRGBSet* leds;

public:
	
	void PatternClass(CRGBSet* leds);
	void ~PatternClass();
		
	void Update();
	
	void Prev();
	void Next();
	
	void SetPlaylist();
};
