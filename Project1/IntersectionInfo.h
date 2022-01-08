/**
	RayTracing, IntersectionInfo.h
	Header file to implement the intersectionInfo struct.

	@author: Vishwanath Raman
	@version: 1.0 Oct/13/2017

*/
#pragma once

#include "TriangleClass.h"

//
struct intersectionInfo
{
	TriangleClass *tri;
	double hit;
	bool flag;
};