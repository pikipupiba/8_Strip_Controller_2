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


#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001008)
#warning "Requires FastLED 3.1.8 or later; check github for latest code."
#endif

// Define the WebServer object.
WebServer webServer(80);

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

// -- The core to run FastLED.show()
#define FASTLED_SHOW_CORE 1

// WiFi Status led.
// TODO No longer needed. REMOVE IT! Maybe?
const int boardLedPin = 2;

#include "tasks.h"
#include "stripSettings.h"

#include "patterns.h"

#include "field.h"
#include "fields.h"

#include "secrets.h"
#include "wifi_changed.h"
#include "web.h"
#include "physicalInputs.h"
#include "builtInDisplay.h"


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
	setupStrips();
	createTasks();

	// Update the Timeout variables after the setup code has completed.
	autoPlayTimeout = millis() + (autoplayDuration * 1000);
	paletteTimeout = millis() + (paletteDuration * 1000);
}

void loop()
{
	handleWeb();
	handleInputs();
	drawMenu();

	if (power == 0) {

		// Make all LEDS black if the power is off.
		//fill_solid(leds, NUM_LEDS, CRGB::Black);

		// NEW METHOD Turn the brightness all the way down so that the state of the strip is saved.
		FastLED.setBrightness(0);
	}

	// Removing the ELSE so the patterns keep running even if they are off.
	// This will hopefully allow smoother transitions between on and off.
	// TODO Remove all evidence once its behavior is confirmed.
	// else {

		// Call the current pattern function once, updating the 'leds' array
		patterns[currentPatternIndex].pattern();

		EVERY_N_MILLISECONDS(10) {
			// slowly blend the current palette to the next
			nblendPaletteTowardPalette(currentPalette, targetPalette, 8);
			gHue += hueSpeed/10;  // slowly cycle the "base color" through the rainbow
		}

		// Advance the pattern and palette if applicable.
		// TODO Should this only happen if POWER is on?
		if (autoplay == 1 && (millis() > autoPlayTimeout)) {
			nextPattern();
			autoPlayTimeout = millis() + (autoplayDuration * 1000);
		}

		if (cyclePalettes == 1 && (millis() > paletteTimeout)) {
			nextPalette();
			paletteTimeout = millis() + (paletteDuration * 1000);
		}
	//} // This is the other bracket of the removed ELSE.

	// Copy the first strip to the second strip.
	// TODO Immplement a mode that duplicates strips or lets eeach do its own thing.
		if (copyStrip == 1) {
			for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
				leds[NUM_LEDS_PER_STRIP + i] = leds[i];
			}
		}

	// send the 'leds' array out to the actual LED strip
	// FastLED.show();
	FastLEDshowESP32();

	// insert a delay to keep the framerate modest.
	// TODO Learn more about why the FastLED.delay() doesn't work and if it can be used, use it.
	// FastLED.delay(1000 / FRAMES_PER_SECOND);
	delay(1000 / FRAMES_PER_SECOND);
}

void nextPattern()
{
	// add one to the current pattern number and wrap around at the end
	currentPatternIndex = (currentPatternIndex + 1) % patternCount;
}

void nextPalette()
{
	// add one to the current palette number and wrap around at the end
	currentPaletteIndex = (currentPaletteIndex + 1) % paletteCount;
	targetPalette = palettes[currentPaletteIndex];
}