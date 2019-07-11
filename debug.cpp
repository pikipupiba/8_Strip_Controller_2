#include "debug.h"

int debugDepth = 0;

int numMiddles = 0;

bool error = false;

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

void showfps()
{
	static int frame_time = millis();
	static int new_frames = 0;

	new_frames++;

	if (millis() - frame_time > 1000)
	{
		frame_time = (millis() - frame_time) / new_frames;

		Serial.print("Running at ");
		Serial.print(1000 / frame_time);
		Serial.println(" fps");

		frame_time = millis();

		new_frames = 0;
	}
}
