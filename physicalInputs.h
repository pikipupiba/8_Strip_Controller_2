#include "stdafx.h"

#pragma once

// BRIGHTNESS Potentiometer
const int potPin1 = 36;
// SPEED and HUE of Solid Color Potentiometer
const int potPin2 = 37;
// Blackout Button
const int butPin1 = 39;
// Pattern Change Button
const int butPin2 = 38;

void setupInputs()
{
	// Set the Button Pins for INPUT.
	pinMode(butPin1, INPUT);
	pinMode(butPin2, INPUT);

	// Set the LED on the board for OUTPUT and turn it on.
	pinMode(boardLedPin, OUTPUT);
	digitalWrite(boardLedPin, 1);
}

// Handle any and all physical buttons on the package.

// TODO Inputs on the final package will be as follows:
// Potentiometer 1 will control BRIGHTNESS.
// Potentiometer 2 will control SPEED as well as HUE of a solid color.
// Button 1 will turn the strip off.
// Button 2 will toggle HOLD and SET modes. SET changes things immediately and HOLD will wait until returning to SET.
// The ROTARY ENCODER will navigate the menu and make changes to settings.

void handleInputs()
{
	static long prevPress = 0;
	static int potVal1 = 0;
	static int potVal2 = 0;

	// Time between button repeats.
	static int buttonTime = 200;

	// Read button inputs if past the minimum repeat time.
	if (millis() - prevPress > buttonTime)
	{
		// Button 1 controls power.
		if (digitalRead(butPin1))
		{
			gPower = !gPower;
			FastLED.setBrightness(255);
			
			prevPress = millis();
		}

		// Button 2 changes the pattern.
		if (digitalRead(butPin2))
		{
			//strip[0]->nextPattern();
			prevPress = millis();
		}
	}

	// Weight the current value heavily against any new values to reduce signal jitter.
	potVal1 = (potVal1 * 4 + 255 - map(analogRead(potPin1), 0, 4096, 0, 255)) / 5;
	potVal2 = (potVal2 * 4 + 255 - map(analogRead(potPin2), 0, 4096, 0, 255)) / 5;

	// Require a change of 2 or more to further reduce jitter.
	if (gHueSpeed - potVal1 > 2 || gHueSpeed - potVal1 < -2)
	{
		gHueSpeed = potVal1;
	}
	if (gSpeed - potVal2 > 2 || gSpeed - potVal2 < -2)
	{
		// TODO Need to normalize speed settings in each animation. This is a quick fix.
		gSpeed = potVal2;

		// If showing a Solid Color the speed dial changes the hue.
		/*if (patterns[curPattern].name == "Solid Color")
		{
			solidColor = CHSV(potVal2, 255, 255);
		}*/
	}
}