#include "stdafx.h"

#pragma once
#include "globalStuff.h"
#include "display.h"

class StripController;
#include "Animation.h"
#include "Mover.h"

class PatternClass
{
private:

	typedef void(PatternClass::*PatternMeth)();

	PatternMeth curPatternMeth;

	typedef struct {
		String name;
		PatternMeth patternMeth;
	} Pattern;

	typedef Pattern PatternList[2];

	PatternList patterns = {
		{ "Poopy Worm 1", &PatternClass::PoopyWorm1 },
		{ "Poopy Worm 2", &PatternClass::PoopyWorm2 }
	};
	


	StripController* strip;

	Animation* patternAnimations[NUM_ANIMATIONS_PER_PATTERN];
	int patternNumAnimations;

	unsigned long stageTime;
	unsigned long nextStageTime;

	int stage;
	int numStages;
	//std::list<Animation*> animations;
	//std::list<Animation*>::iterator it;

public:
	PatternClass(StripController* newStrip, String newPattern);
	~PatternClass();

	void Update();
	int NextStage();

	void AddAnimation();
	void AddAnimation(String newAnimation, float newPosition, float newSpeed, float newHue, int newRangeStart, int newRangeEnd);

	void ClearAnimations();

	void PoopyWorm1();
	void PoopyWorm2();
};