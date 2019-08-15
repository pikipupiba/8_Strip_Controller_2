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
		else if (i == 8)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_0, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_8).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_8;
		}
		else if (i == 9)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_1, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_9).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_9;
		}
		else if (i == 10)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_2, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_10).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_10;
		}
		else if (i == 11)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_3, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_11).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_11;
		}
		else if (i == 12)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_4, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_12).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_12;
		}
		else if (i == 13)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_5, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_13).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_13;
		}
		else if (i == 14)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_6, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_14).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_14;
		}
		else if (i == 15)
		{
			FastLED.addLeds<LED_TYPE, STRIP_PIN_7, COLOR_ORDER>
				(gLeds, numLedsSoFar, NUM_LEDS_STRIP_15).setCorrection(TypicalLEDStrip);
			numLedsSoFar += NUM_LEDS_STRIP_15;
		}

		//Serial.println(gNumLeds);
		//Serial.println(numLedsSoFar - 1);

		ledSets[i]   = new CRGBSet( gLeds(gNumLeds, numLedsSoFar - 1));

		strips[i] = new LEDStrip( ledSets[i] );

		gNumLeds = numLedsSoFar;
	}

	FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS);

	gLeds.fill_solid(CRGB::Black);

	uPower = true;
	uBrightness = 255;
	uSpeed = 0;
	uHue = 0;
	uHueSpeed = 0;
	uOffset = 0;

	uAutoplay = false;
	uAutoplayTimeout = millis() + 15000;
	uAutoplayDuration = 20000;

	uStrobeTime = 0;
	uStrobe = false;
	uFlash = false;
	uSlow = false;
	uSlowStart = millis();
	uSlowDelay = 30;

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

		// Select the current brightness to display the strip
		if (uStrobe)
		{
			// if strobe is active, link brightness to a beatsin
			uTempBrightness = beatsin16(uStrobeTime,0,uBrightness);
		}
		else if (uFlash)
		{
			// if flash is active, either take brightness all the way up or down, which ever is farther away
			if (uBrightness < 128)
			{
				uTempBrightness = 255;
			}
			else
			{
				uTempBrightness = 0;
			}
		}
		else
		{
			// if no brightness modifiers are active, set to the current brightness value
			uTempBrightness = uBrightness;
		}

	// if the stutter button is being pressed, add a small stutter
	if (uSlow)
	{
		delay(uSlowDelay);
	}

	// Currently we defer to the autoplay built into the app.

	//if (uAutoplay && (millis() > uAutoplayTimeout)) {
		//NextPattern();
		//uAutoplayTimeout = millis() + (uAutoplayDuration);
	//}

	// Update each strip
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->UpdateStrip();
	}

	// If power is on, set brightness to the current brightness
	if (uPower)
	{
		FastLED.setBrightness(uTempBrightness);
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
		// Some patterns cycle palettes, so stop that when the pattern changes
		strips[i]->vars.cyclePalettes = false;

		// Set started to false so the pattern knows to initiate itself
		strips[i]->vars.started = false;
	}

	if (uAutoplay == true)
	{
		// If autoplay is on, mix up some variables about half the time.
		if (random8() < 128)
		{
			uOffset = random8(35);
			float hueFactor = float(random8(50,200)) / 90;
			float speedFactor = float(random8(50, 200)) / 90;

			for (int i = 0; i < NUM_STRIPS; i++)
			{
				strips[i]->vars.positionOffset = i * uOffset;
				strips[i]->vars.hueScaleFactor = hueFactor;
				strips[i]->vars.speedScaleFactor = speedFactor;
			}
		}
		// The other half of the time, use standard values for the variables.
		else 
		{
			uOffset = 0;
			float hueFactor = 1;
			float speedFactor = 1;

			for (int i = 0; i < NUM_STRIPS; i++)
			{
				strips[i]->vars.positionOffset = i * uOffset;
				strips[i]->vars.hueScaleFactor = hueFactor;
				strips[i]->vars.speedScaleFactor = speedFactor;
				strips[i]->vars.speed = 1;
				strips[i]->vars.hueSpeed = 1;
			}
		}

		// Randomly select a pattern
		int patternNum = random8(patternCount);

		Serial.println("Pattern Number : " + String(patternNum));

		for (int i = 0; i < NUM_STRIPS; i++)
		{
			//strips[i]->vars.curPattern = patternNum;
		}

	}
	// If autoplay is off, just go to the next pattern.
	else
	{
		for (int i = 0; i < NUM_STRIPS; i++)
		{

			strips[i]->NextPattern();
		}
	}
}

