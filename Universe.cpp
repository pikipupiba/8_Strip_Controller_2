#include "Universe.h"


Universe::Universe()
{
	D(startTime("Universe::Universe()");)

	gNumLeds = 0;
	int numLedsSoFar = 0;

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		D(middleTime("Universe::Universe()");)

		if (i == 0)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_0, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_0).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_0;
		}
		else if (i == 1)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_1, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_1).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_1;
		}
		else if (i == 2)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_2, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_2).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_2;
		}
		else if (i == 3)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_3, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_3).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_3;
		}
		else if (i == 4)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_4, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_4).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_4;
		}
		else if (i == 5)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_5, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_5).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_5;
		}
		else if (i == 6)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_6, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_6).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_6;
		}
		else if (i == 7)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_7, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_7).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_7;
		}

		//Serial.println(gNumLeds);
		//Serial.println(numLedsSoFar - 1);

		ledSets[i] = new CRGBSet( gLeds(gNumLeds, numLedsSoFar - 1));

		strips[i] = new LEDStrip( ledSets[i] );

		gNumLeds = numLedsSoFar;
	}

	gLeds.fill_solid(CRGB::Black);

	D(endTime("Universe::Universe()");)
}


Universe::~Universe()
{
}

Universe* Universe::CreateUniverse()
{
	D(startTime("Universe::CreateUniverse()");)
	return new Universe();
	D(endTime("Universe::CreateUniverse()");)
}

void Universe::Update()
{
	D(startTime("Universe::Update()");)

	EVERY_N_SECONDS(10)
	{
		for (int i = 0; i < NUM_STRIPS; i++)
		{
			strips[i]->NextPattern();
		}
	}

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->UpdateStrip();
	}

	D(endTime("Universe::Update()");)
}

void Universe::PrintInfo()
{
	Serial.println();

	Serial.println("Universe Information:");
	Serial.println();

	Serial.print(NUM_STRIPS);
	Serial.println(" Strips");
	Serial.print(gNumLeds);
	Serial.println(" LEDs");

	Serial.println();
}