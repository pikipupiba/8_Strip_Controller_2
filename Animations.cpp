#pragma once

#include "Animations.h"



Animations::Animations()
{
}

Animations::~Animations()
{
}

void Animations::UpdatePosition()
{
	hue += hueSpeed;
	hueSpeed += hueAcceleration;

	position += speed;
	speed += acceleration;

	//switch (animationEndOfRange)
	//{
	//case Bounce:

	//	if (position < rangeEnd && position > rangeStart)
	//	{}
	//	else if (position > rangeEnd)
	//	{
	//		position = rangeEnd;
	//		speed = -speed;
	//		if (acceleration > 0)
	//		{
	//			acceleration = -acceleration;
	//		}
	//	}
	//	else if (position < rangeStart)
	//	{
	//		position = rangeStart;
	//		speed = -speed;
	//		if (acceleration < 0)
	//		{
	//			acceleration = -acceleration;
	//		}
	//	}
	//	break;
	//
	//case Continue:

		if (position > rangeEnd)
		{
			position -= rangeSize;
		}
		else if (position < rangeStart)
		{
			position += rangeSize;
		}
//		break;
//	}

	end1 = position - featureSize / 2;
	end2 = position + featureSize / 2;

	if (end2 > rangeEnd)
	{
		end2 -= rangeSize;
	}

	if (end1 < rangeStart)
	{
		end1 += rangeSize;
	}
}

void Animations::Update()
{
}

void Animations::Draw()
{
}
