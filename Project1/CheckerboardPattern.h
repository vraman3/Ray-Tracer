#pragma once

//Author: Vishwanath Raman
#include <iostream>

#include "IlluminationClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

double lerp(double, double, double );
double dotGridGradient(int, int, double, double);
double PerlinNoise(double, double, double );

class CheckerboardPattern :public IlluminationClass
{
private:
	int width, height;

public:
	CheckerboardPattern(int, int, double, double);
	ColourClass GetIllumination(VectorClass, RayClass, VectorClass, VectorClass, VectorClass, ColourClass, ColourClass, int);
};

