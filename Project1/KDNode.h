#pragma once

//Author: Vishwanath Raman
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
		AABBClass aabbBox;
		KDNode* left;
		KDNode* right;
		int splitAxis;
		double splitPos;

		std::vector<TriangleClass*> objects;

		KDNode();
		bool isLeaf();
		intersectionInfo Traverse(RayClass, intersectionInfo);
		KDNode* build(std::vector<TriangleClass*>&, int);

		struct KDToDo
		{
			KDNode *node;
			double tminTD, tmaxTD;
		};
};

