/**
	RayTracing, ToneReproduction.h
	Header file for the ToneReproduction class.

	@author: Vishwanath Raman
	@version: 1.0 Oct/10/2017

*/

#pragma once

#include "ColourClass.h"
#include "SaveToFIle.h"

class ToneReproduction
{
public:
	/* Constructors */
	ToneReproduction(){}


	/* Methods */
	ColourClass* WardTP(int, ColourClass*, double, double);
	ColourClass* Reinhard(int, ColourClass *, double, double, double, int, double);
	ColourClass* AdaptiveLogarithmic(int, ColourClass *, double, double, double);
};

