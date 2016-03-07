#pragma once

#include "TriangleClass.h"

struct intersectionInfo
{
	TriangleClass *tri;
	double hit;
	bool flag;
};