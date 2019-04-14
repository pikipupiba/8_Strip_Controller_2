#include "PatternClass.h"


PatternClass::PatternClass(CRGBSet* leds)
{
    PatternClass::leds = leds;
    
    curPattern = 0;
}

PatternClass::~PatternClass()
{
}

void PatternClass::Update()
{
    hue += hueSpeed;
    position += speed;
    
    patterns[curPattern](leds);
}