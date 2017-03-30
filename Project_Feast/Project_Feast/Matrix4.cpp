#include "Matrix4.h"
#include <iostream>

using namespace std;

/** Default Matrix4 constructor, creates an empty Matrix4.
*/
Matrix4::Matrix4()
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = 0.0f;
	}
}


/** Matrix4 copy construtor, creates a Matrix4 from an existing one.
*	@param rhs The Matrix4 to create a copy of.
*/
Matrix4::Matrix4(const Matrix4& rhs)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = rhs.m[i];
	}
}

/** Matrix4 values constructor, creates a Matrix4 from 16 floats.
*	@param _12 The value in the second column and third row of the matrix.
*/
Matrix4::Matrix4(float _00, float _10, float _20, float _30,
				 float _01, float _11, float _21, float _31,
				 float _02, float _12, float _22, float _32,
				 float _03, float _13, float _23, float _33)
{
	m[0]  = _00; m[1]  = _10; m[2]  = _20; m[3]  = _30;
	m[4]  = _01; m[5]  = _11; m[6]  = _21; m[7]  = _31;
	m[8]  = _02; m[9]  = _12; m[10] = _22; m[11] = _32;
	m[12] = _03; m[13] = _13; m[14] = _23; m[15] = _33;
}

/** Matrix4 array constructor, creates a 4x4 matrix from an array of 16 floats.
*	UNTESTED.
*	@param values The array of values to create the matrix from.
*/
Matrix4::Matrix4(float &values[16])
{
	for(int i = 0; i < 16; i++)
	{
		m[i] = values[i];
	}
}

/** [] operator, returns the value of a float at an index.
*	@param index The index at which the value lies.
*	@return The value at that index.
*/
float&	Matrix4::operator[]	(int index)
{
	return m[index];
}

/** Static [] operator, retrieves the value of a float at an index and does not modify it.
*	@param index The index at which the value lies.
*	@return The value at that index.
*/
const float& Matrix4::operator[] (int index) const
{
	return m[index];
}

//Zero Matrix4
/** Zero method, returns a zero-matrix.
*	@return An empty matrix (a matrix filled with zeros).
*/
Matrix4 Matrix4::Zero()
{
	return Matrix4();
}

/** Identity method, creates an identity matrix.
*	@return A matrix whose values are 1 on the leading diagonal and 0 everywhere else.
*/
Matrix4 Matrix4::Identity()
{
	return Matrix4(1.0f,0.0f,0.0f,0.0f,
				   0.0f,1.0f,0.0f,0.0f,
				   0.0f,0.0f,1.0f,0.0f,
				   0.0f,0.0f,0.0f,1.0f);
}

/** Transpose method, swaps the rows and columns of a matrix.
*	@param mat The matrix to be transposed.
*	@return A transposed version of the input matrix.
*/
Matrix4 Matrix4::Transpose(const Matrix4& mat)
{
	return Matrix4(mat[0], mat[4], mat[8], mat[12],
		           mat[1], mat[5], mat[9], mat[13],
		           mat[2], mat[6], mat[10], mat[14],
		           mat[3], mat[7], mat[11], mat[15]);
}

/** Set Translation method, sets the values of the matrix that would modify the position when applied to a vector.
*	@param translation A translation vector.
*	@return An identity matrix whose translation values are modified by the input vector.
*/
Matrix4 Matrix4::SetTranslation(const Vector3 & translation)
{
	return Matrix4(1.0f, 0.0f, 0.0f, translation.x,
		           0.0f, 1.0f, 0.0f, translation.y,
		           0.0f, 0.0f, 1.0f, translation.z,
		           0.0f, 0.0f, 0.0f, 1.0f);
}

/** Get Translation method, finds the translation component of a given matrix.
*	@param mat The input matrix
*	@return A Vector3 that is the translation component of mat.
*/
Vector3 Matrix4::GetTranslation(const Matrix4 & mat)
{
	return Vector3(mat[3],mat[7],mat[11]);
}

