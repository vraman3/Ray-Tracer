/**
	RayTracing, Tracing.h
	Header file for class Tracing.

	@author: Vishwanath Raman
	@version: 1.0 Oct/23/2017

*/
#pragma once

#include "ColourClass.h"
#include "IlluminationClass.h"
#include "KDNode.h"
#include "ObjectClass.h"
#include "RayClass.h"

#include <vector>
class Tracing
{
public:
	/* Constructors */
	Tracing();

	/* Methods */
	ColourClass TraceRay_debug(RayClass ray, int depth, double incomingni, std::vector<ObjectClass*> objects, std::vector<VectorClass*> lights,
		ColourClass background, ColourClass pointCol, int maxDepth);


	ColourClass TraceRay_rt1w(RayClass ray_d, std::vector<ObjectClass*> objects_d);
	bool TraceRay_rt1w_helper(RayClass ray_d, std::vector<ObjectClass*> objects_d, double tMin_d, double tMax_d, intersection_record &rec_d);

	ColourClass TraceRay(RayClass ray, int depth, double incomingni, std::vector<TriangleClass*> objects, std::vector<VectorClass*> lights,
		ColourClass background, ColourClass pointCol, int maxDepth);

	ColourClass TraceRayKD(RayClass, int, double, KDNode kdtree, std::vector<VectorClass*>,
						   ColourClass, ColourClass, int);
};