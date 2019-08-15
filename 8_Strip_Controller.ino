// 8_Strip_Controller.ino is where the controller starts when it first boots up.

// -----------------------------------------------------------------------------------//
// --------------------------------OUTSIDE LIBRARIES----------------------------------//
// -----------------------------------------------------------------------------------//
#include <arduino.h>
#include <FastLED.h>
//#include <ESPAsyncWebServer.h>
//#include <SPIFFS.h>
//#include "FS.h"
#include <EasyButton.h>
#include <WiFi.h>
#include <WiFiUdp.h>


// -----------------------------------------------------------------------------------//
// ----------------------------------Helper Files-------------------------------------//
// -----------------------------------------------------------------------------------//
#include "tasks.h"	// Functions related to interrupts.
//#include "web.h"
#include "debug.h"	// Contains variables and functions for dubugging.

// -----------------------------------------------------------------------------------//
// ---------------------------------PROJECT CLASSES-----------------------------------//
// -----------------------------------------------------------------------------------//
#include "Universe.h"

Universe universe;

// Deprecated because app control is awesome.
//#include "physicalInputs.h"	// Sets up and handles input from physical controls.

#include "webInput.h"


void setup() {

	delay(100);		// 3 second delay for recovery.
	
	Serial.begin(115200);	// Start the Serial Monitor for debugging.

	//setupInputs();	// Initialize physical buttons and knobs.
	setupWeb();		// Initialize UDP input.

	//FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS * NUM_STRIPS);
	//FastLED.setBrightness(gBrightness);

	createTasks();	// Initialize the FastLED show task for ESP32
	
	// Create the universe!
	universe = *Universe::CreateUniverse();

	FastLEDshowESP32();	// Output LED data (should all be off after setup)

	//displayMemory(" after setup");
}

void loop()
{
	//handleInputs();	// Handles input from physical controls.

	handleWeb();		// Handles input from the app.

	universe.Update();	// Calculate the next frame.

	fps(1);			// Show frames per second.

	FastLEDshowESP32();	// Output LED data
	
	// If the error has been detected, restart the controller.
	if (error && millis() > 10000)
	{
		//universe.PrintInfo();
		ESP.restart();
	}
	
	// Modify this delay time based on the number of leds in the fixture
	// to keep it running at about 80 frames per second.
	delay(6);
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
	
	// Catch the error when the framerate drops below 5fps for some reason.
	// Ignore if the stutter button is being used.
	if (framesPerSecond < 30 && !universe.uSlow && millis() - universe.uSlowStart > 2000)
	{
		error = true;
	}
	else
	{
		error = false;
	}
}
