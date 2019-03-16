#pragma once

// HELP!
// Obviously this is not optimized, but once completed will this be faster than just using floats to track animation parameters?
// If this method is faster than using floats, then am I on the right track as far as how to accomplish my goal?

// These functions are meant to allow fine control of certain parameters while maintaing the speed of integer addition.
// The precision is determined by the range the data is being compressed into and the original data type.
// For example, I can track position as a uint32_t and still be able to antialias the final output with the fractional
// part once squeezed into its specified range on a strip.

// I know this is not in any way working or done but I think this is about how it will work.
// TODO Make sure negatives, etc are handled correctly.
// TODO Potentialy pass variables by reference to set the integer and fractional parts in the function itself.

// Define minimum and maximum values of some data types.
#define uINT8_MIN	0
#define uINT8_MAX	255

#define INT16_MIN  -32768
#define INT16_MAX	32767

#define uINT16_MIN	0
#define uINT16_MAX	65535

#define INT32_MIN  -2147483648
#define INT32_MAX	2147483647
#define INT32_RANGE INT32_MAX - INT32_MIN

#define uINT32_MIN	0
#define uINT32_MAX	4294967295
#define uINT32_RANGE uINT32_MAX - uINT32_MIN

// Return the integer part of an unsigned 32-bit integer when compressed to size max - min.
float uint32_to_float(uint32_t val, int min, int max)
{
	return val / uINT32_RANGE * (max - min) + min;
}

float int32_to_float(int val, int min, int max)
{
    return (val - INT32_MIN) / INT32_RANGE * (max - min) + min;
}

// Return the fractional part of an unsigned 32-bit integer when compressed to size max - min.
float fractionalPart(uint32_t val, int min, int max)
{
	return (val - expand(integerPart(val, min, max), min, max, 1)) / (uINT32_MAX / (max - min));
}

// Undo the normalization of a number. This probably loses information so watch out.
long int expand(int val, int min, int max, uint32_t type)
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
}