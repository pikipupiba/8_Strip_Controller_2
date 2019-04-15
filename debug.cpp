#include "debug.h"

int debugDepth = 0;

int numMiddles = 0;

void displayMemory(String label = "")
{
	Serial.print("Memory remaining" + label + ": ");
	Serial.print(ESP.getFreeHeap()/1000);
	Serial.println(" KB");
}


void startTime(String functionName)
{
	debugDepth++;

	for (int i = 0; i < debugDepth; i++)
	{
		Serial.print("	");
	}
	Serial.print(functionName);
	Serial.println(" Start ");
	numMiddles = 0;
}

void middleTime(String functionName)
{
	numMiddles++;

	for (int i = 0; i < debugDepth; i++)
	{
		Serial.print("	");
	}
	Serial.print(functionName);
	Serial.print(" Middle #");
	Serial.println(numMiddles);
}

void endTime(String functionName)
{
	for (int i = 0; i < debugDepth; i++)
	{
		Serial.print("	");
	}
	Serial.print(functionName);
	Serial.println(" End ");

	debugDepth--;
	numMiddles = 0;
}