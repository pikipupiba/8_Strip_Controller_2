// Functions useful for debugging my code!

#include <arduino.h>

//#define DEBUG_US

#if defined DEBUG_US
#	define D(x) x
#else
#	define D(x)
#endif


#define D2(x) x

void displayMemory(String label);

// Print functions for debugging.
void startTime(String newFunctionName);
void middleTime(String newFunctionName);
void endTime(String newFunctionName);

void showfps();