void Universe::PrevPattern()
{

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		// Same as in NextPattern()
		strips[i]->vars.cyclePalettes = false;
		strips[i]->vars.started = false;
	}

	for (int i = 0; i < NUM_STRIPS; i++)
	{

		strips[i]->PrevPattern();
	}

}

void Universe::SetPattern(int newPatternNum)
{
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		if (strips[i]->vars.curPattern != newPatternNum)
		{
			// Same as in NextPattern()
			strips[i]->vars.cyclePalettes = false;
			strips[i]->vars.started = false;
			strips[i]->SetPattern(newPatternNum);
		}
	}
}

void Universe::ToggleAutoplay()
{

	if (uAutoplay == true )
	{

		uAutoplay = false;

	}
	else
	{
		uAutoplay = true;
	}

		// Jump to the next pattern when you toggle autoplay so there is visual feedback
	NextPattern();
}

// Was going to use this as the UDP interface, but due to time constraints I just made some
// variables public. This will not be the case in the next version.
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

// Select a new hue that's at least 50 away from the current hue.
void Universe::RandomHue()
{
	int newHue = random8();

	while (abs(newHue - strips[0]->vars.hue) < 50)
	{
		newHue = random8();
	}

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->vars.hue = newHue;
	}
}

// Advance the hue by 32.
void Universe::NextHue()
{
	int newHue = strips[0]->vars.hue + 32;

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->vars.hue = newHue;
	}
}

void Universe::SetHue(int newHue)
{
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->vars.hue = newHue;
	}
}

// Used when I only had one button to change the offset.
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

// Used once I had a potentiometer to change the offset.
void Universe::ChangeOffset(int newOffset)
{
	uOffset = newOffset;

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->vars.position = i * uOffset;
		strips[i]->vars.positionOffset = i * uOffset;
	}
}

// Used when I only had one buttone to change the hue factor.
void Universe::ChangeHueFactor()
{
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->vars.hueScaleFactor += 0.2;

		if (strips[i]->vars.hueScaleFactor > 2.5)
		{
			strips[i]->vars.hueScaleFactor = 0;
		}
	}
}

// Used once I had a potentiometer to change the hue factor.
void Universe::ChangeHueFactor(float newHueFactor)
{
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->vars.hueScaleFactor = newHueFactor;
	}
}

// Used when I only had one buttone to change the speed factor.
void Universe::ChangeSpeedFactor()
{
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->vars.speedScaleFactor += 0.2;

		if (strips[i]->vars.speedScaleFactor > 2.5)
		{
			strips[i]->vars.speedScaleFactor = 0;
		}
	}
}

// Used once I had a potentiometer to change the speed factor.
void Universe::ChangeSpeedFactor(float newSpeedFactor)
{
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->vars.speedScaleFactor = newSpeedFactor;
	}
}

void Universe::ChangeReflect()
{
	//startTime("Universe::ChangeReflect()");

	if (strips[0]->vars.reflect)
	{
		for (int i = 0; i < NUM_STRIPS; i++)
		{
			strips[i]->vars.reflect = false;
			strips[i]->vars.numLeds *= 2;
		}
	}
	else
	{
		for (int i = 0; i < NUM_STRIPS; i++)
		{
			strips[i]->vars.reflect = true;
			strips[i]->vars.numLeds /= 2;
		}
	}

	//endTime("Universe::ChangeReflect()");
}

// Used for debugging the Universe!
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

