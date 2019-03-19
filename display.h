#pragma once

// Contains everything needed for using the built in display and outputing certain information to the serial moniter.

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306.h> // alias for #include "SSD1306Wire.h"'
#include <FS.h>
#include <MemoryFree.h>

#include "globalStuff.h"

// Initialize the OLED display using Wire library
//extern SSD1306 display;

void setupDisplay();
void drawMenu();
void displayMemory(String label);
void calcFPS();

// Print functions for debugging.
void debugCounter();
void startTime(String newFunctionName);
void middleTime();
void endTime();