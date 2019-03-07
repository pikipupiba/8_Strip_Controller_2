#pragma once

// BRIGHTNESS Potentiometer
const int potPin1 = 36;
// SPEED and HUE of Solid Color Potentiometer
const int potPin2 = 37;
// Blackout Button
const int butPin1 = 39;
// Pattern Change Button
const int butPin2 = 38;

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
			if (power == 0)
			{
				power = 1;
				FastLED.setBrightness(255);
			}
			else
			{
				if (copyStrip == 0) {
					copyStrip = 1;
				}
				else {
					copyStrip = 0;
				}
				power = 0;
			}
			prevPress = millis();
		}

		// Button 2 changes the pattern.
		if (digitalRead(butPin2))
		{
			nextPattern();
			prevPress = millis();
		}
	}

	// Weight the current value heavily against any new values to reduce signal jitter.
	potVal1 = (potVal1 * 4 + 255 - map(analogRead(potPin1), 0, 4096, 0, 255)) / 5;
	potVal2 = (potVal2 * 4 + 255 - map(analogRead(potPin2), 0, 4096, 0, 255)) / 5;

	// Require a change of 2 or more to further reduce jitter.
	if (hueSpeed - potVal1 > 2 || hueSpeed - potVal1 < -2)
	{
		hueSpeed = potVal1;
	}
	if (speed - potVal2 > 2 || speed - potVal2 < -2)
	{
		// TODO Need to normalize speed settings in each animation. This is a quick fix.
		speed = potVal2;

		// If showing a Solid Color the speed dial changes the hue.
		if (patterns[currentPatternIndex].name == "Solid Color")
		{
			solidColor = CHSV(potVal2, 255, 255);
		}
	}
}