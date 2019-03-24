#pragma once

#include "Animations.h"
#include "display.h"


Animations::Animations()
{
	
}

Animations::~Animations()
{
}

void Animations::UpdatePosition()
{
	hue += (hueSpeed * speedScaleFactor) % 255;
	hueSpeed += hueAcceleration;

	position += speed * speedScaleFactor;
	speed += acceleration;

	end1 = position - featureSize / 2;
	end2 = position + featureSize / 2;

	switch (animationEndOfRange)
	{
	case EndOfRanges::Bounce:

		if (end2 < rangeEnd && end1 > rangeStart)
		{}
		else if (end2 > rangeEnd)
		{
			position = rangeEnd - featureSize / 2;
			if (speed > 0)
			{
				speed = -speed;
			}
			if (acceleration > 0)
			{
				acceleration = -acceleration;
			}
		}
		else if (end1 < rangeStart)
		{
			position = rangeStart + featureSize / 2;
			if (speed < 0)
			{
				speed = -speed;
			}
			if (acceleration < 0)
			{
				acceleration = -acceleration;
			}
		}
		break;
	
	case EndOfRanges::Loop:

		if (position > rangeEnd)
		{
			position -= rangeSize;
		}
		else if (position < rangeStart)
		{
			position += rangeSize;
		}
		break;
	}

	end1 = position - featureSize / 2;
	end2 = position + featureSize / 2;

	if (end2 > rangeEnd)
	{
		end2 -= rangeSize;
	}
	else if (end1 < rangeStart)
	{
		end1 += rangeSize;
	}
}

void Animations::Update()
{
	// TODO Implement ErasePrevFrame() so only the pixels used are modified. Speed bonus x1000 I'll bet.
	Draw(-1);
	UpdatePosition();
	Draw();


}
