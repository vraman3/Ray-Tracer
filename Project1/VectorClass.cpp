/**
	RayTracing, VectorClass.h
	Class file for direction vector class

	@author: Vishwanath Raman
	@version: 1.0 Oct/07/2017

*/

#include "VectorClass.h"

#include <stdexcept>

/**
	Operator overload for [] to return corresponding dimension.

	@param dimension: The dimension to be returned.
	@return the dimenion, if valid, is returned.
*/
double VectorClass::operator[](const int dimension) const
{
	switch (dimension)
	{
	case 0: return x;
		break;

	case 1: return y;
		break;

	case 2: return z;
		break;

	default: throw std::invalid_argument("Invalid dimension for vector");;
		break;
	}
}

/**
	Operator overload for adding (+) two VectorClasses.

	@param b: The VectorClass to be added to the first.
	@return the addition of both VectorClasses, as a VectorClass.
*/
VectorClass VectorClass::operator+(const VectorClass& b) const
{
	return VectorClass(this->x + b.x, this->y + b.y, this->z + b.z);
}

/**
	Operator overload for VectorClass subtraction (-).

	@param b: The VectorClass to be subtracted from the first.
	@return the subtraction of both VectorClasses, as a VectorClass.
*/
VectorClass VectorClass::operator-(const VectorClass& b) const
{
	return VectorClass(this->x - b.x, this->y - b.y, this->z - b.z);
}

/**
	Operator overload for multiplying (*) two VectorClasses.
	
	@param b: The VectorClass to be multiplied with the first.
	@return the multiplication of both VectorClasses, as a VectorClass.
*/
VectorClass VectorClass::operator*(const VectorClass& b) const
{
	return VectorClass(this->x * b.x, this->y * b.y, this->z * b.z);
}

/**
	Operator overload for multiplying (*) a VectorClass with an integer constant.

	@param b: The constant to be multiplied with the VectorClass.
	@return the multiplication of the VectorClass with the integer constant, as a VectorClass.
*/
VectorClass VectorClass::operator*(const double b) const
{
	return VectorClass(this->x * b, this->y * b, this->z * b);
}

/**
	Operator overload for division (/) of a VectorClass by an integer constant.

	@param b: The divisor as an integer constant.
	@return the result of the division, as a VectorClass.
*/
VectorClass VectorClass::operator/(const double b) const
{
	return VectorClass(this->x / b, this->y / b, this->z / b);
}

/**
	Default constructor.

	@return A new initialized VectorClass object.
*/
VectorClass::VectorClass()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

/**
	Parameterized constructor.

	@return A new initialized VectorClass with the given parameters.
*/
VectorClass::VectorClass(double i, double j, double k)
{
	x = i;
	y = j;
	z = k;
}

/**
	Get the value of 'x' or first dimension of a VectorClass.

	@return the value of 'x' of a VectorClass.
*/
double VectorClass::GetX()
{
	return x;
}

/**
	Get the value of 'y' or second dimension of a VectorClass.

	@return the value of 'y' of a VectorClass.
*/
double VectorClass::GetY()
{
	return y;
}

/**
	Get the value of 'z' or third dimension of a VectorClass.

	@return the value of 'z' of a VectorClass.
*/
double VectorClass::GetZ()
{
	return z;
}

/**
	Set the value of 'x' or first dimension of a VectorClass.

	@param val: The value of 'x' to be set.
*/
void VectorClass::SetX(double val)
{
	x = val;
}

/**
	Set the value of 'y' or second dimension of a VectorClass.

	@param val: The value of 'y' to be set.
*/
void VectorClass::SetY(double val)
{
	y = val;
}

/**
	Set the value of 'z' or third dimension of a VectorClass.

	@param val: The value of 'z' to be set.
*/
void VectorClass::SetZ(double val)
{
	z = val;
}

/**
	Get the magnitude of the VectorClass.

	@return the magnitude of the VectorClass.
*/
double VectorClass::Magnitude()
{
	double temp = x*x + y*y + z*z;
	return sqrt(temp);

}

/**
	Calculate the dot product of two VectorClasses.

	@param the second VectorClass for the dot product.
	@return the dot product of the two VectorClasses.
*/
double VectorClass::DotProd(VectorClass temp)
{
	return x * temp.GetX() + y * temp.GetY() + z * temp.GetZ();
}

/**
	Calculate the cross product of two VectorClasses.

	@param the second VectorClass for the cross product.
	@return the cross product of the two VectorClasses.
*/
VectorClass VectorClass::CrossProd(VectorClass temp)
{
	return VectorClass(y*temp.GetZ() - z*temp.GetY(), z*temp.GetX() - x*temp.GetZ(), x*temp.GetY() - y*temp.GetX());
}

/**
	Normalize a VectorClass i.e. Divide each element by the magnitude
	of the VectorClass.

	@return the normalized VectorClass.
*/
VectorClass VectorClass::Normalize()
{
	double value = sqrt(x*x + y*y + z*z);
	return VectorClass(x / value, y / value, z / value);
}