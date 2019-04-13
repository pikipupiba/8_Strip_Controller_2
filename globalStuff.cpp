#include "stdafx.h"

#pragma once
#include "globalStuff.h"

CRGBArray<NUM_LEDS> leds;

// Set the global variables to their starting values.
float gHue = 0;
float gHueSpeed = 1;

bool gPower = true;

float gBrightness = 128;

int gSpeed = 0;

// Set the variables for tracking frames per second to their starting values.
float frameTime = 1;
unsigned long lastFrameTime = 1;
int newFrames = 1;
float FPS = 0;
float speedScaleFactor = 1;

unsigned long sTime = 0;
String functionName = "";

int numObjects = 0;
int numOscillators = 0;

int debugDepth = 0;

// Supporting general function -------------------------------------------------------------------------------------------

void showfps() {                                                                // Show rames per seocond on the serial monitor.

// Temporary local variable  
	uint32_t currentMillis;

	// Persistent local variable  
	static uint32_t lastMillis = 0;

	currentMillis = millis();
	loops++;                                                                      // Keep on incrementing this each time it's called until (currentMillis - lastMillis) > 1000

	if (currentMillis - lastMillis > 1000) {                                        // If 1 second has passed, then. . 
		Serial.println(loops);                                                      // Print the value of loops (which is loops per second).
		lastMillis = currentMillis;                                                 // Reset everything and start counting all over again. By Andrew Tuline.
		loops = 0;
	}

} // showfps()



// Supporting visual functions ----------------------------------------------------------------------------------------------

void lineit() {                                                                 // Send the pixels one or the other direction down the line.

	if (thisdir == 0) {
		for (int i = NUM_LEDS - 1; i > 0; i--) leds[i] = leds[i - 1];
	}
	else {
		for (int i = 0; i < NUM_LEDS - 1; i++) leds[i] = leds[i + 1];
	}

} // waveit()



void waveit() {                                                                 // Shifting pixels from the center to the left and right.

	for (int i = NUM_LEDS - 1; i > NUM_LEDS / 2; i--) {                             // Move to the right.
		leds[i] = leds[i - 1];
	}

	for (int i = 0; i < NUM_LEDS / 2; i++) {                                        // Move to the left.
		leds[i] = leds[i + 1];
	}

} // waveit()



void addGlitter(fract8 chanceOfGlitter) {                                      // Let's add some glitter, thanks to Mark

	if (random8() < chanceOfGlitter) {
		leds[random16(NUM_LEDS)] += CRGB::White;
	}

} // addGlitter()
