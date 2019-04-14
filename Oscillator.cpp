#pragma once

#include "Oscillator.h"

#define uINT16_MIN 0
#define uINT16_MAX 65536

Oscillator::Oscillator(int newBPM, float newMin, float newMax)
{
	BPM = newBPM;
	min = newMin;
	max = newMax;

	range = max - min;

}


Oscillator::~Oscillator()
{

}

float Oscillator::O1(uint16_t offset)
{
	// TODO figure out how to normalize any inputs to what is needed for proper functioning.
	return range * (float)beatsin16(BPM) / (float)uINT16_MAX + min;
} 

float Oscillator::O2(uint16_t offset)
{
	return range * (float)(beatsin16(BPM) * 2 + beatsin16(BPM * 3)) / 3 / (float)uINT16_MAX + min;
}

float Oscillator::O3(uint16_t offset)
{
	float h0 = beatsin16( BPM		)	*	2;
	float h1 = beatsin16( BPM * 2	)	/	2;	
	float h2 = beatsin16( BPM * 3	)	/	2;
	float h3 = beatsin16( BPM * 5	)	/	2;

	float hTotal = (h0 + h1 + h2 + h3) / 3.5;

	return range * hTotal / (float)uINT16_MAX + min;
}

float Oscillator::O4(uint16_t offset)
{
	float h0 = beatsin16(BPM * 1,	uINT16_MIN,	uINT16_MAX,	0,	offset)	*	1	;
	float h1 = beatsin16(BPM * 1.5, uINT16_MIN, uINT16_MAX, 0,	offset)	/	1.5	;
	float h2 = beatsin16(BPM * 2,	uINT16_MIN, uINT16_MAX, 0,	offset)	/	2	;
	float h3 = beatsin16(BPM * 3.5, uINT16_MIN, uINT16_MAX, 0,	offset)	/	3.5	;

	float hTotal = (h0 + h1 + h2 + h3) / 2.4523809524;

	return range * hTotal / (float)uINT16_MAX + min;
}

// Change BPM in such a way as to avoid stuttering of oscillator output.
void Oscillator::ChangeBPM(float newBPM, int newChangeTime)
{
}