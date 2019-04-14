#pragma once

#include "Patterns.h"

//class StripController;
//typedef void (StripController::*PatternList[])();
//PatternList patterns = { StripController::PoopyWorm1, StripController::PoopyWorm2 };

class LEDStrip
{
private:

	int numLEDs;				// Number of LEDs assigned to the strip

	bool power;					// If FALSE then the strip brightness is temporarily set to 0.

	PatternClass* curPattern;	// Array of animations currently active on this strip.

	bool stripAutoplay;			// If TRUE then the current pattern (or preset!) will change every autoplayDuration seconds.
	int stripAutoplayDuration;
	unsigned long stripAutoPlayTimeout;

protected:
	
 public:

	 // Constructor simply passes in the pointer to the CRGBSet assigned to this object.
	 LEDStrip(CRGBSet leds);//, Shapes newShape);
	 ~LEDStrip();

	 void UpdateStrip();	// Updates each animation running on the strip and combines them to be displayed.
	 void ResetTimeouts();	// Resets the timeouts for auto preset and palette rotation.
	
	 void NextPattern();	// Advances the pattern playing on the strip.

	 void PrintStripInfo();
};