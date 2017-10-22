/**
	RayTracing, KDNode.h
	Header file to implement KDNode class.

	@author: Vishwanath Raman
	@version: 1.0 Oct/22/2017

*/
#pragma once

#include <iostream>
#include <vector>
#include "ObjectClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"
#include "AABBClass.h"
#include "TriangleClass.h"
#include <cmath>
#include "IntersectionInfo.h"

class KDNode
{
	public:
		/* Variables */
		AABBClass aabbBox;
		KDNode* left;
		KDNode* right;
		int splitAxis;
		double splitPos;

		std::vector<TriangleClass*> objects;

		/* Constructors */
		KDNode();

		/* Methods */
		bool isLeaf();
		intersectionInfo Traverse(RayClass, intersectionInfo);
		KDNode* build(std::vector<TriangleClass*>&, int);

		/* Store info about min td and max td*/
		struct KDToDo
		{
			KDNode *node;
			double tminTD, tmaxTD;
		};
};

