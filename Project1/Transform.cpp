/**
RayTracing, Transform.cpp
Class to implement the different Transformations.

@author: Vishwanath Raman
@version: 1.0 March/18/2018

*/
#pragma once

#include "Transform.h"
#include "Matrix4x4.h"
#include "CustomMath.h"

/**
	Default constructor
*/
Transform::Transform()
{

}

/**
	Parameterized constructor that takes in a 4x4 array and sets it to
	the transform matrix(m4x4) and also calculates it's inverse(mInv) and stores it.

	@param mat:	The 4x4 double array.
*/
Transform::Transform(double mat[4][4])
{
	m4x4 = Matrix4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3],
		mat[1][0], mat[1][1], mat[1][2], mat[1][3],
		mat[2][0], mat[2][1], mat[2][2], mat[2][3],
		mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
	mInv = m4x4.Inverse();
}

/**
	Parameterized constructor that takes in a Matrix4x4 and sets it to
	the transform matrix(m4x4) and also calculates it's inverse(mInv) and stores it.

	@param mat:	The Matrix4x4 object.
*/
Transform::Transform(Matrix4x4 &mat): m4x4(mat), mInv(m4x4.Inverse())
{}

/**
	Parameterized constructor that takes in a Matrix4x4 and it's inverse and 
	sets it to the transform matrix(m4x4) and it's inverse(mInv) respectively.

	@param mat:	The Matrix4x4 object.
	@param matInv: The inverse matrix of 'mat'.
*/
Transform::Transform(Matrix4x4 &mat, Matrix4x4 matInv): m4x4(mat), mInv(matInv)
{}

/**
	Getter function to get the current transformation matrix.

	@return	Returns the transformation matrix as a Matrix4x4.
*/
Matrix4x4& Transform::GetMatrix() 
{
	return m4x4;
}

/**
	Getter function to get the inverse of the current transformation matrix.

	@return	Returns the inverse as a Matrix4x4.
*/
Matrix4x4& Transform::GetInverseMatrix()
{ 
	return mInv;
}

/**
	Deprecated. Do not use.
*/
Transform Transform::GetInverse()
{
	return Transform(mInv, m4x4);
}

/**
	Transformation matrix for translation given by VectorClass delta.

	@param delta: The x, y, and z values for translation on the
				  corresponding axes.
	@return Returns the given point after applying the Translation transformation.
*/
Transform Transform::Translate(VectorClass& delta)
{
	Matrix4x4 mT(1, 0, 0, delta.getX(),
				0, 1, 0, delta.getY(),
				0, 0, 1, delta.getZ(),
				0, 0, 0,		1   );

	Matrix4x4 mInvT(1, 0, 0, -delta.getX(),
					0, 1, 0, -delta.getY(),
					0, 0, 1, -delta.getZ(),
					0, 0, 0, 1);

	return Transform(mT, mInvT);
}

/**
	Transformation matrix for scaling given by scale factors x, y, and z.

	@param x: The scale factor for the x axis.
	@param y: The scale factor for the y axis.
	@param z: The scale factor for the z axis.
	@return Returns the given point after applying the Scaling transformation.
*/
Transform Transform::Scale(double x, double y, double z)
{
	Matrix4x4 mS(x, 0, 0, 0,
				 0, y, 0, 0,
				 0, 0, z, 0,
				 0, 0, 0, 1);

	Matrix4x4 mInvS(1/x, 0, 0, 0,
					0, 1/y, 0, 0,
					0, 0, 1/z, 0,
					0, 0, 0, 1);

	return Transform(mS, mInvS);
}

/**
	Transformation matrix to rotate around the x axis by
	given angle (in Radians).

	@param angle: The angle in Radians.
	@return The Transform to rotate about the x axis by the given angle.
*/
Transform Transform::RotateX(double angle)
{
	double sin_t = sin(Radians(angle));
	double cos_t = cos(Radians(angle));

	Matrix4x4 mRotateX(	1,		0,	0,		0,
						0,	cos_t, -sin_t,	0,
						0,	sin_t, cos_t,	0,
						0,		0,	0,		1);

	return Transform(mRotateX, mRotateX.Transpose());
}

