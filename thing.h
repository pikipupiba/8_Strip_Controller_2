// thing.h

#ifndef _THING_h
#define _THING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ThingClass
{
 protected:


 public:
	void init();
};

extern ThingClass Thing;

#endif

