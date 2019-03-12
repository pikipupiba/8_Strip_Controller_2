/*
   ESP32 FastLED WebServer: https://github.com/jasoncoon/esp32-fastled-webserver
   Copyright (C) 2017 Jason Coon

   Built upon the amazing FastLED work of Daniel Garcia and Mark Kriegsman:
   https://github.com/FastLED/FastLED

   ESP32 support provided by the hard work of Sam Guyer:
   https://github.com/samguyer/FastLED

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// -----------------------------------------------------------------------------------//
// --------------------------------OUTSIDE LIBRARIES----------------------------------//
// -----------------------------------------------------------------------------------//
#include <FastLED.h>
#include <WebServer.h>
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#include <EEPROM.h>
#include <MemoryFree.h>

// Define the WebServer object.
WebServer webServer(80);

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001008)
#warning "Requires FastLED 3.1.8 or later; check github for latest code."
#endif

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

// -----------------------------------------------------------------------------------//
// ----------------------------GLOBAL ANIMATION VARIABLES-----------------------------//
// -----------------------------------------------------------------------------------//
// TODO Save and restore these settings from EEPROM.

uint8_t gHue = 0; // rotating "base color" used by many of the patterns


// WiFi Status led.
// TODO No longer needed. REMOVE IT! Maybe?
const int boardLedPin = 2;

// -----------------------------------------------------------------------------------//
// --------------------------------PROJECT LIBRARIES----------------------------------//
// -----------------------------------------------------------------------------------//

#include "tasks.h"			// Functions related to interrupts.

#include "defaultSettings.h"// Contains all default settings to use if no saved settings are available.
#include "normalizeValues.h"// Contains the functions to compress signed and unsigned ints to more precise smaller ranges.

#include "animationPresets.h"	// The location of presets used when initializing animation objects.
#include "stripPresets.h"	// The location of presets for entire strips which can include multiple animation presets.
#include "universePresets.h"// The location of presets for a collection of strips.

#include "patterns.h"		// Patterns use various animation objects to create an effect.
#include "palettes.h"		// Palettes define specific selections of colors to be used by animations.

#include "field.h"			// Gets field values from the web server.
#include "fields.h"			// Causes field values to affect program.

#include "secrets.h"		// Contains information about WiFi networks the ESP32 should try to connect for web control.
#include "wifi_changed.h"	// 
#include "web.h"			// Sets up the web server and handles web input.
#include "physicalInputs.h"	// Sets up and handles input from physical inputs.
#include "builtInDisplay.h"	// Handles setting up and displaying to the built in display.

// -----------------------------------------------------------------------------------//
// ---------------------------------PROJECT CLASSES-----------------------------------//
// -----------------------------------------------------------------------------------//

#include "Oscillators.h"	// A custom oscillator class for varying animation variables.
#include "StripController.h"// A strip controller is created for each strip connected to the ESP32.
#include "Animations.h"		// An interface class from which individual animations can inherit their base functionality.


// Create array of strips available to the program.
StripController* strip[8];


void setup() {

	delay(3000);			// 3 second delay for recovery

	Serial.begin(115200);	// Start the Serial Monitor for debugging.

	setupInputs();			// Setup the physical inputs.

	setupDisplay();			// Setup the built in display.
	
	// Start the SPIFFS? (whatever that means) and list the contents.
	// TODO Learn about SPIFFS
	SPIFFS.begin();
	listDir(SPIFFS, "/", 1);

	// TODO Learn how to save and read settings to EEPROM and then implement!
	//loadFieldsFromEEPROM(fields, fieldCount);
	// TODO Might actually need to save and restore from an SD card depending on implementation of presets.

	setupWifi();			// Try to connect to WiFi networks specified in secrets.h
	setupWeb();				// Put the contents of the SPIFFS onto the web server.

	// Initialize the strips connected to the ESP32.
	// TODO I need to figure out how to adjust this based on settings. Users will probably have to save these values into
	// EEPROM and then restart the ESP32 to apply the new settings. Maybe you select a strip setup in this setup() function
	// either by manually entering strip lengths or selecting a previously saved setup.
	// TODO Figure out how to change these things during execution.
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strip[i] = new StripController(i, NUM_LEDS_PER_STRIP, Strip);
	}

	FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS * NUM_STRIPS);

	// set master brightness control
	FastLED.setBrightness(masterBrightness);

	createTasks();
	
	displayMemory("after setup");

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strip[i]->ResetTimeouts();
	}

}

void loop()
{
	handleWeb();	// Handles input from the web server.
	handleInputs();	// Handles input from physical controls.
	drawMenu();		// Displays menu on the built in display.

	if (masterPower)
	{
		FastLED.setBrightness(masterBrightness);
	}
	else
	{
		FastLED.setBrightness(0);
	}

	// Update each strip.
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strip[i]->UpdateStrip();
	}

	// send the 'leds' array out to the actual LED strip
	// FastLED.show();
	FastLEDshowESP32();

	// insert a delay to keep the framerate modest.
	// TODO Learn more about why the FastLED.delay() doesn't work and if it can be used, use it.
	// FastLED.delay(1000 / FRAMES_PER_SECOND);
	delay(1000 / FRAMES_PER_SECOND);
}