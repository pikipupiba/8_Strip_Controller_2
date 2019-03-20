#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

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

#include "globalStuff.h"

// Return the integer part of an unsigned 32-bit integer when compressed to size max - min.
float uint32_to_float(uint32_t val, int min, int max);

float int32_to_float(int val, int min, int max);

uint32_t uint32_to_uint32(uint32_t val, uint32_t min, uint32_t max);

// Undo the normalization of a number. This probably loses information so watch out.
//long int expand(int val, int min, int max, uint32_t type);

// Calcualtes the step size based on data type and current range.
//uint32_t stepSize(int min, int max, uint32_t type);