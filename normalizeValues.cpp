#include "stdafx.h"

#include "normalizeValues.h"

float uint32_to_float(uint32_t val, int min, int max)
{
	//Serial.println(val);
	//Serial.println(min);
	//Serial.println(max);
	//Serial.println(val / uINT32_RANGE * (max - min) + min);

	return ((float)val / (float)uINT32_RANGE) * ((float)max - (float)min) + (float)min;
}

float int32_to_float(int val, int min, int max)
{
	return (val - INT32_MIN) / INT32_RANGE * (max - min) + min;
}

uint32_t uint32_to_uint32(uint32_t val, uint32_t min, uint32_t max)
{
	return ((float)val / (float)uINT32_RANGE) * (max - min) + min;
}

// Undo the normalization of a number. This probably loses information so watch out.
/*long int expand(int val, int min, int max, uint32_t type)
{
switch (type) // Expanding depends of the desired variable type.
{
case 1: return map(val, min, max, uINT32_MIN,	uINT32_MAX);	// type 1 is uint32_t
case 2: return map(val, min, max, INT32_MIN,	INT32_MAX);		// type 2 is int
}
}

// Calcualtes the step size based on data type and current range.
uint32_t stepSize(int min, int max, uint32_t type)
{
int size = max - min;

switch (type) // Expanding depends of the desired variable type.
{
case 1: return uINT32_MAX / size;	// type 1 is uint32_t
case 2: return INT32_MAX / size;	// type 2 is int
}
}*/