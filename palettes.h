#pragma once

#include <FastLED.h>
#include <Arduino.h>

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
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

// A mostly red palette with green accents and white trim.
// "CRGB::Gray" is used as white to keep the brightness more uniform.

extern const TProgmemRGBPalette16 RedGreenWhite_p;

// A mostly (dark) green palette with red berries.
#define Holly_Green 0x00580c
#define Holly_Red   0xB00402
extern const TProgmemRGBPalette16 Holly_p;

// A red and white striped palette
// "CRGB::Gray" is used as white to keep the brightness more uniform.
extern const TProgmemRGBPalette16 RedWhite_p;

// A mostly blue palette with white accents.
// "CRGB::Gray" is used as white to keep the brightness more uniform.
extern const TProgmemRGBPalette16 BlueWhite_p;

// A pure "fairy light" palette with some brightness variations
#define HALFFAIRY ((CRGB::FairyLight & 0xFEFEFE) / 2)
#define QUARTERFAIRY ((CRGB::FairyLight & 0xFCFCFC) / 4)
extern const TProgmemRGBPalette16 FairyLight_p;

// A palette of soft snowflakes with the occasional bright one
extern const TProgmemRGBPalette16 Snow_p;

// A palette reminiscent of large 'old-school' C9-size tree lights
// in the five classic colors: red, orange, green, blue, and white.
#define C9_Red    0xB80400
#define C9_Orange 0x902C02
#define C9_Green  0x046002
#define C9_Blue   0x070758
#define C9_White  0x606820
extern const TProgmemRGBPalette16 RetroC9_p;

// A cold, icy pale blue palette
#define Ice_Blue1 0x0C1040
#define Ice_Blue2 0x182080
#define Ice_Blue3 0x5080C0
extern const TProgmemRGBPalette16 IcyBlue_p;

extern CRGBPalette16 IceColors_p;

//#include "gradientPalettes.h";

extern const CRGBPalette16 palettes[17];

extern const uint8_t paletteCount;

//const String paletteNames[16];

extern CRGBPalette16 currentPalette;
extern CRGBPalette16 targetPalette;