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
#include <SSD1306.h> // alias for #include "SSD1306Wire.h"'

// Initialize the OLED display using Wire library
SSD1306  display(0x3c, 4, 15);

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001008)
#warning "Requires FastLED 3.1.8 or later; check github for latest code."
#endif

// Define the WebServer object.
WebServer webServer(80);

// -----------------------------------------------------------------------------------//
// -------------------------------ANIMATION VARIABLES---------------------------------//
// -----------------------------------------------------------------------------------//
// TODO Save and restore these settings from EEPROM.

uint8_t currentPatternIndex = 0; // Index number of which pattern is current

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

uint8_t power = 1;
uint8_t brightness = 8;

// Speed value used by many animations.
// TODO Normalize speed value between the varias animations.
uint8_t speed = 30;

// Number of milliseconds between incrementing gHue.
int hueDelay = 40;

// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100
uint8_t cooling = 50;

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
uint8_t sparking = 120;

CRGB solidColor = CRGB::Blue;

uint8_t autoplay = 0;
uint8_t autoplayDuration = 10;
unsigned long autoPlayTimeout = 0;

uint8_t cyclePalettes = 0;
uint8_t paletteDuration = 10;
uint8_t currentPaletteIndex = 0;
unsigned long paletteTimeout = 0;

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

#define DATA_PIN    12 // pins tested so far on the Feather ESP32: 13, 12, 27, 33, 15, 32, 14, SCL
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_STRIPS 2
#define NUM_LEDS_PER_STRIP 300
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS
CRGB leds[NUM_LEDS];

#define MILLI_AMPS         60000 // IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)
#define FRAMES_PER_SECOND  120

// -- The core to run FastLED.show()
#define FASTLED_SHOW_CORE 1

// WiFi Status led.
// TODO No longer needed. REMOVE IT! Maybe?
const int boardLedPin = 2;
// BRIGHTNESS Potentiometer
const int potPin1 = 36;
// SPEED and HUE of Solid Color Potentiometer
const int potPin2 = 37;
// Blackout Button
const int butPin1 = 39;
// Pattern Change Button
const int butPin2 = 38;

#include "patterns.h"

#include "field.h"
#include "fields.h"

#include "secrets.h"
#include "wifi_changed.h"
#include "web.h"


// wifi ssid and password should be added to a file in the sketch named secrets.h
// the secrets.h file should be added to the .gitignore file and never committed or
// pushed to public source control (GitHub).
// const char* ssid = "........";
// const char* password = "........";

// -- Task handles for use in the notifications
static TaskHandle_t FastLEDshowTaskHandle = 0;
static TaskHandle_t userTaskHandle = 0;

/** show() for ESP32
	Call this function instead of FastLED.show(). It signals core 0 to issue a show,
	then waits for a notification that it is done.
*/
void FastLEDshowESP32()
{
	if (userTaskHandle == 0) {
		// -- Store the handle of the current task, so that the show task can
		//    notify it when it's done
		userTaskHandle = xTaskGetCurrentTaskHandle();

		// -- Trigger the show task
		xTaskNotifyGive(FastLEDshowTaskHandle);

		// -- Wait to be notified that it's done
		const TickType_t xMaxBlockTime = pdMS_TO_TICKS(200);
		ulTaskNotifyTake(pdTRUE, xMaxBlockTime);
		userTaskHandle = 0;
	}
}

/** show Task
	This function runs on core 0 and just waits for requests to call FastLED.show()
*/
void FastLEDshowTask(void *pvParameters)
{
	// -- Run forever...
	for (;;) {
		// -- Wait for the trigger
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		// -- Do the show (synchronously)
		FastLED.show();

		// -- Notify the calling task
		xTaskNotifyGive(userTaskHandle);
	}
}