/**
	Transformation matrix to rotate around the y axis by
	given angle (in Radians).

	@param angle: The angle in Radians.
	@return The Transform to rotate about the y axis by the given angle.
*/
Transform Transform::RotateY(double angle)
{
	double sin_t = sin(Radians(angle));
	double cos_t = cos(Radians(angle));

	Matrix4x4 mRotateY(	cos_t,	0,	sin_t,	0,
						0,		1,	0,		0,
						-sin_t, 0,	cos_t,	0,
						0,		0,	0,		1);

	return Transform(mRotateY, mRotateY.Transpose());
}

/**
	Transformation matrix to rotate around the z axis by
	given angle (in Radians).

	@param angle: The angle in Radians.
	@return The Transform to rotate about the z axis by the given angle.
*/
Transform Transform::RotateZ(double angle)
{
	double sin_t = sin(Radians(angle));
	double cos_t = cos(Radians(angle));

	Matrix4x4 mRotateZ(	cos_t, -sin_t,  0,	0,
						sin_t,  cos_t,  0,	0,
						0,		0,		1,	0,
						0,		0,		0,	1);

	return Transform(mRotateZ, mRotateZ.Transpose());
}

/**
	INCOMPLETE
	Transformation matrix to rotate around an arbitrary axis by the 
	given angle (in Radians).

	@param angle: The angle in Radians.
	@param axis: The arbitrary axis to rotate around.
	@return The Transform to rotate about the given axis by the given angle.
*/
Transform Transform::Rotate(double angle, VectorClass& axis)
{
	return Transform();
}

/**
	Matrix to calculate the LookAt matrix to convert from camera space to 
	world space.

	@param pos: The position or origin of the camera.
	@param look: The direction the camera is looking at.
	@param up: The up vector of the camera.
	@return The Transform to convert from camera space to world space.
*/
Transform Transform::LookAt(VectorClass& pos, VectorClass& look, VectorClass& up)
{
	double m[4][4];

	m[0][3] = pos.getX();
	m[1][3] = pos.getY();
	m[2][3] = pos.getZ();
	m[3][3] = 1;

	// The direction vector is the z axis. Camera space is usually defined with the viewing direction looking down the +z axis.
	VectorClass dir = (look - pos).normalize();

	if (up.normalize().crossProd(dir).magnitude() == 0)
	{
		std::cout<< " up vector and viewing direction passed to LookAt are pointing in the same direction. Using the identity transformation. " 
				<< "up: " << up.getX() << " " << up.getY() << " " << up.getZ() << "dir: "
				<< dir.getX() << " " << dir.getY() << " " << dir.getZ() << std::endl;
		/*Error("\"up\" vector (%f, %f, %f) and viewing direction (%f, %f, %f) "
			"passed to LookAt are pointing in the same direction.  Using "
			"the identity transformation.", up.x, up.y, up.z, dir.x, dir.y,
			dir.z);*/
		return Transform();
	}

	// The cross product of the calculated direction vector and user given up vector (normalized)
	// gives the world space direction that the +x axis in camera space maps to.
	VectorClass right	 = dir.crossProd(up.normalize());

	// The up vector is re calculated to ensure that the y and z axes are perpendicular.
	VectorClass upRecalc = right.crossProd(dir);

	m[0][0] = right.getX();
	m[1][0] = right.getY();
	m[2][0] = right.getZ();
	m[3][0] = 0;

	m[0][1] = upRecalc.getX();
	m[1][1] = upRecalc.getY();
	m[2][1] = upRecalc.getZ();
	m[3][1] = 0;

	m[0][2] = dir.getX();
	m[1][2] = dir.getY();
	m[2][2] = dir.getZ();
	m[3][2] = 0;

	Matrix4x4 camToWorld(m);

	return Transform(camToWorld.Inverse(), camToWorld);
}

