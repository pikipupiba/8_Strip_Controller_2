#include "stdafx.h"
#include "PatternClass.h"


PatternClass::PatternClass()
{
}


PatternClass::~PatternClass()
{
}

void PatternClass::PoopyWorm1()
{
	D(startTime("poopyWorm1");)

	/*	static int stage = 0;

	// TODO Move these to being time dependant like displaying the menu.
	switch (stage)
	{
	case 0:

		D(middleTime("Poopy worm 1 case 0");)

			ClearAnimations();

		for (int i = 0; i < NUM_ANIMATIONS_PER_STRIP; i++)
		{
			AddAnimation("Mover", stripRangeStart + 5, 0.2, i * (255 / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}
		stage++;
		break;

	case 1:

		D(middleTime("Poopy worm 1 case 1");)

			ClearAnimations();

		for (int i = 0; i < NUM_ANIMATIONS_PER_STRIP; i++)
		{
			AddAnimation("Mover", stripRangeEnd - 5, -0.2, i * (255 / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}
		stage = 0;
		break;
	}
	*/
	D(endTime("poopyWorm1");)
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

		for (int i = 0; i < NUM_ANIMATIONS_PER_STRIP / 2; i++)
		{
			AddAnimation("Mover", stripRangeStart + 5, 0.1, i * (255 / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}
		for (int i = NUM_ANIMATIONS_PER_STRIP / 2; i < NUM_ANIMATIONS_PER_STRIP; i++)
		{
			AddAnimation("Mover", stripRangeEnd - 5, -0.1, i * (255 / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}

		stage++;
		break;

	case 1:

		D(middleTime("Poopy worm 2 case 1");)

			ClearAnimations();

		for (int i = 0; i < NUM_ANIMATIONS_PER_STRIP / 2; i++)
		{
			AddAnimation("Mover", (stripRangeStart + stripRangeEnd) / 2, -0.1, i * (255 / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}
		for (int i = NUM_ANIMATIONS_PER_STRIP / 2; i < NUM_ANIMATIONS_PER_STRIP; i++)
		{
			AddAnimation("Mover", (stripRangeStart + stripRangeEnd) / 2, 0.1, i * (255 / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + i * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP), stripRangeStart + (i + 1) * (NUM_LEDS_PER_STRIP / NUM_ANIMATIONS_PER_STRIP));
		}

		stage = 0;
		break;
	}
	*/
	D(endTime("poopyWorm2");)
}
