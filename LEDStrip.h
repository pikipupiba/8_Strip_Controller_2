#pragma once

#include "debug.h"
#include "patterns.h"

class LEDStrip
{
private:

	bool power;					// If FALSE then the strip brightness is temporarily set to 0.

	//bool stripAutoplay;			// If TRUE then the current pattern (or preset!) will change every autoplayDuration seconds.
	//int stripAutoplayDuration;
	unsigned long stripAutoplayTimeout;

protected:
	
public:
	PatternVars vars;

	 // Constructor simply passes in the pointer to the CRGBSet assigned to this object.
	 LEDStrip(CRGBSet* leds);//, Shapes newShape);
	 ~LEDStrip();

	 void UpdateStrip();
	 void UpdatePatternVars();
	 void ResetTimeouts();	// Resets the timeouts for auto preset and palette rotation.
	
	 void NextPattern();	// Advances the pattern playing on the strip.

	 void ChangeVars(float newSpeed, float newHueSpeed, int newOffset, float newHue);

	 void PrintStripInfo();
};