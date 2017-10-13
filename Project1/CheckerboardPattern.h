/**
	RayTracing, CheckerboardPattern.h
	Header file for the CheckboardPattern class.

	@author: Vishwanath Raman
	@version: 1.0 Oct/12/2017

*/
#pragma once

#include <iostream>

#include "IlluminationClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

//double lerp(double, double, double );
//double dotGridGradient(int, int, double, double);
//double perlinNoise(double, double, double );

class CheckerboardPattern :public IlluminationClass
{
private:
	int width, height;

public:
	/* Constructors */
	CheckerboardPattern(int, int, double, double);

	/* Methods */
	ColourClass getIllumination(VectorClass pi, RayClass ray, VectorClass normal, VectorClass lightRay, VectorClass viewerRay, ColourClass objColour, ColourClass pointCol, int maxDepth);
};

