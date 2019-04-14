#pragma once

#include <arduino.h>
#include <FastLED.h>

const int numPatterns = 3;

class PatternClass
{
private:

	// I need to get this code out of the class definition.
	typedef void(PatternClass::*PatternMeth)();

	typedef struct {
		String name;
		PatternMeth patternMeth;
	} Pattern;

	Pattern curPattern;

	typedef Pattern PatternList[numPatterns];

	PatternList patternList = {
		{ "Color Waves", &PatternClass::ColorWaves },
		{ "Color Pulses", &PatternClass::ColorPulses },
		{ "Plasma", &PatternClass::Plasma }
	};
	
	CRGBSet* leds;

public:
	PatternClass(CRGBSet* leds);
	~PatternClass();

	void Update();

	void Next();

	void PrintPatternInfo();

	// Pattern Methods!
	void ColorWaves();

	void ColorPulses();

	void Plasma();
};