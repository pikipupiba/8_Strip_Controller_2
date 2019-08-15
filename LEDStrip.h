// The LEDStrip class is responsible for tracking the state of an individual strip.


#pragma once

#include "debug.h"
#include "patterns.h"
#include "palettes.h"

class LEDStrip
{
private:

	bool power;	// If FALSE then the strip brightness is temporarily set to 0.

	unsigned long stripAutoplayTimeout;
	unsigned long stripPaletteTimeout;

protected:
	
public:
	PatternVars vars;	// All the variables required to generate any pattern

	 // Constructor simply passes in the pointer to the CRGBSet assigned to this object.
	 LEDStrip(CRGBSet* leds);//, Shapes newShape);
	 ~LEDStrip();

	 void UpdateStrip();	// generate the next frame
	 void UpdatePatternVars();// advance the pattern variables by 1 frame
	 void ResetTimeouts();	// Resets the timeouts for auto preset and palette rotation.
	
	 void NextPattern();	// Advances the pattern playing on the strip.
	 void PrevPattern();
	 void SetPattern(int newPatternNum);
	 void NextPalette();	// Advances the palette that the patterns are choosing their hues from

	 void ChangeVars(float newSpeed, float newHueSpeed, int newOffset, float newHue);

	 void PrintStripInfo();
};