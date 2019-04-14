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

}