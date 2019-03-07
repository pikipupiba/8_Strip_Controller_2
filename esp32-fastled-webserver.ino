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

// Define the WebServer object.
WebServer webServer(80);

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001008)
#warning "Requires FastLED 3.1.8 or later; check github for latest code."
#endif

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

// -----------------------------------------------------------------------------------//
// -------------------------------ANIMATION VARIABLES---------------------------------//
// -----------------------------------------------------------------------------------//
// TODO Save and restore these settings from EEPROM.

uint8_t gHue = 0; // rotating "base color" used by many of the patterns


// WiFi Status led.
// TODO No longer needed. REMOVE IT! Maybe?
const int boardLedPin = 2;

#include "tasks.h"

#include "patterns.h"
#include "palettes.h"

#include "field.h"
#include "fields.h"

#include "secrets.h"
#include "wifi_changed.h"
#include "web.h"
#include "physicalInputs.h"
#include "builtInDisplay.h"

#include "StripController.h"

// Create array of strips available to the program.
StripController* strip[8];


void setup() {

	delay(3000); // 3 second delay for recovery

	// Start the Serial Monitor for debugging.
	Serial.begin(115200);

	// Set the Button Pins for INPUT.
	pinMode(butPin1, INPUT);
	pinMode(butPin2, INPUT);

	// Set the LED on the board for OUTPUT and turn it on.
	pinMode(boardLedPin, OUTPUT);
	digitalWrite(boardLedPin, 1);

	// Get the display running.
	// TODO Learn more about the display library.
	pinMode(16, OUTPUT);
	digitalWrite(16, LOW); // set GPIO16 low to reset OLED
	delay(50);
	digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high

	display.init();
	display.flipScreenVertically();
	display.setColor(WHITE);
	display.setTextAlignment(TEXT_ALIGN_LEFT);

	// TODO Figure out what other fonts are available and choose one.
	display.setFont(ArialMT_Plain_10);

	display.clear();
	display.drawString(2, 20, String("Connecting to Wi-Fi"));

	display.display();
	
	// Starts the SPIFFS? and list the contents.
	// TODO Learn about SPIFFS
	SPIFFS.begin();
	listDir(SPIFFS, "/", 1);

	// TODO Learn how to save and read settings to EEPROM and then implement!
	//loadFieldsFromEEPROM(fields, fieldCount);

	setupWifi();
	setupWeb();

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strip[i] = new StripController(i, NUM_LEDS_PER_STRIP, Strip);
	}

	FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS * NUM_STRIPS);

	// set master brightness control
	FastLED.setBrightness(masterBrightness);

	createTasks();

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strip[i]->resetTimeouts();
	}
}

void loop()
{
	handleWeb();
	handleInputs();
	drawMenu();

	if (masterPower)
	{
		FastLED.setBrightness(masterBrightness);
	}
	else
	{
		FastLED.setBrightness(0);
	}

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strip[i]->updateStrip();
	}
	// send the 'leds' array out to the actual LED strip
	// FastLED.show();
	FastLEDshowESP32();

	// insert a delay to keep the framerate modest.
	// TODO Learn more about why the FastLED.delay() doesn't work and if it can be used, use it.
	// FastLED.delay(1000 / FRAMES_PER_SECOND);
	delay(1000 / FRAMES_PER_SECOND);
}