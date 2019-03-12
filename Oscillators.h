#pragma once

class Oscillators
{
private:
	uint32_t BPM;	// Overall BPM of the oscillator.
	int min;		// Absolute minimum value reached by the oscillator.
	int max;		// Absolute maximum valur reached by the oscillator.

public:
	Oscillators();
	~Oscillators();

	int Oscillator1();
	int Oscillator2();
	int Oscillator3();
	int Oscillator4();
	
	void ChangeBPM(uint32_t newBPM, uint32_t newChangeTime);
};

