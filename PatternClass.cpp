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
			curPattern = x;
			stage = 100;
			started = 0;
		}
	}

	patternNumAnimations = 0;

	stage = 100;
	started = 0;

	nextStageTime = millis();

	Update();

	D(endTime("PatternClass::PatternClass()");)
}


PatternClass::~PatternClass()
{
}

void PatternClass::Update()
{
	D(startTime("PatternClass::Update()");)

	(this->*curPattern.patternMeth)();

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

bool PatternClass::AddAnimation(String newAnimation)
{
	D(startTime("PatternClass::AddAnimation(int stufff)");)

		if (patternNumAnimations < NUM_ANIMATIONS_PER_PATTERN)
		{
			if (newAnimation == "Mover")
			{

				patternAnimations[patternNumAnimations] = new Mover(strip);

				//patternAnimations[patternNumAnimations]->PrintAnimationInfo(String(strip->stripIndex) + "-" + String(patternNumAnimations));

			}
			else if (newAnimation == "Color Wave")
			{

				patternAnimations[patternNumAnimations] = new ColorWave(strip);

				//patternAnimations[patternNumAnimations]->PrintAnimationInfo(String(strip->stripIndex) + "-" + String(patternNumAnimations));

			}

			patternNumAnimations++;

			return 1;
		}
		else {
			return 0;
		}

	D(endTime("PatternClass::AddAnimation(int stufff)");)
}

void PatternClass::NextPattern()
{
	int newIndex = (curPattern.index + 1) % numPatterns;

	curPattern = patterns[newIndex];

	stage = 100;
	started = 0;

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
	static int numMovers = 10;
	static int prevStage = 100;
	
	if (NextStage())
	{
		prevStage = stage;

		switch (stage)
		{
		case 0:

			D(middleTime("Poopy worm 1 case 0");)

			ClearAnimations();

			for (int i = 0; i < numMovers; i++)
			{
				if (AddAnimation("Mover"))
				{
					patternAnimations[patternNumAnimations - 1]->position = strip->stripRangeStart + 5;
					patternAnimations[patternNumAnimations - 1]->speed = 0.2;
					patternAnimations[patternNumAnimations - 1]->hue = i * (255 / numMovers);
					patternAnimations[patternNumAnimations - 1]->rangeStart = strip->stripRangeStart + i * (strip->stripNumLEDs / numMovers);
					patternAnimations[patternNumAnimations - 1]->rangeEnd = strip->stripRangeStart + (i + 1) * (strip->stripNumLEDs / numMovers);
				}
			}

			break;

		case 1:
			//debugCounter();
			D(middleTime("Poopy worm 1 case 1");)

			ClearAnimations();

			for (int i = 0; i < numMovers; i++)
			{
				if (AddAnimation("Mover"))
				{
					patternAnimations[patternNumAnimations - 1]->position = strip->stripRangeEnd - 5;
					patternAnimations[patternNumAnimations - 1]->speed = -0.2;
					patternAnimations[patternNumAnimations - 1]->hue = i * (255 / numMovers);
					patternAnimations[patternNumAnimations - 1]->rangeStart = strip->stripRangeStart + i * (strip->stripNumLEDs / numMovers);
					patternAnimations[patternNumAnimations - 1]->rangeEnd = strip->stripRangeStart + (i + 1) * (strip->stripNumLEDs / numMovers);
				}
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

		if (AddAnimation("Color Wave"))
		{
			patternAnimations[patternNumAnimations - 1]->hueSpeed = 1;
			patternAnimations[patternNumAnimations - 1]->featureSize = 20;
		}

		started = 1;
	}

	D(endTime("PatternClass::ColorWaves");)
}

void PatternClass::ColorWavesWithMovers()
{
	static int started = 0;
	static int numMovers = 10;

	if (started == 0)
	{
		ClearAnimations();

		if (AddAnimation("Color Wave"))
		{
			patternAnimations[patternNumAnimations - 1]->hueSpeed = 1;
			patternAnimations[patternNumAnimations - 1]->featureSize = 20;
		}


		for (int i = 0; i < numMovers; i++)
		{
			if (AddAnimation("Mover"))
			{
				patternAnimations[patternNumAnimations - 1]->speed = -0.2;
				patternAnimations[patternNumAnimations - 1]->hue = i * (255 / numMovers);
				patternAnimations[patternNumAnimations - 1]->rangeStart = strip->stripRangeStart + i * (strip->stripNumLEDs / numMovers);
				patternAnimations[patternNumAnimations - 1]->rangeEnd = strip->stripRangeStart + (i + 1) * (strip->stripNumLEDs / numMovers);
			}

		}

		started = 1;
	}
}

void PatternClass::ColorPulses()
{
	D(startTime("PatternClass::ColorPulses");)

		static Oscillator o = Oscillator(10, -0.02, 0.02);
	static Oscillator o2 = Oscillator(1, strip->stripRangeStart, strip->stripRangeEnd);

	static Oscillator o3 = Oscillator(3, -0.3, 0.3);
	static Oscillator o4 = Oscillator(3, 3, 10);

	if (started == 0)
	{
		ClearAnimations();

		for (int i = 0; i < NUM_ANIMATIONS_PER_PATTERN; i++)
		{
			aniArg newAniArgs2[] = {
				{ "speed", 0.1 }, // *((i % 2) ? -1 : 1) },
				{ "hue", i * 7 * (255 / NUM_ANIMATIONS_PER_PATTERN) },
				//{ "position", strip->stripRangeStart + i * (strip->stripNumLEDs / NUM_ANIMATIONS_PER_PATTERN) },
				//{ "rangeStart", strip->stripRangeStart + i * (strip->stripNumLEDs / NUM_ANIMATIONS_PER_PATTERN) },
				//{ "rangeEnd", strip->stripRangeStart + (i + 1) * (strip->stripNumLEDs / NUM_ANIMATIONS_PER_PATTERN) },
				{ "", 0 }
			};

			//AddAnimation("Mover", newAniArgs2);

		}

		started = 1;
	}
	else
	{

		for (int i = 0; i < NUM_ANIMATIONS_PER_PATTERN; i++)
		{
			aniArg newAniArgs2[] = {
				{ "speed",	o3.O4(2500 * i) },
				{ "featureSize", o4.O4(2500 * i) },
				//{ "rangeStart",		o2.O4( i * 150) },
				//{ "rangeEnd",		o2.O4( i * 500) },
				{ "", 0 }
			};

			patternAnimations[i]->AssignVals(newAniArgs2);

			patternAnimations[i]->BounceOffOther();
		}
	}

	D(endTime("PatternClass::ColorPulses");)
}

void PatternClass::FunkyMover()
{
	static Oscillator oSpeed = Oscillator(4, -0.8, 0.8);
	static Oscillator oHue = Oscillator(1, 0, 510);
	static Oscillator o5 = Oscillator(1, (strip->stripRangeEnd - strip->stripRangeStart) / 2 + 10, strip->stripRangeEnd);


	static Oscillator o3 = Oscillator(6, -0.3, 1.5);
	static Oscillator oSize = Oscillator(10, 3, 100);

	if (started == 0)
	{
		ClearAnimations();

		for (int i = 0; i < 2; i++)
		{
			if (AddAnimation("Mover"))
			{
				patternAnimations[patternNumAnimations - 1]->speed = 0;
			}
		}

		started = 1;
	}
	else
	{

		aniArg newAniArgs[] = {
			{ "speed",	oSpeed.O4(0) },
			{ "featureSize", oSize.O4(0) },
			{ "hue",		oHue.O4(150) },
			//{ "rangeEnd",		o5.O4(i * 500) },
			{ "", 0 }
		};

		patternAnimations[0]->AssignVals(newAniArgs);

		aniArg newAniArgs2[] = {
			{ "position",	strip->stripRangeEnd + 1 - ((int)patternAnimations[0]->position - strip->stripRangeStart) },
			{ "featureSize", patternAnimations[0]->featureSize },
			{ "hue",		oHue.O4(37000) },
			//{ "rangeEnd",		o5.O4(i * 500) },
			{ "", 0 }
		};

		patternAnimations[1]->AssignVals(newAniArgs2);


	}
}

void PatternClass::Plasma()
{
	// Persistent local variables
	static int16_t thisphase = 0;                                                 // Phase of a cubicwave8.
	static int16_t thatphase = 0;                                                 // Phase of the cos8.

  // Temporary local variables
	uint16_t thisbright;
	uint16_t colorIndex;

	timeval = 20;                                                                 // Our EVERY_N_MILLIS_I timer value.

	thisphase += beatsin8(6, -4, 4);                                                // You can change direction and speed individually.
	thatphase += beatsin8(7, -4, 4);                                                // Two phase values to make a complex pattern. By Andrew Tuline.

	for (int k = 0; k < NUM_LEDS; k++) {                                              // For each of the LED's in the strand, set a brightness based on a wave as follows.
		thisbright = cubicwave8((k * 8) + thisphase) / 2;
		thisbright += cos8((k * 10) + thatphase) / 2;                                     // Let's munge the brightness a bit and animate it all with the phases.
		colorIndex = thisbright;
		thisbright = qsuba(thisbright, 255 - sampleavg);                              // qsuba chops off values below a threshold defined by sampleavg. Gives a cool effect.

		leds[k] = ColorFromPalette(currentPalette, colorIndex, thisbright, currentBlending);   // Let's now add the foreground colour.
	}

	addGlitter(sampleavg / 2);                                                      // Add glitter based on sampleavg.

}
