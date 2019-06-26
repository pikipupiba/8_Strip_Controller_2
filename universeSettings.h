#pragma once

#define NUM_STRIPS 8

#define NUM_LEDS_STRIP_0 300
#define NUM_LEDS_STRIP_1 300
#define NUM_LEDS_STRIP_2 300
#define NUM_LEDS_STRIP_3 300
#define NUM_LEDS_STRIP_4 300
#define NUM_LEDS_STRIP_5 300
#define NUM_LEDS_STRIP_6 300
#define NUM_LEDS_STRIP_7 300
#define NUM_LEDS_STRIP_8 00
#define NUM_LEDS_STRIP_9 00
#define NUM_LEDS_STRIP_10 00
#define NUM_LEDS_STRIP_11 00
#define NUM_LEDS_STRIP_12 00
#define NUM_LEDS_STRIP_13 00
#define NUM_LEDS_STRIP_14 00
#define NUM_LEDS_STRIP_15 00

#define NUM_LEDS	NUM_LEDS_STRIP_0 + \
					NUM_LEDS_STRIP_1 + \
					NUM_LEDS_STRIP_2 + \
					NUM_LEDS_STRIP_3 + \
					NUM_LEDS_STRIP_4 + \
					NUM_LEDS_STRIP_5 + \
					NUM_LEDS_STRIP_6 + \
					NUM_LEDS_STRIP_7 + \
					NUM_LEDS_STRIP_8 + \
					NUM_LEDS_STRIP_9 + \
					NUM_LEDS_STRIP_10 + \
					NUM_LEDS_STRIP_11 + \
					NUM_LEDS_STRIP_12 + \
					NUM_LEDS_STRIP_13 + \
					NUM_LEDS_STRIP_14 + \
					NUM_LEDS_STRIP_15

/* The pins I used in the before time */
//#define STRIP_PIN_0 13
//#define STRIP_PIN_1 12
//#define STRIP_PIN_2 27
//#define STRIP_PIN_3 33
//#define STRIP_PIN_4 15
//#define STRIP_PIN_5 32
//#define STRIP_PIN_6 14
//#define STRIP_PIN_7 SCL

/* The pins used on Jason Coon's awesome PCBs */
#define STRIP_PIN_0 13
#define STRIP_PIN_1 12
#define STRIP_PIN_2 15
#define STRIP_PIN_3 2
#define STRIP_PIN_4 0
#define STRIP_PIN_5 4
#define STRIP_PIN_6 16
#define STRIP_PIN_7 17

/* The pins used on an Arduino Nano */
//#define STRIP_PIN_0 11
//#define STRIP_PIN_1 12
//#define STRIP_PIN_2 15
//#define STRIP_PIN_3 2
//#define STRIP_PIN_4 0
//#define STRIP_PIN_5 4
//#define STRIP_PIN_6 16
//#define STRIP_PIN_7 17

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

#define MILLI_AMPS 120000

#define FRAMES_PER_SECOND