
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
#include "Oscillator.h"	// A custom oscillator class for varying animation variables.
#include "LEDStrip.h"// A strip controller is created for each strip connected to the ESP32.

void setup() {

	delay(3000);			// 3 second delay for recovery

	Serial.begin(115200);	// Start the Serial Monitor for debugging.

	//FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS * NUM_STRIPS);
	//FastLED.setBrightness(gBrightness);

	createTasks();

	displayMemory(" after setup ");
}

void loop()
{
	//debugCounter();
	//handleWeb();	// Handles input from the web server.
	handleInputs();	// Handles input from physical controls.


	//Universe->Update();
	
	FastLEDshowESP32();

}