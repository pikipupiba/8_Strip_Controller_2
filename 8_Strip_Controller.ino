
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

// -----------------------------------------------------------------------------------//
// --------------------------------PROJECT LIBRARIES----------------------------------//
// -----------------------------------------------------------------------------------//
#include "tasks.h"			// Functions related to interrupts.
//#include "physicalInputs.h"	// Sets up and handles input from physical controls.
//#include "web.h"
#include "debug.h"			// Contains variables and functions for dubugging.

// -----------------------------------------------------------------------------------//
// ---------------------------------PROJECT CLASSES-----------------------------------//
// -----------------------------------------------------------------------------------//
#include "Universe.h"

#define BUTTON_PIN_W 32

#define BUTTON_PIN_B 35
#define BUTTON_PIN_R 34

Universe universe;

EasyButton button_W(BUTTON_PIN_W, 50, false, true);
EasyButton button_B(BUTTON_PIN_B,50,false,false);
EasyButton button_R(BUTTON_PIN_R, 50, false, false);

void onPressed_W()
{
	universe.NextPattern();
	//Serial.println("WHITE BUTTON PRESSED!");
}

void onHold_W()
{
	universe.ToggleAutoplay();
	//Serial.println("WHITE BUTTON HELD!");
}

void onPressed_B()
{
	universe.uBrightness = universe.uBrightness * 0.8;

	//Serial.println("BLACK BUTTON PRESSED!");
}

void onHold_B()
{
	universe.uBrightness = 255;

	//Serial.println("BLACK BUTTON HELD!");
}

void onSequence_B()
{
	universe.uBrightness = universe.uBrightness * 1.5625;

	universe.ChangeHueFactor();
	//Serial.println("BLACK BUTTON SEQUENCE!");
}

void onPressed_R()
{
	universe.ChangeOffset();
	//Serial.println("RED BUTTON PRESSED!");
}

void onSequence_R()
{
	universe.ChangeOffset();
	universe.ChangeOffset();
	universe.ChangeOffset();
	universe.ChangeOffset();
	universe.ChangeOffset();
	universe.ChangeOffset();

	universe.ChangeSpeedFactor();
	//Serial.println("RED BUTTON SEQUENCE!");
}

void setup() {

	delay(3000);			// 3 second delay for recovery

	Serial.begin(115200);	// Start the Serial Monitor for debugging.

	button_W.begin();
	button_B.begin();
	button_R.begin();

	button_W.onPressed(onPressed_W);
	button_W.onPressedFor(2000, onHold_W);

	button_B.onPressed(onPressed_B);
	button_B.onPressedFor(1300, onHold_B);
	button_B.onSequence(2, 500, onSequence_B);

	button_R.onPressed(onPressed_R);
	button_R.onSequence(2, 500, onSequence_R);

	//setupInputs();
	//setupWeb();

	//FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS * NUM_STRIPS);
	//FastLED.setBrightness(gBrightness);

	createTasks();

	universe = *Universe::CreateUniverse();

	FastLEDshowESP32();

	//displayMemory(" after setup");
}

void loop()
{
	//handleInputs();	// Handles input from physical controls.

	button_W.read();
	button_B.read();
	button_R.read();

	universe.Update();

	//showfps();
	//fps(1);

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