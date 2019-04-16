
// -----------------------------------------------------------------------------------//
// --------------------------------OUTSIDE LIBRARIES----------------------------------//
// -----------------------------------------------------------------------------------//
#include <arduino.h>
#include <FastLED.h>

// -----------------------------------------------------------------------------------//
// --------------------------------PROJECT LIBRARIES----------------------------------//
// -----------------------------------------------------------------------------------//
#include "tasks.h"			// Functions related to interrupts.
#include "physicalInputs.h"	// Sets up and handles input from physical controls.
#include "debug.h"			// Contains variables and functions for dubugging.

// -----------------------------------------------------------------------------------//
// ---------------------------------PROJECT CLASSES-----------------------------------//
// -----------------------------------------------------------------------------------//
#include "Universe.h"

Universe universe;

void setup() {

	delay(3000);			// 3 second delay for recovery

	Serial.begin(115200);	// Start the Serial Monitor for debugging.

	//FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS * NUM_STRIPS);
	//FastLED.setBrightness(gBrightness);

	createTasks();

	universe = *Universe::CreateUniverse();

	FastLEDshowESP32();

	displayMemory(" after setup");
}

void loop()
{
	//handleInputs();	// Handles input from physical controls.

	universe.Update();

	//showfps();
	fps(1);

	FastLEDshowESP32();

	//delay(20);
}


static inline void fps(const int seconds) {
	// Create static variables so that the code and variables can
	// all be declared inside a function
	static unsigned long lastMillis;
	static unsigned long frameCount;
	static unsigned int framesPerSecond;

	// It is best if we declare millis() only once
	unsigned long now = millis();
	frameCount++;
	if (now - lastMillis >= seconds * 1000) {
		framesPerSecond = frameCount / seconds;
		Serial.println(framesPerSecond);
		frameCount = 0;
		lastMillis = now;
	}
}