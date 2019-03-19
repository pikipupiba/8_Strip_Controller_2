#include "display.h"

// Initialize the OLED display using Wire library
SSD1306 display(0x3c, 4, 15);

void setupDisplay()
{
	// Get the display running.
	// TODO Learn more about the display library.
	pinMode(16, OUTPUT);
	digitalWrite(16, LOW); // set GPIO16 low to reset OLED
	delay(50);
	digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high

	display.init();
	display.flipScreenVertically();
	display.setColor(WHITE);
	display.setTextAlignment(TEXT_ALIGN_LEFT);

	// TODO Figure out what other fonts are available and choose one.
	display.setFont(ArialMT_Plain_10);

	drawMenu();
	delay(2000);
}


// Draws the menu onto the OLED display.
// TODO Implement a more rigourous menu structure that uses a rotary encoder for navigation.
// TODO Come up with some icons to easily communicate certain information.
void drawMenu()
{
	if (millis() - mTime > 100)
	{
		startTime("Draw Menu");
		// Clear the display for updating.
		display.clear();

		// ALONG THE TOP or ALONG THE RIGHT.
		// TODO Implement a status bar.

		// TOP LEFT CORNER
		// Display the current state.
		display.drawString(2, 2, "Pattern: ");// +patterns[currentPatternIndex].name);
		display.drawString(2, 12, "Palette: ");// + paletteNames[currentPaletteIndex]);
		display.drawString(2, 22, "Hue Speed: ");// +String(hueSpeed));
		display.drawString(2, 32, "Speed: " + String(gSpeed));

		// BOTTOM LEFT CORNER
		// Diaplay the current IP Address to control via WiFi.
		// TODO Switch between IP Address and the host network SSID every few seconds.
		// TODO Display "Manual Control Only!" if no connection has been made.
		display.drawString(2, 50, "IP: ");// +WiFi.localIP().toString());

		// BOTTOM RIGHT CORNER
		// Display the current power state of the lights.
		if (gPower == 0)
		{
			display.drawString(100, 50, "OFF");
		}
		else
		{
			display.drawString(70, 40, String(frameTime) + " ms");
			display.drawString(90, 50, String(FPS));
		}

		display.display();

		mTime = millis();

		endTime();
	}
}

void displayMemory(String label)
{
	Serial.print("Memory remaining " + label + ": ");
	//Serial.print(freeMemory());
	Serial.println(" Bytes");
}

void calcFPS()
{

	/*Serial.print("New Frames: ");
	Serial.println(newFrames);
	Serial.print(frameTime);
	Serial.println(" ms");
	*/
	frameTime = (millis() - lastFrameTime) / newFrames;

	FPS = 1000 / frameTime;

	lastFrameTime = millis();
	newFrames = 0;

	
}

void debugCounter()
{
	static uint32_t dc = 0;

	Serial.print("Debug Counter: ");
	Serial.println(dc);

	dc++;
}

void startTime(String newFunctionName)
{
	functionName = newFunctionName;

	Serial.print("Starting ");
	Serial.println(functionName);

	sTime = millis();
}

void middleTime()
{
	Serial.print("In the middle of ");
	Serial.print(functionName);
	Serial.print(" at ");
	Serial.print(millis() - sTime);
	Serial.println (" ms");
}

void endTime()
{
	Serial.print("Finished ");
	Serial.print(functionName);
	Serial.print(" at ");
	Serial.print(millis() - sTime);
	Serial.println(" ms");
}