#pragma once
#include "globalStuff.h"

CRGBArray<NUM_LEDS> leds;

// Set the master variables to their starting values.

float gHue = 0;
float gHueSpeed = 1;

bool gPower = true;

float gBrightness = 128;

int gSpeed = 0;

// Set the variables for tracking frames per second to their starting values.
float frameTime = 1;
unsigned long lastFrameTime = 1;
int newFrames = 1;
float FPS = 0;
float speedScaleFactor = 1;

unsigned long sTime = 0;
String functionName = "";

int numObjects = 0;