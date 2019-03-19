
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
//#include <WebServer.h>
//#include <WiFi.h>
#include <FS.h>
//#include <SPIFFS.h>
//#include <EEPROM.h>
#include <MemoryFree.h>

// Define the WebServer object.
//WebServer webServer(80);

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001008)
#warning "Requires FastLED 3.1.8 or later; check github for latest code."
#endif

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


// WiFi Status led.
// TODO No longer needed. REMOVE IT! Maybe?
const int boardLedPin = 2;

// -----------------------------------------------------------------------------------//
// --------------------------------PROJECT LIBRARIES----------------------------------//
// -----------------------------------------------------------------------------------//

//#include "tasks.h"			// Functions related to interrupts.

//#include "defaultSettings.h"// Contains all default settings to use if no saved settings are available.
//#include "globalStuff.h"
#include "normalizeValues.h"// Contains the functions to compress signed and unsigned ints to more precise smaller ranges.

#include "animationPresets.h"	// The location of presets used when initializing animation objects.
#include "stripPresets.h"	// The location of presets for entire strips which can include multiple animation presets.
#include "universePresets.h"// The location of presets for a collection of strips.

//#include "patterns.h"		// Patterns use various animation objects to create an effect.
//#include "palettes.h"		// Palettes define specific selections of colors to be used by animations.

//#include "field.h"			// Gets field values from the web server.
//#include "fields.h"			// Causes field values to affect program.

//#include "secrets.h"		// Contains information about WiFi networks the ESP32 should try to connect for web control.
//#include "wifi_changed.h"	// 
//#include "web.h"			// Sets up the web server and handles web input.
//#include "physicalInputs.h"	// Sets up and handles input from physical inputs.
#include "display.h"	// Handles setting up and displaying to the built in display and serial output.

// -----------------------------------------------------------------------------------//
// ---------------------------------PROJECT CLASSES-----------------------------------//
// -----------------------------------------------------------------------------------//

#include "Oscillators.h"	// A custom oscillator class for varying animation variables.
#include "Animations.h"		// An interface class from which individual animations can inherit their base functionality.
#include "Mover.h"
#include "StripController.h"// A strip controller is created for each strip connected to the ESP32.


// Create array of strips available to the program.
StripController* strip[8];


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

void createTasks()
{

	// Print the core the main code is running on.
	// Make sure to change FASTLED_SHOW_CORE if it is the same as this one.
	int core = xPortGetCoreID();
	Serial.print("Main code running on core ");
	Serial.println(core);

	// -- Create the FastLED show task
	xTaskCreatePinnedToCore(FastLEDshowTask, "FastLEDshowTask", 2048, NULL, 2, &FastLEDshowTaskHandle, FASTLED_SHOW_CORE);

}

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
	//setupWeb();				// Put the contents of the SPIFFS onto the web server.

	// Initialize the strips connected to the ESP32.
	// TODO I need to figure out how to adjust this based on settings. Users will probably have to save these values into
	// EEPROM and then restart the ESP32 to apply the new settings. Maybe you select a strip setup in this setup() function
	// either by manually entering strip lengths or selecting a previously saved setup.
	// TODO Figure out how to change these things during execution.
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strip[i] = new StripController(i, NUM_LEDS_PER_STRIP);// , Strip);
	}

	FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS * NUM_STRIPS);

	// set master brightness control
	FastLED.setBrightness(gBrightness);

	createTasks();
	
	displayMemory("after setup");

	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strip[i]->ResetTimeouts();
	}

}

void loop()
{
	debugCounter();
	//handleWeb();	// Handles input from the web server.
	//handleInputs();	// Handles input from physical controls.

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
		strip[i]->UpdateStrip();
	}
	
	EVERY_N_SECONDS(5)
	{
		for (int i = 0; i < NUM_STRIPS; i++)
		{
			strip[i]->AddAnimation();
		}
	}

	// send the 'leds' array out to the actual LED strip
	// FastLED.show();
	FastLEDshowESP32();

	newFrames++;
	calcFPS();


	// insert a delay to keep the framerate modest.
	// TODO Learn more about why the FastLED.delay() doesn't work and if it can be used, use it.
	// FastLED.delay(1000 / FRAMES_PER_SECOND);
	delay(1000 / FRAMES_PER_SECOND);


}