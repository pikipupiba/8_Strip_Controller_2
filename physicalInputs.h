// This module is currently configured to take advantage of my button panel
// with 8 buttons and 4 potentiometers

#pragma once

#define POT_PIN_GOLD		14
#define BUTTON_PIN_YELLOW	5
#define BUTTON_PIN_BLACK	18

#define POT_PIN_RED			34
#define BUTTON_PIN_RED_T	21
#define BUTTON_PIN_RED_B	22

#define POT_PIN_GREEN		35
#define BUTTON_PIN_GREEN_T	25
#define BUTTON_PIN_GREEN_B	26

#define POT_PIN_BLUE		27
#define BUTTON_PIN_BLUE_T	32
#define BUTTON_PIN_BLUE_B	33

int pot_gold = 0;
EasyButton but_yellow(BUTTON_PIN_YELLOW, 50, false, false);
EasyButton but_black(BUTTON_PIN_BLACK, 50, false, false);

float pot_red = 0;
EasyButton but_red_t(BUTTON_PIN_RED_T, 50, false, false);
EasyButton but_red_b(BUTTON_PIN_RED_B, 50, false, false);

float pot_green = 0;
EasyButton but_green_t(BUTTON_PIN_GREEN_T, 50, false, false);
EasyButton but_green_b(BUTTON_PIN_GREEN_B, 50, false, false);

int pot_blue = 0;
EasyButton but_blue_t(BUTTON_PIN_BLUE_T, 50, false, false);
EasyButton but_blue_b(BUTTON_PIN_BLUE_B, 50, false, false);


void PressedYellow()
{
	universe.NextPattern();

	//Serial.println("Pressed Yellow!");
}

void OnPressedForYellow()
{
	universe.ToggleAutoplay();
}

void PressedBlack()
{
	universe.PrevPattern();

	//Serial.println("Pressed Black!");
}

void PressedRedT()
{
	//Serial.println("Pressed Red Top!");
}

void PressedRedB()
{
	//Serial.println("Pressed Red Bottom!");
}

void PressedGreenT()
{
	universe.NextHue();

	//Serial.println("Pressed Green Top!");
}

void PressedGreenB()
{
	universe.RandomHue();

	//Serial.println("Pressed Green Bottom!");
}

void PressedBlueT()
{
	universe.uStrobeTime += 5;

	//Serial.println("Pressed Blue Top!");
}

void OnPressedForBlueT()
{
	universe.uStrobeTime *= 1.5;
}

void PressedBlueB()
{

	universe.uStrobeTime -= 2;

	if (universe.uStrobeTime < 0)
	{
		universe.uStrobeTime = 0;
	}

	//Serial.println("Pressed Blue Bottom!");
}

void OnPressedForBlueB()
{
	universe.uStrobeTime = 0;
}

void setupInputs()
{
	but_yellow.begin();
	but_black.begin();

	but_red_b.begin();
	but_red_t.begin();

	but_green_b.begin();
	but_green_t.begin();

	but_blue_b.begin();
	but_blue_t.begin();

	but_yellow.onPressed(PressedYellow);
	but_yellow.onPressedFor(3000, OnPressedForYellow);
	but_black.onPressed(PressedBlack);

	but_red_b.onPressed(PressedRedB);
	but_red_t.onPressed(PressedRedT);

	but_green_b.onPressed(PressedGreenB);
	but_green_t.onPressed(PressedGreenT);

	but_blue_b.onPressed(PressedBlueB);
	but_blue_b.onPressedFor(2000, OnPressedForBlueB);
	but_blue_t.onPressed(PressedBlueT);
	but_blue_t.onPressedFor(1000, OnPressedForBlueT);
}


void handleInputs()
{
	pot_gold = analogRead(POT_PIN_GOLD);
	universe.uBrightness = (universe.uBrightness * 3 + pot_gold / 16) / 4;
	but_yellow.read();
	but_black.read();

	pot_red = (pot_red * 3 + (float)analogRead(POT_PIN_RED) / 1024 ) / 4;

	static float speedScaleFactor = pot_red;

	if ((pot_red < 0.95 * speedScaleFactor || pot_red > 1.05 * speedScaleFactor) && universe.uAutoplay == false)
	{

		if (speedScaleFactor > 0.4 || pot_red < 0.75 * speedScaleFactor || pot_red > 1.25 * speedScaleFactor)
		{
			//Serial.println("CHANGED!");
			speedScaleFactor = pot_red;

			universe.ChangeSpeedFactor(speedScaleFactor);
		}
	}

	but_red_b.read();

	but_red_t.read();

	pot_green = (pot_green * 3 + (float)analogRead(POT_PIN_GREEN) / 1024) / 4;

	static float hueScaleFactor = pot_green;

	if ((pot_green < 0.95 * hueScaleFactor || pot_green > 1.05 * hueScaleFactor) && universe.uAutoplay == false)
	{
		hueScaleFactor = pot_green;

		universe.ChangeHueFactor(hueScaleFactor);
	}

	but_green_b.read();
	but_green_t.read();

	pot_blue = (pot_blue * 3 + analogRead(POT_PIN_BLUE) / 128 ) / 4;

	static float offset = pot_blue;



	if ((pot_blue < offset - 1 || pot_blue > offset + 1) && universe.uAutoplay == false)
	{
		offset = pot_blue;

		if (offset < 5)
		{
			offset = 0;
		}

		universe.ChangeOffset(offset);
	}

	but_blue_b.read();
	but_blue_t.read();

	/*EVERY_N_SECONDS(5)
	{
		Serial.println();

		Serial.print("Gold: ");
		Serial.println(pot_gold);

		Serial.print("Red: ");
		Serial.println(pot_red);

		Serial.print("Green: ");
		Serial.println(pot_green);

		Serial.print("Blue: ");
		Serial.println(pot_blue);
	}*/

	if (but_red_b.isPressed())
	{
		delay(30);
	}

	if (but_red_t.isPressed())
	{
		delay(75);
	}

	if (universe.uStrobeTime != 0)
	{
		universe.uBrightness = beatsin8(universe.uStrobeTime);
	}
	
}

