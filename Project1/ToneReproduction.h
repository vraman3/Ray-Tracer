#pragma once

//Author: Vishwanath Raman
#include "ColourClass.h"
#include "SaveToFIle.h"

class ToneReproduction
{
public:

	ToneReproduction(){}

	ColourClass* WardTP(int, ColourClass*, double, double);
	ColourClass* Reinhard(int, ColourClass *, double, double, double, int, double);
	ColourClass* AdaptiveLogarithmic(int, ColourClass *, double, double, double);
};

