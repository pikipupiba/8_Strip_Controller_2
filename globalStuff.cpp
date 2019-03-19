#pragma once
#include "globalStuff.h"

CRGBArray<NUM_LEDS> leds;

// Set the master variables to their starting values.

uint8_t gHue = 0;

bool gPower = true;

uint32_t gBrightness = 128;

int gSpeed = 0;

// Set the variables for tracking frames per second to their starting values.
unsigned long frameTime = 0;
unsigned long lastFrameTime = 0;
uint32_t newFrames = 0;
uint32_t FPS = 0;

unsigned long sTime = 0;
unsigned long mTime = 0;
String functionName = "";