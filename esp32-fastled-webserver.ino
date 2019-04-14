// Based largely on the ESP32 FastLED webserver example by Jason Coon.
//
// The purpose of this project is to allow my DJ buddy to hook up various NeoPixel Fixtures
// to a single ESP32 and control them via physical buttons and knobs as well as a web page.
//
// He will control it mostly by setting up different presets ahead of time and then calling
// on this program to smoothly vary different parameters in the moment. The web interface will
// be used to create and save the presets and then transition between them during an event.
//
// My first step has been to figure out how to make the program and data structures flexible 
// and robust enough for a lot of different use cases. If you are here to help at this point
// then all I'm asking for is whether or not I'm heading in the right direction with my approach.
// If I am, then tell me what I'm doing right. If I'm not, what strategy would be more effective?
//
// Thank you so much for taking the time to help me with this project! If you would like to
// help in a more consistant capacity or would even consider diving a little deeper for some $$$
// then please reach out!


// -----------------------------------------------------------------------------------//
// --------------------------------OUTSIDE LIBRARIES----------------------------------//
// -----------------------------------------------------------------------------------//
#include <FastLED.h>



// -----------------------------------------------------------------------------------//
// --------------------------------PROJECT LIBRARIES----------------------------------//
// -----------------------------------------------------------------------------------//

#include "tasks.h"			// Functions related to interrupts.
#include "physicalInputs.h"	// Sets up and handles input from physical inputs.
#include "debug.h"	// Contains variables and functions for dubugging.

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

	// Initialize the strips connected to the ESP32.
	// TODO I need to figure out how to adjust this based on settings. Users will probably have to save these values into
	// EEPROM and then restart the ESP32 to apply the new settings. Maybe you select a strip setup in this setup() function
	// either by manually entering strip lengths or selecting a previously saved setup.
	// TODO Figure out how to change these things during execution.


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