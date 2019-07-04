
// -----------------------------------------------------------------------------------//
// --------------------------------OUTSIDE LIBRARIES----------------------------------//
// -----------------------------------------------------------------------------------//
#include <arduino.h>
#include <FastLED.h>
//#include <WiFi.h>
//#include <ESPAsyncWebServer.h>
//#include <SPIFFS.h>
//#include "FS.h"
#include <EasyButton.h>
#include <WiFi.h>
#include <WiFiUdp.h>


// -----------------------------------------------------------------------------------//
// --------------------------------PROJECT LIBRARIES----------------------------------//
// -----------------------------------------------------------------------------------//
#include "tasks.h"			// Functions related to interrupts.
//#include "web.h"
#include "debug.h"			// Contains variables and functions for dubugging.

// -----------------------------------------------------------------------------------//
// ---------------------------------PROJECT CLASSES-----------------------------------//
// -----------------------------------------------------------------------------------//
#include "Universe.h"

Universe universe;

//#include "physicalInputs.h"	// Sets up and handles input from physical controls.

#include "webInput.h"


void setup() {

	delay(3000);			// 3 second delay for recovery.

	Serial.begin(115200);	// Start the Serial Monitor for debugging.

	//setupInputs();			// Initialize physical buttons and knobs.
	setupWeb();

	//FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS * NUM_STRIPS);
	//FastLED.setBrightness(gBrightness);

	createTasks();

	universe = *Universe::CreateUniverse();	// Somebody told me I should initialize my object this way. Not quite sure why.

	FastLEDshowESP32();

	//displayMemory(" after setup");
}

void loop()
{
	//handleInputs();	// Handles input from physical controls.
	D(startTime("Loop");)
	handleWeb();

	D(middleTime("Loop");)
	universe.Update();

	D(endTime("Loop");)
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
