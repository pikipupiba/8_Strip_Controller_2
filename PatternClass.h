#pragma once
#include "globalStuff.h"
#include "display.h"

class PatternClass
{
private:

	typedef void(PatternClass::*Pattern)();

	typedef struct {
		Pattern pattern;
		bool active;
	} ActivePattern;

	typedef ActivePattern ActivePatternList[2];

	ActivePatternList patterns = {
		{ &PatternClass::PoopyWorm1,	true },
		{ &PatternClass::PoopyWorm2,	true }
	};

public:
	PatternClass();
	~PatternClass();

	void PoopyWorm1();
	void PoopyWorm2();
};

