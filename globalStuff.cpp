#pragma once
#include "globalStuff.h"

CRGBArray<NUM_LEDS> leds;

// Set the master variables to their starting values.

uint32_t gHue = 0;
int gHueSpeed = 1;

bool gPower = true;

uint32_t gBrightness = 128;

int gSpeed = 0;

// Set the variables for tracking frames per second to their starting values.
uint32_t frameTime = 1;
unsigned long lastFrameTime = 1;
uint32_t newFrames = 1;
uint32_t FPS = 0;

unsigned long sTime = 0;
unsigned long mTime = 0;
String functionName = "";

uint32_t numObjects = 0;