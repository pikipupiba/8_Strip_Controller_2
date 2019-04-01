#include "stdafx.h"
#include "PatternClass.h"
#include "stripController.h"

PatternClass::PatternClass(StripController* newStrip, String newPattern)
{
	D(startTime("PatternClass::PatternClass()");)

	strip = newStrip;

	for (Pattern x : patterns)
	{
		if (x.name == newPattern)
		{
			curPatternMeth = x.patternMeth;
		}
	}

	patternNumAnimations = 0;

	stage = 100;

	nextStageTime = millis();

	D(endTime("PatternClass::PatternClass()");)
}


PatternClass::~PatternClass()
{
}

void PatternClass::Update()
{
	D(startTime("PatternClass::Update()");)

	(this->*curPatternMeth)();

	for (int i = 0; i < patternNumAnimations; i++)
	{
		patternAnimations[i]->Update();
	}

	D(endTime("PatternClass::Update()");)
}

int PatternClass::NextStage()
{
	D(startTime("PatternClass::NextStage");)

	if (millis() > nextStageTime)
	{
		stage++;
		nextStageTime = millis() + stageTime;

		if (stage > numStages)
		{
			stage = 0;
		}

		D(endTime("PatternClass::NextStage");)
		return 1;
	}
	
	D(endTime("PatternClass::NextStage");)
	return 0;

}

void PatternClass::AddAnimation()
{
	D(startTime("PatternClass::AddAnimation()");)

		if (patternNumAnimations < NUM_PATTERNS_PER_STRIP)
		{

			// TODO Figure out how to initialize an animation object like this.
			// This has not been worked on at all yet.
			// Will probably use a similar system to the following taken from my AnimationClassTest.ino at line 42.
			// typedef void(*SimplePatternList[])();
			// SimplePatternList gPatterns = { pattern1, pattern2, pattern3};

			patternAnimations[patternNumAnimations] = new Mover(strip);

			patternNumAnimations++;
		}

	D(endTime("PatternClass::AddAnimation()");)
}

void PatternClass::AddAnimation(String newAnimation, float newPosition, float newSpeed, float newHue, int newRangeStart, int newRangeEnd)
{
	D(startTime("PatternClass::AddAnimation(int stufff)");)

		if (newAnimation == "Mover")
		{
			if (patternNumAnimations < NUM_ANIMATIONS_PER_PATTERN)
			{
				patternAnimations[patternNumAnimations] = new Mover(strip, newPosition, newSpeed, newHue, newRangeStart, newRangeEnd);

				patternNumAnimations++;
			}
		}
	D(endTime("PatternClass::AddAnimation(int stufff)");)
}

void PatternClass::ClearAnimations()
{
	D(startTime("PatternClass::ClearAnimations()");)

		for (int i = patternNumAnimations - 1; i >= 0; i--)
		{
			if (patternAnimations[i] == NULL)
			{
			}
			else
			{
				delete patternAnimations[i];
				patternAnimations[i] = NULL;

				patternNumAnimations--;
			}
		}

	D(endTime("PatternClass::ClearAnimations()");)
}

void PatternClass::PoopyWorm1()
{
	D(startTime("PatternClass::PoopyWorm1");)

		numStages = 1;
		stageTime = 15000;

	static int prevStage = 100;
	
	if (NextStage())
	{
		prevStage = stage;

		switch (stage)
		{
		case 0:

			D(middleTime("Poopy worm 1 case 0");)

				ClearAnimations();

			for (int i = 0; i < NUM_ANIMATIONS_PER_PATTERN; i++)
			{
				AddAnimation("Mover", strip->stripRangeStart + 5, 0.2, i * (255 / NUM_ANIMATIONS_PER_PATTERN), strip->stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_PATTERN), strip->stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_PATTERN));
			}
			break;

		case 1:

			D(middleTime("Poopy worm 1 case 1");)
				Serial.println("Thing here");

				ClearAnimations();

			for (int i = 0; i < NUM_ANIMATIONS_PER_PATTERN; i++)
			{
				AddAnimation("Mover", strip->stripRangeEnd - 5, -0.2, i * (255 / NUM_ANIMATIONS_PER_PATTERN), strip->stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_PATTERN), strip->stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_PATTERN));
			}
			break;
		}
	}
	
		D(endTime("PatternClass::PoopyWorm1");)
}

void PatternClass::PoopyWorm2()
{
	D(startTime("poopyWorm2");)
/*
		static int stage = 0;


	switch (stage)
	{
	case 0:

		D(middleTime("Poopy worm 2 case 0");)

			ClearAnimations();

		for (int i = 0; i < NUM_PATTERNS_PER_STRIP / 2; i++)
		{
			AddAnimation("Mover", stripRangeStart + 5, 0.1, i * (255 / NUM_PATTERNS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_PATTERNS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_PATTERNS_PER_STRIP));
		}
		for (int i = NUM_PATTERNS_PER_STRIP / 2; i < NUM_PATTERNS_PER_STRIP; i++)
		{
			AddAnimation("Mover", stripRangeEnd - 5, -0.1, i * (255 / NUM_PATTERNS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_PATTERNS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_PATTERNS_PER_STRIP));
		}

		stage++;
		break;

	case 1:

		D(middleTime("Poopy worm 2 case 1");)

			ClearAnimations();

		for (int i = 0; i < NUM_PATTERNS_PER_STRIP / 2; i++)
		{
			AddAnimation("Mover", (stripRangeStart + stripRangeEnd) / 2, -0.1, i * (255 / NUM_PATTERNS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_PATTERNS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_PATTERNS_PER_STRIP));
		}
		for (int i = NUM_PATTERNS_PER_STRIP / 2; i < NUM_PATTERNS_PER_STRIP; i++)
		{
			AddAnimation("Mover", (stripRangeStart + stripRangeEnd) / 2, 0.1, i * (255 / NUM_PATTERNS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_PATTERNS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_PATTERNS_PER_STRIP));
		}

		stage = 0;
		break;
	}
	*/
	D(endTime("poopyWorm2");)
}
