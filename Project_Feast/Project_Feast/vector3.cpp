#include "Vector3.h"
#include <iostream>
using namespace std;


/** Default constructor.\n
*	Produces an empty Vector3.\n
*	Its values are set to 0.
*/
Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

/** Input constructor.\n
*	Creates a Vector3 based on input parameters.
*	@param x The x component of the vector.
*	@param y The y component of the vector.
*	@param z The z component of the vector.
*/
Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

/** Copy constructor.\n
*	Creates a new Vector3 based on an existing one.
*	@param rhs The vector whose values will be copied.
*/
Vector3::Vector3(const Vector3& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}

/** Overloaded += operator.\n
*	Allows one vector to be added to another and the result is stored in the first.
*	@param v The vector we will add to the original.
*/
void Vector3::operator+= (const Vector3 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

/** Overloaded -= operator.\n
*	Allows one vector to be subtracted from another and the result is stored in the first.
*	@param v The vector we will subtract from the original.
*/
void Vector3::operator-= (const Vector3 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

/** Overloaded *= operator.\n
*	Allows a Vector3 to be multiplied by a float and have the result stored in the same vector.
*	@param s The value to multiply by.
*/
void Vector3::operator*= (const float s)
{
	x *= s;
	y *= s;
	z *= s;
}

/** Overloaded division operator.\n
*	Allows a vector to be divided by a float.
*	@param s The value to divide by.
*	@return The vector divided by the float.
*/
Vector3 Vector3::operator/  (const float s) const
{
	return Vector3(x / s, y / s, z / s);
}

/** Overloaded subtraction operator.\n
*	Allows one vector to be subtracted from another.
*	@param v The vector to subtract from the left hand vector.
*	@return The result of the subtraction operation.
*/
Vector3 Vector3::operator- (const Vector3 &v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

/** Overloaded addition operator.\n
*	Allows 2 vectors to be added together.
*	@param v The vector to add.
*	@return The result of the addition operation.
*/
Vector3 Vector3::operator+  (const Vector3 &v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

/** Overloaded multiplication operator.\n
*	Allows a Vector3 to be multiplied by a float.
*	@param s The value to multiply the vector by.
*	@return The result of the multiplication operation.
*/
Vector3 Vector3::operator*  (const float    s) const
{
	return Vector3(x * s, y * s, z * s);
}

/** Overloaded unary minus operator.\n
*	Allows a vector to become negative by putting the minus sign in front of it.
*	@return The negative of this vector.
*/
Vector3 Vector3::operator- () const
{
	return Vector3(x * -1, y * -1, z * -1);
}

/** Cross product operation.\n
*	Performs the cross product between 2 vectors.
*	@param vA The first vector.
*	@param vB The seond vector.
*	@return The cross product vector of vA and vB. It is a vector perpendicular to both, i.e. the (un-normalized) normal.
*/
Vector3 Vector3::Cross(const Vector3 &vA, const Vector3 &vB)
{
	//(a2*b3-a3*b2)i + (a3*b1-a1*b3)j + (a1*b2-a2*b1)k
	return Vector3(vA.y * vB.z - vA.z * vB.y, vA.z * vB.x - vA.x * vB.z, vA.x * vB.y - vA.y * vB.x);
}

/** Dot product operation.\n
*	Performs the dot product between two vectors.
*	@param vA The first vector.
*	@param vB The second vector.
*	@return The algebraic dot product between vA and vB (not the geometric dot product).
*/
float Vector3::Dot(const Vector3 &vA, const Vector3 &vB)
{
	//u.v = u1v1 + u2v2 + u3v3
	return float(vA.x * vB.x + vA.y * vB.y + vA.z * vB.z);
}

/** Normalize operation.
*	@param v The vector to normalize.
*	@return The value of v divided by its length.
*/
Vector3 Vector3::Normalize(const Vector3& v)
{
	return v / Vector3::Length(v);
}

/** Length operation.\n
*	Finds the length of a vector. Does not use a Matth:: method.
*	@param v The input vector.
*	@return The length of v.
*/
float Vector3::Length(const Vector3& v)
{
	return sqrt(LengthSq(v));
}

/** Square length operation.\n
*	Finds the length squared of a vector. Does not use a square root.
*	@param v The input vector.
*	@return The squared length of v.
*/
float Vector3::LengthSq(const Vector3& v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}