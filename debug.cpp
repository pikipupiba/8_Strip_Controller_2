#include "debug.h"

int debugDepth = 0;


void displayMemory(String label = "")
{
	Serial.print("Memory remaining" + label + ": ");
	Serial.print(ESP.getFreeHeap()/1000);
	Serial.println(" KB");
}


void startTime(String functionName)
{
	for (int i = 0; i < debugDepth; i++)
	{
		Serial.print("	");
	}
	Serial.print(functionName);
	Serial.println(" Start ");

	debugDepth++;
}

void middleTime(String functionName)
{
	for (int i = 0; i < debugDepth; i++)
	{
		Serial.print("	");
	}
	Serial.print(functionName);
	Serial.println(" Middle ");
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
}