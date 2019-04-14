
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

	displayMemory(" after setup");
}

void loop()
{
	handleInputs();	// Handles input from physical controls.

	universe.Update();
	
	FastLEDshowESP32();
}