/**
	Operator overloading.
	Use the current transform to transform a point.

	@param point: The point to be transformed.
	@param intPoint: To designate the current VectorClass is a point.
	@return The transformed point as a VectorClass.
*/
VectorClass Transform::operator()(VectorClass& point, int intPoint)
{

	double x = point.getX();
	double y = point.getY();
	double z = point.getZ();

	// The incoming Point is expressed in homogeneous column vector [x y z 1]^T.
	// Then the Point is transformed by premultiplying that column vector by the
	// transformation matrix.
	double xp = m4x4.matArray[0][0] * x + m4x4.matArray[0][1] * y + m4x4.matArray[0][2] * z + m4x4.matArray[0][3];
	double yp = m4x4.matArray[1][0] * x + m4x4.matArray[1][1] * y + m4x4.matArray[1][2] * z + m4x4.matArray[1][3];
	double zp = m4x4.matArray[2][0] * x + m4x4.matArray[2][1] * y + m4x4.matArray[2][2] * z + m4x4.matArray[2][3];
	double wp = m4x4.matArray[3][0] * x + m4x4.matArray[3][1] * y + m4x4.matArray[3][2] * z + m4x4.matArray[3][3];

	if (wp == 0)
		std::cout << "wp = 0" << std::endl;

	// Divide by wp to convert back to non-homogeneous Point representation.
	if (wp == 1.0)
		return VectorClass(xp, yp, zp);

	return VectorClass(xp, yp, zp)/wp;
}

/**
	Operator overloading.
	Use the current transform to transform a point, when also given
	the pointer to the point to store the result in.

	@param point: The point to be transformed.
	@param pOut: The pointer to the VectorClass for storing the transformed 
				 point.
	@param intPoint: Int to designate the current VectorClass is a Point.
*/
void Transform::operator()(VectorClass& point, VectorClass *pOut, int intPoint)
{
	double x = point.getX();
	double y = point.getY();
	double z = point.getZ();

	pOut->setX( m4x4.matArray[0][0] * x + m4x4.matArray[0][1] * y + m4x4.matArray[0][2] * z );
	pOut->setY( m4x4.matArray[1][0] * x + m4x4.matArray[1][1] * y + m4x4.matArray[1][2] * z );
	pOut->setZ( m4x4.matArray[2][0] * x + m4x4.matArray[2][1] * y + m4x4.matArray[2][2] * z );
	double wp = m4x4.matArray[3][0] * x + m4x4.matArray[3][1] * y + m4x4.matArray[3][2] * z ;

	if (wp != 1.0)
		*pOut = *pOut/wp;
}

/**
	Operator overloading.
	Use the current transform to transform a vector.

	@param vec: The vector to be transformed.
	@return The transformed vector as a VectorClass.
*/
VectorClass Transform::operator()(VectorClass& vec)
{
	double x = vec.getX();
	double y = vec.getY();
	double z = vec.getZ();

	double xp = m4x4.matArray[0][0] * x + m4x4.matArray[0][1] * y + m4x4.matArray[0][2] * z + m4x4.matArray[0][3];
	double yp = m4x4.matArray[1][0] * x + m4x4.matArray[1][1] * y + m4x4.matArray[1][2] * z + m4x4.matArray[1][3];
	double zp = m4x4.matArray[2][0] * x + m4x4.matArray[2][1] * y + m4x4.matArray[2][2] * z + m4x4.matArray[2][3];

	return VectorClass(xp, yp, zp);
}

/**
	Operator overloading.
	Use the current transform to transform a vector, when also given
	the pointer to the VectorClass to store the result in.

	@param vec: The vector to be transformed.
	@param vecOut: The pointer to the VectorClass where the transformed
				   vector will be stored.
*/
void Transform::operator()(VectorClass& vec, VectorClass* vecOut)
{
	double x = vec.getX();
	double y = vec.getY();
	double z = vec.getZ();

	vecOut->setX( m4x4.matArray[0][0] * x + m4x4.matArray[0][1] * y + m4x4.matArray[0][2] * z + m4x4.matArray[0][3] );
	vecOut->setY( m4x4.matArray[1][0] * x + m4x4.matArray[1][1] * y + m4x4.matArray[1][2] * z + m4x4.matArray[1][3] );
	vecOut->setZ( m4x4.matArray[2][0] * x + m4x4.matArray[2][1] * y + m4x4.matArray[2][2] * z + m4x4.matArray[2][3] );
}

