#pragma once

#include <arduino.h>
#include <FastLED.h>



	// I need to get this code out of the class definition.
	typedef void(PatternMeth)();

	typedef struct {
		String name;
		PatternMeth patternMeth;
	} PatternAndName;

	PatternAndName patternAndNameList[] = {
		{ "Color Waves", ColorWaves },
		{ "Color Pulses", ColorPulses },
		{ "Plasma", Plasma }
	};

	const int numPatterns = 3;
	
	void Update();

	void Next();

	void PrintPatternInfo();

	// Pattern Methods!
	void ColorWaves();

	void ColorPulses();

	void Plasma();
};