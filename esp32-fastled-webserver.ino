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
//#define FASTLED_ALLOW_INTERRUPTS 0
#include <HTTP_Method.h>
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

WebServer webServer(80);


const int led = 2;

uint8_t autoplay = 0;
uint8_t autoplayDuration = 10;
unsigned long autoPlayTimeout = 0;

uint8_t currentPatternIndex = 0; // Index number of which pattern is current

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

uint8_t power = 1;
uint8_t brightness = 8;

uint8_t speed = 30;

// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100
uint8_t cooling = 50;

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
uint8_t sparking = 120;

CRGB solidColor = CRGB::Blue;

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

int potPin1 = 36;
int potPin2 = 37;
int butPin1 = 39;
int butPin2 = 38;

void setup() {

	delay(3000); // 3 second delay for recovery

	pinMode(butPin1, INPUT);
	pinMode(butPin2, INPUT);

	// Get the display running.
	pinMode(16, OUTPUT);
	digitalWrite(16, LOW); // set GPIO16 low to reset OLED
	delay(50);
	digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high

	display.init();
	display.flipScreenVertically();
	display.setColor(WHITE);
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	display.setFont(ArialMT_Plain_10);

	pinMode(led, OUTPUT);
	digitalWrite(led, 1);

	Serial.begin(115200);

	display.clear();
	display.drawString(2, 20, String("Connecting to Wi-Fi"));

	display.display();

	SPIFFS.begin();
	listDir(SPIFFS, "/", 1);

	//  loadFieldsFromEEPROM(fields, fieldCount);

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

	int core = xPortGetCoreID();
	Serial.print("Main code running on core ");
	Serial.println(core);

	// -- Create the FastLED show task
	xTaskCreatePinnedToCore(FastLEDshowTask, "FastLEDshowTask", 2048, NULL, 2, &FastLEDshowTaskHandle, FASTLED_SHOW_CORE);

	autoPlayTimeout = millis() + (autoplayDuration * 1000);


	Serial.print("Server IP: ");
	Serial.println(WiFi.localIP().toString());
	Serial.println("\n\n");

	drawMenu();
}

void loop()
{
	handleWeb();

	handleButtons();

	drawMenu();


	if (power == 0) {
		fill_solid(leds, NUM_LEDS, CRGB::Black);
	}
	else {
		// Call the current pattern function once, updating the 'leds' array
		patterns[currentPatternIndex].pattern();

		EVERY_N_MILLISECONDS(40) {
			// slowly blend the current palette to the next
			nblendPaletteTowardPalette(currentPalette, targetPalette, 8);
			gHue++;  // slowly cycle the "base color" through the rainbow
		}

		if (autoplay == 1 && (millis() > autoPlayTimeout)) {
			nextPattern();
			autoPlayTimeout = millis() + (autoplayDuration * 1000);
		}

		if (cyclePalettes == 1 && (millis() > paletteTimeout)) {
			nextPalette();
			paletteTimeout = millis() + (paletteDuration * 1000);
		}
	}

	// Copy the first strip to the second strip
	 for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
	   leds[NUM_LEDS_PER_STRIP + i] = leds[i];
	 }

	// send the 'leds' array out to the actual LED strip
	FastLEDshowESP32();

	// FastLED.show();
	// insert a delay to keep the framerate modest
	// FastLED.delay(1000 / FRAMES_PER_SECOND);
	delay(1000 / FRAMES_PER_SECOND);
}

void nextPattern()
{
	// add one to the current pattern number, and wrap around at the end
	currentPatternIndex = (currentPatternIndex + 1) % patternCount;
}

void nextPalette()
{
	currentPaletteIndex = (currentPaletteIndex + 1) % paletteCount;
	targetPalette = palettes[currentPaletteIndex];
}

void drawMenu()
{
	display.clear();
	display.drawString(2, 2, "Pattern: " + patterns[currentPatternIndex].name);
	display.drawString(2, 12, "Palette: " + paletteNames[currentPaletteIndex]);
	display.drawString(2, 22, "Brightness: " + String(brightness));
	display.drawString(2, 32, "Speed: " + String(speed));
	display.drawString(2, 50, "IP: " + WiFi.localIP().toString());

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

void handleButtons()
{
	static long prevPress = 0;
	static int potVal1 = 0;
	static int potVal2 = 0;

	static int prevPotVal1 = 0;
	static int prevPotVal2 = 0;
	 
	long buttonTime = 200;

	if (millis() - prevPress > buttonTime)
	{
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
		if (digitalRead(butPin2))
		{
			nextPattern();
			prevPress = millis();
		}
	}

	potVal1 = (prevPotVal1 * 4 + 255 - map(analogRead(potPin1), 0, 4096, 0, 255))/5;
	potVal2 = (prevPotVal2 * 4 + 255 - map(analogRead(potPin2), 0, 4096, 0, 255))/5;

	if (brightness - potVal1 > 2 || brightness - potVal1 < -2)
	{
		brightness = potVal1;
		FastLED.setBrightness(brightness);
	}
	if (speed*5 - potVal2 > 2 || speed*5 - potVal2 < -2)
	{
		speed = potVal2/5;
		
		if (patterns[currentPatternIndex].name == "Solid Color")
		{
			solidColor = CHSV(potVal2,255,255);
		}
	}

	prevPotVal1 = potVal1;
	prevPotVal2 = potVal2;

}