/**
	Operator overloading.
	Use the current transform to transform a normal.

	@param normal: The normal to be transformed.
	@param fNormal: The float value to indicate the current VectorClass 
					is a normal.
	@return The transformed normal as a VectorClass.
*/
VectorClass Transform::operator()(VectorClass& normal, float fNormal)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//			Normal n, tangent vector t on the surface are orthogonal by construction.				//
	//																									//
	//			DotProd(n, t) = n^T * t = 0;															//
	//																									//
	//		Transforming a point by a matrix M, the new tangent vector t' at transformed point is Mt.	//
	//		The transformed normal n' should be S*n for some matrix S.									//
	//		Since	n^T * t = 0;																		//
	//			(n')^T * t' = 0;																		//
	//			(Sn)^T * Mt = 0;																		//
	//			n^T * S^T * M * t = 0;																	//
	//																									//
	//			So this will hold true only if S^T * M = I												//
	//			So S^T = Minv																			//
	//			So S = Minv^T;																			//
	//																									//
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	double x = normal.getX();
	double y = normal.getY();
	double z = normal.getZ();

	return VectorClass(mInv.matArray[0][0] * x + mInv.matArray[1][0] * y + mInv.matArray[2][0] * z,
					 mInv.matArray[0][1] * x + mInv.matArray[1][1] * y + mInv.matArray[2][1] * z, 
					 mInv.matArray[0][2] * x + mInv.matArray[1][2] * y + mInv.matArray[2][2] * z );
}

/**
	Operator overloading.
	Use the current transform to transform a normal, when given the pointer
	to the VectorClass to store the transformed normal.

	@param normal: The normal to be transformed.
	@param normalOut: Pointer to the VectorClass where the transformed
					  normal will be stored.
	@param fNormal: The float value to indicate the current VectorClass
					is a normal.
*/
void Transform::operator()(VectorClass& normal, VectorClass* normalOut, float fNormal)
{
	double x = normal.getX();
	double y = normal.getY();
	double z = normal.getZ();

	normalOut->setX(mInv.matArray[0][0] * x + mInv.matArray[1][0] * y + mInv.matArray[2][0] * z);
	normalOut->setY(mInv.matArray[0][1] * x + mInv.matArray[1][1] * y + mInv.matArray[2][1] * z);
	normalOut->setZ(mInv.matArray[0][2] * x + mInv.matArray[1][2] * y + mInv.matArray[2][2] * z);

}

/**
	Operator overloading.
	Use the current transform to transform a ray.

	@param ray: The ray to be transformed.
	@return The transformed ray as a RayClass.
*/
RayClass Transform::operator()(RayClass& ray)
{
	// Origin is a 'Point' and direction is a 'VectorClass'. So should be
	// transformed accordingly.
	RayClass retRay(	(*this)(ray.GetRayOrigin(), 1	) , 
						(*this)(ray.GetRayDirection()	)	);

	retRay.minT = ray.minT;
	retRay.maxT = ray.maxT;

	return retRay;
}

/**
	Operator overloading.
	Use the current transform to transform a ray, when given the pointer
	to the RayClass to store the transformed ray.

	@param ray: The ray to be transformed.
	@param rayOut: Pointer to the RayClass where the transformed
					ray will be stored.
*/
void Transform::operator()(RayClass& ray, RayClass* rayOut)
{
	// Transform like a Point.
	rayOut->SetRayOrigin(	 (*this)(ray.GetRayOrigin(),	1	));

	// Transform like a Vector.
	rayOut->SetRayDirection( (*this)(ray.GetRayDirection()	));

	if (rayOut != &ray) {
		rayOut->minT = ray.minT;
		rayOut->maxT = ray.maxT;
	}
}

