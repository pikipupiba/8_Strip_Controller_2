#include "stdafx.h"
#include "PatternClass.h"
#include "stripController.h"

PatternClass::PatternClass(StripController* newStrip, String newPattern)
{
	D(startTime("PatternClass::PatternClass()");)

	strip = newStrip;

	index = strip->stripNumPatterns - 1;

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

void PatternClass::AddAnimation(String newAnimation, aniArg newAniArgs[])
{
	D(startTime("PatternClass::AddAnimation(int stufff)");)

		if (patternNumAnimations < NUM_ANIMATIONS_PER_PATTERN)
		{
			if (newAnimation == "Mover")
			{

				patternAnimations[patternNumAnimations] = new Mover(strip, newAniArgs);

				//patternAnimations[patternNumAnimations]->PrintAnimationInfo(String(strip->stripIndex) + "-" + String(patternNumAnimations));

			}
			else if (newAnimation == "Color Wave")
			{

				patternAnimations[patternNumAnimations] = new ColorWave(strip, newAniArgs);

				//patternAnimations[patternNumAnimations]->PrintAnimationInfo(String(strip->stripIndex) + "-" + String(patternNumAnimations));

			}

			patternNumAnimations++;
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
				//debugCounter();
				delete patternAnimations[i];
				patternAnimations[i] = NULL;

				patternNumAnimations--;
			}
		}

	D(endTime("PatternClass::ClearAnimations()");)
}

void PatternClass::PrintPatternInfo()
{
	Serial.println();

	Serial.print("Pattern ID: ");
	Serial.println(index);

	Serial.print("Pattern Range Start: ");
	Serial.println(strip->stripRangeStart);
	Serial.print("Pattern Range End: ");
	Serial.println(strip->stripRangeEnd);

	Serial.println();
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
			//debugCounter();

			D(middleTime("Poopy worm 1 case 0");)

				ClearAnimations();

			for (int i = 0; i < NUM_ANIMATIONS_PER_PATTERN; i++)
			{
				aniArg newAniArgs[] = {
					{ "position", strip->stripRangeStart + 5 },
					{ "speed", 0.2 },
					{ "hue", i * (255 / NUM_ANIMATIONS_PER_PATTERN) },
					{ "rangeStart", strip->stripRangeStart + i * (strip->stripNumLEDs / NUM_ANIMATIONS_PER_PATTERN) },
					{ "rangeEnd", strip->stripRangeStart + (i + 1) * (strip->stripNumLEDs / NUM_ANIMATIONS_PER_PATTERN) },
					{ "", 0}
				};

				AddAnimation("Mover", newAniArgs);
			}

			break;

		case 1:
			//debugCounter();
			D(middleTime("Poopy worm 1 case 1");)

				ClearAnimations();

			for (int i = 0; i < NUM_ANIMATIONS_PER_PATTERN; i++)
			{
				aniArg newAniArgs[] = {
					{ "position", strip->stripRangeEnd - 5 },
					{ "speed", -0.2 },
					{ "hue", i * (255 / NUM_ANIMATIONS_PER_PATTERN) },
					{ "rangeStart", strip->stripRangeStart + i * (strip->stripNumLEDs / NUM_ANIMATIONS_PER_PATTERN) },
					{ "rangeEnd", strip->stripRangeStart + (i + 1) * (strip->stripNumLEDs / NUM_ANIMATIONS_PER_PATTERN) },
					{ "", 0 }
				};

				AddAnimation("Mover", newAniArgs);
				
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

void PatternClass::ColorWaves()
{
	D(startTime("PatternClass::ColorWaves");)

		static int started = 0;

	if (started == 0)
	{
		ClearAnimations();
		started = 1;
	}

	for (int i = 0; i < NUM_ANIMATIONS_PER_PATTERN; i++)
	{
		aniArg newAniArgs[] = {
			{ "speed", 0.2 },
			{ "featureSize", 20 },
			{ "", 0 }
		};

		AddAnimation("Color Wave", newAniArgs);
	}

	D(endTime("PatternClass::ColorWaves");)
}
