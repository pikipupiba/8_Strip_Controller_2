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

	FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS);

	gLeds.fill_solid(CRGB::Black);

	uPower = true;
	uBrightness = 128;
	uSpeed = 0;
	uHue = 0;
	uHueSpeed = 0;
	uOffset = 0;

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

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->UpdateStrip();
	}

	if (uPower)
	{
		FastLED.setBrightness(uBrightness);
	}
	else
	{
		FastLED.setBrightness(0);
	}

	D(endTime("Universe::Update()");)
}

void Universe::NextPattern()
{

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->vars.autoplayDuration = 5000;
		strips[i]->vars.autoplay = false;

		strips[i]->NextPattern();
	}
}

void Universe::ToggleAutoplay()
{

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		if (strips[i]->vars.autoplay == true)
		{
			strips[i]->vars.autoplayDuration += 5000;
		}

		strips[i]->vars.autoplay = true;
	}
}

void Universe::Change(String label, int value)
{
	if (label == "power")
	{
		uPower = value;
	}
	else if (label == "brightness")
	{
		uBrightness = value;
	}
	else if (label == "speed")
	{
		uSpeed = (value + 10000) / 10000 * (20) - 10;
	}
	else if (label == "hue")
	{
		uHue = (value + 10000) / 10000 * (255);
	}
	else if (label == "hueSpeed")
	{
		uHueSpeed = (value + 10000) / 10000 * (20) - 10;
	}
	else if (label == "offset")
	{
		uOffset = value;
	}

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->ChangeVars(uSpeed, uHue, uHueSpeed, uOffset);
	}

}

void Universe::ChangeOffset()
{
	uOffset = (uOffset + 5);
	
	if (uOffset > 37)
	{
		uOffset = 0;
	}

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->vars.position = i * uOffset;
		strips[i]->vars.positionOffset = i * uOffset;
	}
}

void Universe::ChangeHueFactor()
{
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->vars.hueScaleFactor += 0.2;

		if (strips[i]->vars.hueScaleFactor > 2)
		{
			strips[i]->vars.hueScaleFactor = 0;
		}
	}
}

void Universe::ChangeSpeedFactor()
{
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->vars.speedScaleFactor += 0.2;

		if (strips[i]->vars.speedScaleFactor > 2)
		{
			strips[i]->vars.speedScaleFactor = 0;
		}
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

