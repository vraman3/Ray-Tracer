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

		KDNode* build(std::vector<ObjectClass*>& objs, int depth);
};

KDNode* KDNode::build(std::vector<ObjectClass*>& objs, int depth)
{
	KDNode* node = new KDNode();

	node->objects = objs;
	node->left  = NULL;
	node->right = NULL;
	node->aabbBox = AABBClass();

	// If there are no objects
	if (objs.size() == 0)
		return node;

	// If only one object
	if (objs.size() == 1)
	{
		node->aabbBox = objs[0]->GetBoundingBox();
		node->left  = new KDNode();
		node->right = new KDNode();
		node->left->objects  = std::vector<ObjectClass*>();
		node->right->objects = std::vector<ObjectClass*>();
		return node;
	}

	// For multiple objects get boundingbox for whole scene
	// by getting bounding box for one
	node->aabbBox = objs[0]->GetBoundingBox();
	// and then expand for all the objects
	for (int i = 1; i < objs.size(); i++)
	{
		node->aabbBox.Expand(objs[i]->GetBoundingBox());
	}

	// Get the sum of midpoints of all objects (For now do this for triangles ONLY)
	VectorClass midpoint = VectorClass(0, 0, 0);
	for (int i = 0; i < objs.size(); i++)
	{
		midpoint = midpoint + (objs[i]->GetMidpoint() * (1.0 / objs.size()));
	}

	std::vector<ObjectClass*> left_objs;
	std::vector<ObjectClass*> right_objs;

	// Get the longest axis for the current bounding box and split
	// the objects based on that
	int axis = node->aabbBox.GetLongestAxis();

	for (int i = 0; i < objs.size(); i++)
	{
		switch (axis)
		{	
			// X Axis
			case 0:
				midpoint.GetX() >= objs[i]->GetMidpoint().GetX() ? right_objs.push_back(objs[i]) : left_objs.push_back(objs[i]);
				break;
			// Y Axis
			case 1:
				midpoint.GetY() >= objs[i]->GetMidpoint().GetY() ? right_objs.push_back(objs[i]) : left_objs.push_back(objs[i]);
				break;
			// Z Axis
			case 2:
				midpoint.GetZ() >= objs[i]->GetMidpoint().GetZ() ? right_objs.push_back(objs[i]) : left_objs.push_back(objs[i]);
				break;
		}
	}

	// If one side is empty, make both sides equal to stop subdivision further
	// Since more than 50% of objects will match
	if (left_objs.size() == 0 && right_objs.size() > 0)
	{
		left_objs = right_objs;
	}
	if (right_objs.size() == 0 && left_objs.size() > 0)
	{
		right_objs = left_objs;
	}

	// Check how many objects match
	int matches = 0;
	for (int i = 0; i < left_objs.size(); i++)
	{
		for (int j = 0; j < right_objs.size(); j++)
		{
			if (left_objs[i] == right_objs[i])
				matches++;
		}
	}

	// If more than 50% of objects match, stop subdivision
	// else subdivide further
	if ((float)matches / left_objs.size() < 0.5 && (float)matches / right_objs.size() < 0.5)
	{
		node->left  = build(left_objs, depth + 1);
		node->right = build(right_objs, depth + 1);
	}
	else
	{
		node->left  = new KDNode();
		node->right = new KDNode();
		node->left->objects  = std::vector<ObjectClass*>();
		node->right->objects = std::vector<ObjectClass*>();
	}

	return node;
}