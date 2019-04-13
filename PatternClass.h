#include "stdafx.h"

#pragma once
#include "globalStuff.h"
#include "display.h"
#include "Oscillator.h"

class StripController;
#include "Animation.h"
#include "Mover.h"
#include "ColorWave.h"

const int numPatterns = 6;

class PatternClass
{
private:

	typedef void(PatternClass::*PatternMeth)();


	typedef struct {
		int index;
		String name;
		PatternMeth patternMeth;
	} Pattern;

	Pattern curPattern;

	typedef Pattern PatternList[numPatterns];

	PatternList patterns = {
		{ 0, "Poopy Worm 1", &PatternClass::PoopyWorm1 },
		{ 1, "Color Waves", &PatternClass::ColorWaves },
		{ 2, "Color Waves With Movers", &PatternClass::ColorWavesWithMovers },
		{ 3, "Color Pulses", &PatternClass::ColorPulses },
		{ 4, "Funky Mover", &PatternClass::FunkyMover },
		{ 5, "Plasma", &PatternClass::Plasma }
	};
	


	StripController* strip;

	int index;

	Animation* patternAnimations[NUM_ANIMATIONS_PER_PATTERN];
	int patternNumAnimations;

	unsigned long stageTime;
	unsigned long nextStageTime;

	int patternNumber;

	int started;
	int stage;
	int numStages;
	//std::list<Animation*> animations;
	//std::list<Animation*>::iterator it;

public:
	PatternClass(StripController* newStrip, String newPattern);
	~PatternClass();

	void Update();
	int NextStage();

	bool AddAnimation(String newAnimation);

	void NextPattern();

	void ClearAnimations();

	void PrintPatternInfo();

	void PoopyWorm1();
	void PoopyWorm2();

	void ColorWaves();
	void ColorWavesWithMovers();

	void ColorPulses();
	void FunkyMover();

	void Plasma();
};