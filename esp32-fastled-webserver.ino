#include "stdafx.h"


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

// Define the WebServer object.
WebServer webServer(80);

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001008)
#warning "Requires FastLED 3.1.8 or later; check github for latest code."
#endif


// WiFi Status led.
// TODO No longer needed. REMOVE IT! Maybe?
const int boardLedPin = 2;

// -----------------------------------------------------------------------------------//
// --------------------------------PROJECT LIBRARIES----------------------------------//
// -----------------------------------------------------------------------------------//

#include "tasks.h"			// Functions related to interrupts.

#include "globalStuff.h"
#include "normalizeValues.h"// Contains the functions to compress signed and unsigned ints to more precise smaller ranges.

#include "animationPresets.h"	// The location of presets used when initializing animation objects.
#include "stripPresets.h"	// The location of presets for entire strips which can include multiple animation presets.
#include "universePresets.h"// The location of presets for a collection of strips.

#include "patterns.h"		// Patterns use various animation objects to create an effect.
//#include "palettes.h"		// Palettes define specific selections of colors to be used by animations.

#include "field.h"			// Gets field values from the web server.
#include "fields.h"			// Causes field values to affect program.

#include "secrets.h"		// Contains information about WiFi networks the ESP32 should try to connect for web control.
#include "wifi_changed.h"	// 
#include "web.h"			// Sets up the web server and handles web input.
#include "physicalInputs.h"	// Sets up and handles input from physical inputs.
#include "display.h"	// Handles setting up and displaying to the built in display and serial output.

// -----------------------------------------------------------------------------------//
// ---------------------------------PROJECT CLASSES-----------------------------------//
// -----------------------------------------------------------------------------------//

#include "Oscillators.h"	// A custom oscillator class for varying animation variables.
#include "Animations.h"		// An interface class from which individual animations can inherit their base functionality.
#include "Mover.h"
#include "StripController.h"// A strip controller is created for each strip connected to the ESP32.

StripController* strips[8];

void setup() {

	delay(3000);			// 3 second delay for recovery

	Serial.begin(115200);	// Start the Serial Monitor for debugging.

	//setupInputs();			// Setup the physical inputs.

	setupDisplay();			// Setup the built in display.
	
	// Start the SPIFFS? (whatever that means) and list the contents.
	// TODO Learn about SPIFFS
	//SPIFFS.begin();
	//listDir(SPIFFS, "/", 1);

	// TODO Learn how to save and read settings to EEPROM and then implement!
	//loadFieldsFromEEPROM(fields, fieldCount);
	// TODO Might actually need to save and restore from an SD card depending on implementation of presets.

	//setupWifi();			// Try to connect to WiFi networks specified in secrets.h
	//setupWeb();			// Put the contents of the SPIFFS onto the web server.

	// Initialize the strips connected to the ESP32.
	// TODO I need to figure out how to adjust this based on settings. Users will probably have to save these values into
	// EEPROM and then restart the ESP32 to apply the new settings. Maybe you select a strip setup in this setup() function
	// either by manually entering strip lengths or selecting a previously saved setup.
	// TODO Figure out how to change these things during execution.
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i] = new StripController(i, NUM_LEDS_PER_STRIP);// , Strip);
	}

	FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS * NUM_STRIPS);

	// set master brightness control
	FastLED.setBrightness(gBrightness);

	createTasks();
	
	displayMemory(" after setup ");

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->ResetTimeouts();
	}

	patterns[currentPatternIndex](strips[0]);

	lastFrameTime = millis();

}

void loop()
{
	//debugCounter();
	//handleWeb();	// Handles input from the web server.
	handleInputs();	// Handles input from physical controls.

	drawMenu();		// Displays menu on the built in display.

	if (gPower)
	{
		FastLED.setBrightness(gBrightness);
	}
	else
	{
		FastLED.setBrightness(0);
	}

	// Update each strip.
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i]->UpdateStrip();
	}
	
	EVERY_N_MILLIS(5000)
	{
		
		/*for (int i = 0; i < NUM_STRIPS; i++)
		{
			for (int j = 0; j < strips[i]->numAnimations; j++)
			{
				if (random8() < 255) { strips[i]->animation[j]->Randomize(); }
			}
			strips[i]->AddAnimation();
		}*/
		
		displayMemory(" after more Movers");
		//calcFPS();
	}

	EVERY_N_SECONDS(20)
	{
		nextPattern();
		patterns[currentPatternIndex](strips[0]);
	}

	// send the 'leds' array out to the actual LED strip
	// FastLED.show();
	FastLEDshowESP32();

	newFrames++;
	calcFPS();

	// Removed the delay because it was cutting my framerate in half at the lowest setting.
	// TODO Learn more about why the FastLED.delay() doesn't work and if it can be used, use it.
	// FastLED.delay(1000 / FRAMES_PER_SECOND);
	//delay(1000 / FRAMES_PER_SECOND);

}

void nextPattern()
{
	currentPatternIndex = (currentPatternIndex + 1) % ARRAY_SIZE(patterns);
}