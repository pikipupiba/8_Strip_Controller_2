#pragma once

#include <arduino.h>
#include <FastLED.h>

class Oscillator
{
private:
	int BPM;	// Overall BPM of the oscillator.
	float min;		// Absolute minimum value reached by the oscillator.
	float max;		// Absolute maximum valur reached by the oscillator.

	float range;

public:
	Oscillator(int newBPM, float newMin, float newMax);
	~Oscillator();

	// Different Oscillator combine different harmonic series of the overall BPM at different intensities.
	float O1(uint16_t offset);
	float O2(uint16_t offset);
	float O3(uint16_t offset);
	float O4(uint16_t offset);
	
	// Change the BPM smoothly maintaining the oscillator's current position.
	// and maybe even the first derivative if I'm baller enough.
	void ChangeBPM(float newBPM, int newChangeTime);
};