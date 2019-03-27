#include "stdafx.h"

#pragma once

//#include <stdint.h>


class Oscillators
{
private:
	uint32_t BPM;	// Overall BPM of the oscillator.
	int min;		// Absolute minimum value reached by the oscillator.
	int max;		// Absolute maximum valur reached by the oscillator.

public:
	Oscillators();
	~Oscillators();

	// Different oscillators combine different harmonic series of the overall BPM at different intensities.
	int Oscillator1();
	int Oscillator2();
	int Oscillator3();
	int Oscillator4();
	
	// Change the BPM smoothly maintaining the oscillator's current position.
	// and maybe even the first derivative if I'm baller enough.
	void ChangeBPM(uint32_t newBPM, uint32_t newChangeTime);
};