/** Scale operation, creates an identity matrix with scale components set by an input vector.
*	Scales in x, y and z.
*	@param scale A Vector3 containing the scale .
*	@return An identity Matrix4 whose scale components are defined by the input vector.
*/
Matrix4 Matrix4::SetScale(const Vector3 & scale)
{
	return Matrix4(	scale.x, 0.0f, 0.0f, 0.0f,
					0.0f, scale.y, 0.0f, 0.0f,
					0.0f, 0.0f, scale.z, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}

/**	Set Rotation Axis, sets up a rotation matrix about a vector by an angle.
*	@param axis A Vector3 representing an axis to rotate around.
*	@param angle An angle in radians to rotate by.
*/
Matrix4 Matrix4::SetRotationAxis(const Vector3 & axis, float angle)
{
	// where u is a unit vector
	Vector3 u = Vector3::Normalize(axis);
	float C = cos(angle);
	float OMC = (1 - C);
	float S = sin(angle);

	// Remember the order of operations. 
	return Matrix4(u.x * u.x * OMC + C      , u.x * u.y * OMC - u.z * S, u.x * u.z * OMC + u.y * S, 0.0f,
				   u.y * u.x * OMC + u.z * S, u.y * u.y * OMC + C      , u.y * u.z * OMC - u.x * S, 0.0f,
		           u.z * u.x * OMC - u.y * S, u.z * u.y * OMC + u.x * S, u.z * u.z * OMC + C      , 0.0f,
		           0.0f                     , 0.0f                     , 0.0f                     , 1.0f);
}

/** Method to transform a point vector by a given matrix.
*	p and m are not modified.
*	@param mat The transformation matrix.
*	@param p The point vector that will be transformed.
*	@return A Vector3 that is p transformed by m.
*/
Vector3 Matrix4::TransformPoint(const Matrix4 & mat, const Vector3 & p)
{
	return Vector3(mat[0] * p.x + mat[4] * p.y + mat[8] * p.z + mat[3],
				   mat[1] * p.x + mat[5] * p.y + mat[9] * p.z + mat[7],
		           mat[2] * p.x + mat[6] * p.y + mat[10] * p.z + mat[11]);
}

/** Method to transform a direction vector by a given matrix.
*	Note that matrix multiplication is non-commutative.
	@param mat A transformation matrix.
*	@param n A normalized direction vector to transform.
*	@return The transformed direction vector.
*/
Vector3 Matrix4::TransformDirection(const Matrix4 & mat, const Vector3 & n)
{
	return Vector3(n.x * mat[0] + n.y * mat[4] + n.z * mat[8],
		           n.x * mat[1] + n.y * mat[5] + n.z * mat[9],
		           n.x * mat[2] + n.y * mat[6] + n.z * mat[10]);
}

/** Overloaded multiplication operator.
*	Multiplies two matrices together.
*	@param lhs Left matrix
*	@param rhs Right matrix
*	@return The result of the matrix multiplication.
*/
Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs)
{
	return Matrix4(
		(lhs[0 ] * rhs[0] + lhs[1 ] * rhs[4] + lhs[2 ] * rhs[8] + lhs[3 ] * rhs[12]), (lhs[0 ] * rhs[1] + lhs[1 ] * rhs[5] + lhs[2 ] * rhs[9] + lhs[3 ] * rhs[13]), (lhs[0 ] * rhs[2] + lhs[1 ] * rhs[6] + lhs[2 ] * rhs[10] + lhs[3 ] * rhs[14]), (lhs[0 ] * rhs[3] + lhs[1 ] * rhs[7] + lhs[2 ] * rhs[11] + lhs[3 ] * rhs[15]),
		(lhs[4 ] * rhs[0] + lhs[5 ] * rhs[4] + lhs[6 ] * rhs[8] + lhs[7 ] * rhs[12]), (lhs[4 ] * rhs[1] + lhs[5 ] * rhs[5] + lhs[6 ] * rhs[9] + lhs[7 ] * rhs[13]), (lhs[4 ] * rhs[2] + lhs[5 ] * rhs[6] + lhs[6 ] * rhs[10] + lhs[7 ] * rhs[14]), (lhs[4 ] * rhs[3] + lhs[5 ] * rhs[7] + lhs[6 ] * rhs[11] + lhs[7 ] * rhs[15]),
		(lhs[8 ] * rhs[0] + lhs[9 ] * rhs[4] + lhs[10] * rhs[8] + lhs[11] * rhs[12]), (lhs[8 ] * rhs[1] + lhs[9 ] * rhs[5] + lhs[10] * rhs[9] + lhs[11] * rhs[13]), (lhs[8 ] * rhs[2] + lhs[9 ] * rhs[6] + lhs[10] * rhs[10] + lhs[11] * rhs[14]), (lhs[8 ] * rhs[3] + lhs[9 ] * rhs[7] + lhs[10] * rhs[11] + lhs[11] * rhs[15]),
		(lhs[12] * rhs[0] + lhs[13] * rhs[4] + lhs[14] * rhs[8] + lhs[15] * rhs[12]), (lhs[12] * rhs[1] + lhs[13] * rhs[5] + lhs[14] * rhs[9] + lhs[15] * rhs[13]), (lhs[12] * rhs[2] + lhs[13] * rhs[6] + lhs[14] * rhs[10] + lhs[14] * rhs[14]), (lhs[12] * rhs[3] + lhs[13] * rhs[7] + lhs[14] * rhs[11] + lhs[15] * rhs[15])
		);
}
