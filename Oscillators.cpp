#include "stdafx.h"

#pragma once

#include "Oscillators.h"



Oscillators::Oscillators()
{

}


Oscillators::~Oscillators()
{
}

int Oscillators::Oscillator1()
{
	// TODO figure out how to normalize any inputs to what is needed for proper functioning.
	return beatsin16(BPM, min, max);
} 

int Oscillators::Oscillator2()
{
	return 0;
}

int Oscillators::Oscillator3()
{
	return 0;
}

int Oscillators::Oscillator4()
{
	return 0;
}

// Change BPM in such a way as to avoid stuttering of oscillator output.
void Oscillators::ChangeBPM(uint32_t newBPM, uint32_t newChangeTime)
{
}
