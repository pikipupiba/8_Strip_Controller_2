#include "Mover.h"



Mover::Mover(uint32_t newPreset)
{

}


Mover::~Mover()
{
}

void Mover::Update()
{
	GeneralUpdate();
	Draw();
}

void Mover::Draw()
{

	animationLEDs[0, 300] = CRGB::Black;

	if (end1 < end2)
	{
		animationLEDs[integerPart(end1, 0, 300), integerPart(end2, 0, 300)] = hue;
	}
	else
	{
		animationLEDs[integerPart(end1, 0, 300), integerPart(rangeEnd, 0, 300)];
		animationLEDs[integerPart(rangeStart, 0, 300), integerPart(end2, 0, 300)];
	}

	animationLEDs[integerPart(end1, 0, 300)] *= 1 - fractionalPart(end1, 0, 300);
	animationLEDs[integerPart(end2, 0, 300)] *= fractionalPart(end2, 0, 300);

}
