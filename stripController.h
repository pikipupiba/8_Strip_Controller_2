// stripController.h
#pragma once

// ESP32 default pin settings
#define DATA_PIN_0 13
#define DATA_PIN_1 12
#define DATA_PIN_2 27
#define DATA_PIN_3 33
#define DATA_PIN_4 15
#define DATA_PIN_5 32
#define DATA_PIN_6 14
#define DATA_PIN_7 SCL

// Define a clock pin if your LEDs require it.
//#define CLK_PIN   4

// Define the standard properties of the LED strips I currently own.
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_STRIPS 8
#define NUM_LEDS_PER_STRIP 300

// TODO Probably don't need the total number of LEDs because each strip will be controlled individually.
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS

CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

#define MILLI_AMPS         60000 // IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)
#define FRAMES_PER_SECOND  120

enum Shapes { Strip, Panel, Ring };

bool masterPower = true;
uint8_t masterBrightness = 128;

class StripController
{
 protected:
	 uint8_t index;
	 uint16_t numLEDs;

	 Shapes shape;

	 bool power;
	 float brightness;

	 float curPos;
	 float speed;
	 float curHue;
	 float hueSpeed;

	 bool autoplay;
	 uint8_t autoplayDuration;
	 unsigned long autoPlayTimeout;

	 bool cyclePalettes;
	 uint8_t paletteDuration;
	 unsigned long paletteTimeout;

	 uint8_t curPattern;
	 uint8_t curPaletteIndex;
	 CRGBPalette16 curPalette;
	 CRGBPalette16 tarPalette;

	 // COOLING: How much does the air cool as it rises?
	 // Less cooling = taller flames.  More cooling = shorter flames.
	 // Default 50, suggested range 20-100
	 uint8_t cooling = 50;

	 // SPARKING: What chance (out of 255) is there that a new spark will be lit?
	 // Higher chance = more roaring fire.  Lower chance = more flickery fire.
	 // Default 120, suggested range 50-200.
	 uint8_t sparking = 120;

 public:
	 StripController(uint8_t newStripNum, uint16_t newNumLEDs, Shapes newShape);

	 void updateStrip();
	 void resetTimeouts();
	
	 void nextPattern();
	 void nextPalette();

	 uint8_t getLength();
	 int getSpeed();
};