void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {

	Serial.printf("Listing directory: %s\n", dirname);

	File root = fs.open(dirname);
	if (!root) {
		Serial.println("Failed to open directory");
		return;
	}
	if (!root.isDirectory()) {
		Serial.println("Not a directory");
		return;
	}

	File file = root.openNextFile();
	while (file) {
		if (file.isDirectory()) {
			Serial.print("  DIR : ");
			Serial.println(file.name());
			if (levels) {
				listDir(fs, file.name(), levels - 1);
			}
		}
		else {
			Serial.print("  FILE: ");
			Serial.print(file.name());
			Serial.print("  SIZE: ");
			Serial.println(file.size());
		}
		file = root.openNextFile();
	}
}

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

	// three-wire LEDs (WS2811, WS2812, NeoPixel)
	//FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

	// four-wire LEDs (APA102, DotStar)
	//FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

	// Parallel output: 13, 12, 27, 33, 15, 32, 14, SCL.0

	FastLED.addLeds<LED_TYPE, 13, COLOR_ORDER>(leds, 0, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	FastLED.addLeds<LED_TYPE, 12, COLOR_ORDER>(leds, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	//FastLED.addLeds<LED_TYPE, 27, COLOR_ORDER>(leds, 2 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	//FastLED.addLeds<LED_TYPE, 33, COLOR_ORDER>(leds, 3 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	//FastLED.addLeds<LED_TYPE, 15, COLOR_ORDER>(leds, 4 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	//FastLED.addLeds<LED_TYPE, 32, COLOR_ORDER>(leds, 5 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	//FastLED.addLeds<LED_TYPE, 14, COLOR_ORDER>(leds, 6 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	//FastLED.addLeds<LED_TYPE, SCL, COLOR_ORDER>(leds, 7 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);

	FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS);

	// set master brightness control
	FastLED.setBrightness(brightness);

	// Print the core the main code is running on.
	// Make sure to change FASTLED_SHOW_CORE if it is the same as this one.
	int core = xPortGetCoreID();
	Serial.print("Main code running on core ");
	Serial.println(core);

	// -- Create the FastLED show task
	xTaskCreatePinnedToCore(FastLEDshowTask, "FastLEDshowTask", 2048, NULL, 2, &FastLEDshowTaskHandle, FASTLED_SHOW_CORE);

	// Update the Timeout variables after the setup code has completed.
	autoPlayTimeout = millis() + (autoplayDuration * 1000);
	paletteTimeout = millis() + (paletteDuration * 1000);
}

void loop()
{
	handleWeb();

	handleButtons();

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

		EVERY_N_MILLISECONDS(hueDelay) {
			// slowly blend the current palette to the next
			nblendPaletteTowardPalette(currentPalette, targetPalette, 8);
			gHue++;  // slowly cycle the "base color" through the rainbow
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
	 for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
	   leds[NUM_LEDS_PER_STRIP + i] = leds[i];
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

// Draws the menu onto the OLED display.
// TODO Implement a more rigourous menu structure that uses a rotary encoder for navigation.
// TODO Come up with some icons to easily communicate certain information.
void drawMenu()
{
	// Clear the display for updating.
	display.clear();

	// ALONG THE TOP or ALONG THE RIGHT.
	// TODO Implement a status bar.

	// TOP LEFT CORNER
	// Display the current state.
	display.drawString(2, 2, "Pattern: " + patterns[currentPatternIndex].name);
	display.drawString(2, 12, "Palette: " + paletteNames[currentPaletteIndex]);
	display.drawString(2, 22, "Brightness: " + String(brightness));
	display.drawString(2, 32, "Speed: " + String(speed));

	// BOTTOM LEFT CORNER
	// Diaplay the current IP Address to control via WiFi.
	// TODO Switch between IP Address and the host network SSID every few seconds.
	// TODO Display "Manual Control Only!" if no connection has been made.
	display.drawString(2, 50, "IP: " + WiFi.localIP().toString());

	// BOTTOM RIGHT CORNER
	// Display the current power state of the lights.
	if (power == 0)
	{
		display.drawString(100, 50, "OFF");
	}
	else
	{
		display.drawString(100, 50, "ON");
	}

	display.display();
}

// Handle any and all physical buttons on the package.

// TODO Inputs on the final package will be as follows:
// Potentiometer 1 will control BRIGHTNESS.
// Potentiometer 2 will control SPEED as well as HUE of a solid color.
// Button 1 will turn the strip off.
// Button 2 will toggle HOLD and SET modes. SET changes things immediately and HOLD will wait until returning to SET.
// The ROTARY ENCODER will navigate the menu and make changes to settings.
void handleButtons()
{
	static long prevPress = 0;
	static int potVal1 = 0;
	static int potVal2 = 0;
	
	// Time between button repeats.
	static int buttonTime = 200;

	// Read button inputs if past the minimum repeat time.
	if (millis() - prevPress > buttonTime)
	{
		// Button 1 controls power.
		if (digitalRead(butPin1))
		{
			if (power == 0)
			{
				power = 1;
			}
			else
			{
				power = 0;
			}
			prevPress = millis();
		}

		// Button 2 changes the pattern.
		if (digitalRead(butPin2))
		{
			nextPattern();
			prevPress = millis();
		}
	}

	// Weight the current value heavily against any new values to reduce signal jitter.
	potVal1 = (potVal1 * 4 + 255 - map(analogRead(potPin1), 0, 4096, 0, 255))/5;
	potVal2 = (potVal2 * 4 + 255 - map(analogRead(potPin2), 0, 4096, 0, 255))/5;

	// Require a change of 2 or more to further reduce jitter.
	if (brightness - potVal1 > 2 || brightness - potVal1 < -2)
	{
		brightness = potVal1;
		FastLED.setBrightness(brightness);
	}
	if (speed*5 - potVal2 > 2 || speed*5 - potVal2 < -2)
	{
		// TODO Need to normalize speed settings in each animation. This is a quick fix.
		speed = potVal2/5;
		
		// If showing a Solid Color the speed dial changes the hue.
		if (patterns[currentPatternIndex].name == "Solid Color")
		{
			solidColor = CHSV(potVal2,255,255);
		}
	}
}