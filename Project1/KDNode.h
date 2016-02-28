#pragma once

//Author: Vishwanath Raman
#include <iostream>
#include <vector>
#include "ObjectClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"
#include "AABBClass.h"
#include <cmath>

class KDNode
{
	public:
		AABBClass aabbBox;
		KDNode* left;
		KDNode* right;		
		std::vector<ObjectClass*> objects;

		KDNode();

		KDNode* build(std::vector<ObjectClass*>& objs, int depth) const;
};