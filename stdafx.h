#pragma once


#if defined (ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include<FastLED.h>
#include <WebServer.h>
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#include <EEPROM.h>

#include <SSD1306.h> // alias for #include "SSD1306Wire.h"'