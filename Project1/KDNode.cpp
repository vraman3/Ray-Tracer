#include "KDNode.h"

KDNode::KDNode()
{}

KDNode* KDNode::build(std::vector<TriangleClass*>& objs, int depth)
{
	KDNode* node = new KDNode();
	
	*node = *this;

	node->objects = objs;
	node->left = NULL;
	node->right = NULL;
	//node->aabbBox = AABBClass();

	int objectsSize = objs.size();
	// If there are no objects
	if (objectsSize == 0)
	{
		node->splitAxis = 3;
		return node;
	}

	// If only one object
	if (objectsSize == 1)
	{
		node->aabbBox = AABBClass(objs[0]->GetMinValBBox(), objs[0]->GetMaxValBBox());//objs[0]->GetBoundingBox();
		node->left = new KDNode();
		node->right = new KDNode();
		node->left->objects = std::vector<TriangleClass*>();
		node->right->objects = std::vector<TriangleClass*>();
		node->splitAxis = 3;
		return node;
	}

	// For multiple objects get boundingbox for whole scene
	// by getting bounding box for one
	node->aabbBox = AABBClass(objs[0]->GetMinValBBox(), objs[0]->GetMaxValBBox()); //objs[0]->GetBoundingBox();
	// and then expand for all the objects
	for (int i = 1; i < objectsSize; i++)
	{
		//std::cout << objectsSize << " testExpand ";
		node->aabbBox.Expand(AABBClass(objs[i]->GetMinValBBox(), objs[i]->GetMaxValBBox()));//GetBoundingBox());
	}

	// Get the sum of midpoints of all objects (For now do this for triangles ONLY)
	VectorClass midpoint = VectorClass(0, 0, 0);
	for (int i = 0; i < objectsSize; i++)
	{
		midpoint = midpoint + (objs[i]->GetMidpoint() * (1.0 / objs.size()));
	}

	std::vector<TriangleClass*> left_objs;
	std::vector<TriangleClass*> right_objs;

	// Get the longest axis for the current bounding box and split
	// the objects based on that
	int axis = node->aabbBox.GetLongestAxis();


	for (int i = 0; i < objectsSize; i++)
	{
		switch (axis)
		{
			// X Axis
		case 0: //std::cout << " X ";
			midpoint.GetX() >= objs[i]->GetMidpoint().GetX() ? right_objs.push_back(objs[i]) : left_objs.push_back(objs[i]);
			break;
			// Y Axis
		case 1://std::cout << " Y ";
			midpoint.GetY() >= objs[i]->GetMidpoint().GetY() ? right_objs.push_back(objs[i]) : left_objs.push_back(objs[i]);
			break;
			// Z Axis
		case 2://std::cout << " Z ";
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
	int leftObjSize = (int)left_objs.size();
	int rightObjSize = (int)right_objs.size();

	if (leftObjSize == 0 && rightObjSize > 0)
	{
		//std::cout << " l = r ";
		left_objs = right_objs;
	}
	if (rightObjSize == 0 && leftObjSize > 0)
	{
		//std::cout << " r = l ";
		right_objs = left_objs;
	}

	// Check how many objects match
	int matches = 0;
	for (int i = 0; i < leftObjSize; i++)
	{
		for (int j = 0; j < rightObjSize; j++)
		{
			if (left_objs[i] == right_objs[j])
				matches++;
		}
	}
	//std::cout << matches;
	// If more than 50% of objects match, stop subdivision
	// else subdivide further
	if ((float)matches / leftObjSize < 0.5 && (float)matches / rightObjSize < 0.5)
	{
		node->left = build(left_objs, depth + 1);
		node->right = build(right_objs, depth + 1);
	}
	else
	{
		//std::cout << " hmmm ";
		node->left = new KDNode();
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

intersectionInfo KDNode::Traverse(RayClass ray, intersectionInfo isect)
{
	//
	// Compute initial parametric range of ray inside kd-tree extent
	//
	double tmin, tmax;

	// Not comparing parametric range yet.
	if (this->aabbBox.GetIntersection(ray, &tmin, &tmax) == -1)
	{
		isect.flag = false;
		return isect;
	}
	//
	// End of computing initial parametric range
	//

	//
	// Prepare to traverse kd-tree for ray
	//
#define MAX_TODO 5000
	KDToDo todo[MAX_TODO];
	int todoPos = 0;

	// Add pointer to object that has the least intersection


	//
	// End of preparing to traverse kd-tree for ray
	//

	//
	// Traverse KDTree nodes in order for ray
	//
	//bool hit = false;


	isect.flag = false;																// Initialize isect flag to false for no intersection
	KDNode *nodeT = this;														// ARE YOU SURE?

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
		//std::cout << "Is nodeT NULL?";
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
				|| ((ray.GetRayOrigin()[axis] == nodeT->splitPos) &&
				(ray.GetRayDirection()[axis] >= 0));

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

			/*if (tplane > tmax || tplane <= 0)
			nodeT = firstChild;
			else if (tplane < tmin)
			nodeT = secondChild;
			else*/
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
			//std::cout << noOfPrimitives;
			for (int i = 0; i < noOfPrimitives; i++)
			{
				TriangleClass *prim = nodeT->objects[i];

				//
				// Check one primitive inside leaf node
				//
				double ans = prim->GetIntersection(ray);
				if (ans != -1)
				{
					// Valid intersection exists between object and ray
					//std::cout << ans;
					// Check if another intersection was already found
					if (isect.flag == true)
					{
						// Keep information for object with smaller intersection
						// value, i.e. the closer object
						if (ans < isect.hit)
						{
							isect.tri = prim;
							isect.hit = ans;
							isect.flag = true;
						}
					}
					// First object to intersect with the ray
					else
					{
						isect.tri = prim;
						isect.hit = ans;
						isect.flag = true;
					}
				}
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
	return isect;

	//
	// End of traversing kd-tree in order for ray
	//
}