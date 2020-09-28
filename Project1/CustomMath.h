#pragma once
#define _USE_MATH_DEFINES
#include <math.h>


inline double Radians(double deg) {
	return ((double)M_PI / 180) * deg;
}


inline double Degrees(double rad) {
	return (180 / (double)M_PI) * rad;
}