#include "display.h"

// Initialize the OLED display using Wire library
SSD1306 display(0x3c, 4, 15);

void setupDisplay()
{
	D( startTime("setupDisplay()"); )

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

	D( endTime("setupDisplay()"); )
}

/*void drawMenu()
{
	// Clear the display for updating.
	display.clear();

	// ALONG THE TOP or ALONG THE RIGHT.
	// TODO Implement a status bar.

	// TOP LEFT CORNER
	// Display the current state.
	display.drawString(2, 2, "Pattern: ");// +patterns[currentPatternIndex].name);
	display.drawString(2, 12, "Palette: ");// +paletteNames[currentPaletteIndex]);
	display.drawString(2, 22, "Brightness: ");// +String(brightness));
	display.drawString(2, 32, "Speed: ");// +String(speed));

	// BOTTOM LEFT CORNER
	// Diaplay the current IP Address to control via WiFi.
	// TODO Switch between IP Address and the host network SSID every few seconds.
	// TODO Display "Manual Control Only!" if no connection has been made.
	display.drawString(2, 50, "IP: ");// + WiFi.localIP().toString());

	// BOTTOM RIGHT CORNER
	// Display the current power state of the lights.
	if (gPower == 0)
	{
		display.drawString(100, 50, "OFF");
	}
	else
	{
		display.drawString(100, 50, "ON");
	}

	display.display();
}*/


// Draws the menu onto the OLED display.
// TODO Implement a more rigourous menu structure that uses a rotary encoder for navigation.
// TODO Come up with some icons to easily communicate certain information.
// TODO The last Heltec WiFi Kit 32 I used showed weird behavior before I broke it. Investigate on new display.
void drawMenu()
{
	static unsigned long mTime = millis();

	// Only refresh the menu 10 times per second.
	if (millis() - mTime > 100)
	{
		D(startTime("drawMenu()"); )

		// Clear the display for updating.
		display.clear();

		// ALONG THE TOP or ALONG THE RIGHT.
		// TODO Implement a status bar.

		// TOP LEFT CORNER
		// Display the current state.
		display.drawString(2, 2, "Pattern: ");// +patterns[currentPatternIndex].name);
		display.drawString(2, 12, "Palette: ");// + paletteNames[currentPaletteIndex]);
		display.drawString(2, 22, "Hue Speed: " + String(gHueSpeed));
		display.drawString(2, 32, "Speed: " + String(gSpeed));

		// BOTTOM LEFT CORNER
		// Diaplay the current IP Address to control via WiFi.
		// TODO Switch between IP Address and the host network SSID every few seconds.
		// TODO Display "Manual Control Only!" if no connection has been made.
		display.drawString(2, 50, "IP: ");// +WiFi.localIP().toString());

		// BOTTOM RIGHT CORNER
		// Display the current power state of the lights.
		if (gPower == 0)
		{ display.drawString(100, 50, "OFF"); }

		else
		{
			// TODO Why can I not output these strings!?!?
			display.drawString(70, 40, "Hmmm");// String(frameTime) + " ms");
			String sHue = String(gHue);
			//display.drawString(90, 50, sHue);// String(FPS));
		}

		display.display();

		mTime = millis();

		D( endTime("drawMenu()"); )
	}
}

void displayMemory(String label = "")
{
	Serial.print("Memory remaining" + label + ": ");
	Serial.print(ESP.getFreeHeap()/1000);
	Serial.println(" KB");
	Serial.print("Number of Animations: ");
	Serial.println(numObjects);
}

void calcFPS()
{

	if (newFrames > 0)
	{
		frameTime = (float)(millis() - lastFrameTime) / (float)newFrames;

		FPS = 1000 / frameTime;

		lastFrameTime = millis();
		newFrames = 0;

		speedScaleFactor = (float)100 / (float)FPS;

		Serial.print("Frame Time: ");
		Serial.println(frameTime);
		Serial.print("FPS: ");
		Serial.println(FPS);
		Serial.print("Speed Scale Factor : ");
		Serial.println(speedScaleFactor);
	}
	
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

void middleTime(String newFunctionName)
{
	Serial.print("In the middle of ");
	Serial.print(newFunctionName);
	Serial.print(" at ");
	Serial.print(millis() - sTime);
	Serial.println (" ms");
}

void endTime(String newFunctionName)
{
	Serial.print("Finished ");
	Serial.print(newFunctionName);
	Serial.print(" at ");
	Serial.print(millis() - sTime);
	Serial.println(" ms");
}