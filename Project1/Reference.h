/**
RayTracing, Reference.h
Header file for Reference class.

Taken from/Based on the PBRT book by Matt Pharr and Greg Humphreys.

@author: Vishwanath Raman
@version: 1.0 Mar/18/2018

*/

#pragma once

template <class T> class Reference
{
private:
	T * ptr;

public:
	/* Constructors */

	/**
		Parameterized constructor that takes in an object.

		@param p:	Pointer to a template object.
	*/
	Reference(T *p = NULL)
	{
		// Assign current Reference object to point to new
		// template object(p)
		ptr = p;

		// If ptr does not point to NULL, increase the count
		// of pointers pointing to the object.
		if (ptr)
			++ptr->nReferences;
	}

	/**
		Constructor that takes in another Reference.
	*/
	Reference(const Reference<T> &r)
	{
		// Assign current Reference object to point to the
		// template object new
		// Reference object.
		ptr = r.ptr;

		// If ptr does not point to NULL, increase the count
		// of pointers pointing to the object.
		if (ptr)
			++ptr->nReferences;
	}

	/**
		Default Destructor
	*/
	~Reference()
	{
		// Check if the current Reference object going out of scope points
		// to something, i.e. is not NULL and is the ONLY pointer to point
		// to an object. If it is, then delete the ptr, which will free
		// the memory.
		if (ptr && --ptr->nReferences == 0)
			delete ptr;
	}

	/**
		Operator overloading for assignment from another Reference.

		@param	&newReference: The new Reference object being assigned.
		@return Return the address of the current updated Reference.
	*/
	Reference& operator=(const Reference<T> &newReference)
	{
		// Check the Reference being assigned, i.e. newReference, if it
		// exists and is not NULL; and then increment it's nReferences
		// count since it will have another pointer, which is the current
		// pointer,  pointing to it.
		if (newReference.ptr)
			newReference.ptr->nReferences++;

		// Check if the old pointer that is being assigned a new value,
		// ptr, is not NULL and is the ONLY pointer to point to an object.
		// If it is, then delete the ptr, which will free the memory.
		if (ptr && --ptr->nReferences == 0)
			delete ptr;

		// Assign the new value to ptr.
		ptr = newReference.ptr;

		// Return the current Reference object.
		return *this;
	}

	/**
		Operator overloading for assignment from another template object.

		@param	&newObject: The new template object being assigned.
		@return Return the address of the current updated Reference.
	*/
	Reference& operator=(T *newObject)
	{
		// Check the new object being assigned, i.e. newObject, if it
		// exists and is not NULL; and then increment it's nReferences
		// count since it will have another pointer, which is the current
		// pointer, pointing to it.
		if (newObject)
			newObject->nReferences++;

		// Check if the old pointer that is being assigned a new value,
		// ptr, is not NULL and is the ONLY pointer to point to an object.
		// If it is, then delete the ptr, which will free the memory.
		if (ptr && --ptr->nReferences == 0)
			delete ptr;

		// Assign the new value to ptr.
		ptr = newObject;

		// Return the current Reference object.
		return *this;
	}

};