/**
	Operator overloading.
	Use the current transform to transform an axis aligned bounding box(AABB).

	@param box: The normal to be transformed.
	@return The transformed AABB.
*/
AABBClass Transform::operator()(AABBClass& box)
{
	Transform &curr = *this;

	// Apply the transformation on each of the eight corners of the bounding box.
	AABBClass retBox(curr(VectorClass(box.getbMin().getX(), box.getbMin().getY(), box.getbMin().getZ()), 1));

	retBox.Expand(curr(VectorClass(box.getbMax().getX(), box.getbMin().getY(), box.getbMin().getZ())));
	retBox.Expand(curr(VectorClass(box.getbMin().getX(), box.getbMax().getY(), box.getbMin().getZ())));
	retBox.Expand(curr(VectorClass(box.getbMin().getX(), box.getbMin().getY(), box.getbMax().getZ())));
	retBox.Expand(curr(VectorClass(box.getbMin().getX(), box.getbMax().getY(), box.getbMax().getZ())));
	retBox.Expand(curr(VectorClass(box.getbMax().getX(), box.getbMax().getY(), box.getbMin().getZ())));
	retBox.Expand(curr(VectorClass(box.getbMax().getX(), box.getbMin().getY(), box.getbMax().getZ())));
	retBox.Expand(curr(VectorClass(box.getbMax().getX(), box.getbMax().getY(), box.getbMax().getZ())));

	return retBox;
}

/**
	Multiply two transformation matrices. The first matrix is the current
	transform, which is post-multiplied with the second transform matrix (t2).

	@param	t2: The second transform matrix for post multiplication with
				the current transform matrix.
	@return the result of the multiplication as a a new Transform.
*/
Transform Transform::operator*(Transform & t2)
{
	//////////////////////////////////////
	//									//
	//		(AB)^-1 = B^-1 * A^-1		//
	//		(AB)inv = Binv * Ainv		//
	//									//
	//////////////////////////////////////

	Matrix4x4 newM = m4x4.Mul(t2.m4x4);
	Matrix4x4 newMinv = t2.mInv.Mul(mInv);
	return Transform();
}

/**
	Checks if a transformation changes handedness.

	@return Returns true if the current Transform changes handedness,
			otherwise returns false.
*/
bool Transform::SwapsHandedness()
{
	//////////////////////////////////////////////////////////////////////////////
	/*																			//
	//	Handedness is changed by a transformation only when the determinant		//
	//	of the transformation's upper-left 3x3 sub-matrix is negative.			//
	//																			//
	//		[a  b  c]	[00  01  02]											//
	//	A = [d  e  f] = [10  11  12]											//
	//		[g  h  i]	[20  21  22]											//
	//																			//
	//			|e  f|     |d  f|     |d  e|									//
	//	|A| = a.|h  i| - b.|g  i| + c.|g  h|									//
	//																			//
	//	|A| =  a*(e * i - f * h) -  b*(d * i - f * g) +  c*(d * h - e * g)		//
	//																			//
	//	|A| = 00*(11*22 - 12*21) - 01*(10*22 - 12*20) + 02*(10*21 - 11*20)		//
	//																			//
	//																			*/
	//////////////////////////////////////////////////////////////////////////////

	double firstTerm	= m4x4.matArray[0][0] * (m4x4.matArray[1][1] * m4x4.matArray[2][2] - m4x4.matArray[1][2] * m4x4.matArray[2][1]);
	double secondTerm	= m4x4.matArray[0][1] * (m4x4.matArray[1][0] * m4x4.matArray[2][2] - m4x4.matArray[1][2] * m4x4.matArray[2][0]);
	double thirdTerm	= m4x4.matArray[0][2] * (m4x4.matArray[1][0] * m4x4.matArray[2][1] - m4x4.matArray[1][1] * m4x4.matArray[2][0]);

	double determinant = firstTerm - secondTerm + thirdTerm;

	return determinant < 0.0;
}
