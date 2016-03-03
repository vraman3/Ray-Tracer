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
		bool Traverse(RayClass ray);
		KDNode* build(std::vector<TriangleClass*>& objs, int depth);

		struct KDToDo
		{
			KDNode *node;
			float tminTD, tmaxTD;
		};
};

KDNode::KDNode()
{}

KDNode* KDNode::build(std::vector<TriangleClass*>& objs, int depth)
{
	KDNode* node = new KDNode();

	node->objects = objs;
	node->left  = NULL;
	node->right = NULL;
	node->aabbBox = AABBClass();

	// If there are no objects
	if (objs.size() == 0)
	{
		node->splitAxis = 3;
		return node;
	}

	// If only one object
	if (objs.size() == 1)
	{
		node->aabbBox = objs[0]->GetBoundingBox();
		node->left  = new KDNode();
		node->right = new KDNode();
		node->left->objects = std::vector<TriangleClass*>();
		node->right->objects = std::vector<TriangleClass*>();
		node->splitAxis = 3;
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

	std::vector<TriangleClass*> left_objs;
	std::vector<TriangleClass*> right_objs;

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

	// Assign the splitAxis for the current node and the position where it was
	// split
	node->splitAxis = axis;
	if (axis == 0)
		node->splitPos = midpoint.GetX();
	else if (axis == 1)
		node->splitPos = midpoint.GetY();
	else if (axis == 2)
		node->splitPos = midpoint.GetZ();

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
		node->left->objects = std::vector<TriangleClass*>();
		node->right->objects = std::vector<TriangleClass*>();
		node->splitAxis = 3;

	}

	return node;
}

bool KDNode::isLeaf()
{
	if (this->splitAxis == 3)
		return true;
	else
		return false;
}

bool KDNode::Traverse(RayClass ray)
{
	//
	// Compute initial parametric range of ray inside kd-tree extent
	//
	double tmin, tmax;

	// Not comparing parametric range yet.
	if (!this->aabbBox.GetIntersection(ray, &tmin, &tmax))
		return false;

	//
	// End of computing initial parametric range
	//

	//
	// Prepare to traverse kd-tree for ray
	//
	#define MAX_TODO 64
	KDToDo todo[MAX_TODO];
	int todoPos = 0;

	//
	// End of preparing to traverse kd-tree for ray
	//

	//
	// Traverse KDTree nodes in order for ray
	//
	bool hit = false;

	KDNode *nodeT = &this[0];														// ARE YOU SURE?

	// while loop for traversing all required nodes in kd-tree
	while (nodeT != NULL)
	{
		//
		// Bail out if we found a hit closer than the current node
		//
		if (ray.maxT < tmin) break;
		//
		// End of bail out if we find a closer hit
		//

		if (!nodeT->isLeaf())
		{
			//
			// Process kd-tree interior node
			//

			//
			// Compute the parametric distance along ray to split
			// plane

			int axis = nodeT->splitAxis;
			double tplane = (nodeT->splitPos - ray.GetRayOrigin()[axis]) * ray.GetRayInvDirection()[axis];
			//
			// End of computing parametric distance along ray
			//

			//
			// Get node children pointers for ray
			//
			KDNode *firstChild, *secondChild;

			int belowFirst = (ray.GetRayOrigin()[axis] < nodeT->splitPos)
				|| ( (ray.GetRayOrigin()[axis] == nodeT->splitPos) && 
					 (ray.GetRayDirection()[axis] >= 0 ) );

			if (belowFirst)
			{
				firstChild = nodeT->left;
				secondChild = nodeT->right;
			}
			else
			{
				firstChild = nodeT->right;
				secondChild = nodeT->left;
			}
			//
			// End of node children pointers for ray
			//

			//
			// Advance to next child node, possibly enqueue other child
			//

			if (tplane > tmax || tplane <= 0)
				nodeT = firstChild;
			else if (tplane < tmin)
				nodeT = secondChild;
			else
			{
				//
				// Enqueue secondChild in todo list
				//
				todo[todoPos].node = secondChild;
				todo[todoPos].tminTD = tplane;
				todo[todoPos].tmaxTD = tmax;
				++todoPos;
				//
				// End of enqueueing secondChild in todo list
				//

				nodeT = firstChild;
				tmax = tplane;
			}
			//
			// End of advance to next child node, possibly enqueue other child
			//
		}
		//
		// End of process kd-tree interior node
		//		( and the if block )
		else
		{
			//
			// Check for intersections inside leaf node
			//

			// In this program, it will be only triangles as primitives yet.
			int noOfPrimitives = nodeT->objects.size();

			for (int i = 0; i < noOfPrimitives; i++)
			{
				TriangleClass *prim = nodeT->objects[i];

				//
				// Check one primitive inside leaf node
				//
				if (prim->GetIntersection(ray))
					hit = true;
				//
				// End of checking one primitive inside leaf node
				//
			}
			//
			// End of checking for intersection inside leaf node
			//

			//
			// Grab next node to process from todo list
			//
			if (todoPos > 0)
			{
				--todoPos;
				nodeT = todo[todoPos].node;
				tmin = todo[todoPos].tminTD;
				tmax = todo[todoPos].tmaxTD;
			}
			else
				break;
			//
			// End of grabbing next node to process from todo list
			//
		}
	}
	return hit;

	//
	// End of traversing kd-tree in order for ray
	//
}