#include "Universe.h"


Universe::Universe()
{
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		static int numLedsSoFar = 0;

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

		strips[i] = new LEDStrip( gLeds(gNumLeds, numLedsSoFar) );

		gNumLeds = numLedsSoFar;
	}

}


Universe::~Universe()
{
}

Universe* Universe::CreateUniverse()
{
	return new Universe();
}

void Universe::Update()
{
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->UpdateStrip();
	}
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