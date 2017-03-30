#include "Matrix4.h"
#include <iostream>

using namespace std;

//Default Constructor, creates an empty Matrix4
Matrix4::Matrix4()
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = 0.0f;
	}
}

//Copy constructor, creates a Matrix4 from a Matrix4
Matrix4::Matrix4(const Matrix4& rhs)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = rhs.m[i];
	}
}

//Constructor with inputs
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

//[] Operator, returns the element at that position
float&	Matrix4::operator[]	(int index)
{
	return m[index];
}

//Static [] Operator 
const float& Matrix4::operator[] (int index) const
{
	return m[index];
}

//Zero Matrix4
Matrix4 Matrix4::Zero()
{
	return Matrix4();
}

//Identity Matrix4
Matrix4 Matrix4::Identity()
{
	return Matrix4(1.0f,0.0f,0.0f,0.0f,
				   0.0f,1.0f,0.0f,0.0f,
				   0.0f,0.0f,1.0f,0.0f,
				   0.0f,0.0f,0.0f,1.0f);
}

//Transpose Matrix4
Matrix4 Matrix4::Transpose(const Matrix4& mat)
{
	return Matrix4(mat[0], mat[4], mat[8], mat[12],
		           mat[1], mat[5], mat[9], mat[13],
		           mat[2], mat[6], mat[10], mat[14],
		           mat[3], mat[7], mat[11], mat[15]);
}

//Create Matrix4 with this translation
Matrix4 Matrix4::SetTranslation(const Vector3 & translation)
{
	return Matrix4(1.0f, 0.0f, 0.0f, translation.x,
		           0.0f, 1.0f, 0.0f, translation.y,
		           0.0f, 0.0f, 1.0f, translation.z,
		           0.0f, 0.0f, 0.0f, 1.0f);
}

//Get the Translation on Matrix4
Vector3 Matrix4::GetTranslation(const Matrix4 & mat)
{
	return Vector3(mat[3],mat[7],mat[11]);
}

//Create Matrix4 of this scale
Matrix4 Matrix4::SetScale(const Vector3 & scale)
{
	return Matrix4(	scale.x, 0.0f, 0.0f, 0.0f,
					0.0f, scale.y, 0.0f, 0.0f,
					0.0f, 0.0f, scale.z, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}

//Sets up a rotation matrix about a vector by an angle
Matrix4 Matrix4::SetRotationAxis(const Vector3 & axis, float angle)
{
	//where u is a unit victor
	Vector3 u = Vector3::Normalize(axis);
	float C = cos(angle);
	float OMC = (1 - C);
	float S = sin(angle);

	return Matrix4(C + u.x * u.x * OMC, u.x * u.y * OMC - u.z * S, u.x * u.z * OMC + u.y * S, 0.f,
				   u.y * u.x * OMC + u.z * S, C + u.y * u.y * OMC, u.y * u.z * OMC - u.x * S, 0.f,
		           u.z * u.x * OMC - u.y * S, u.z * u.y * OMC + u.x * S, C + u.z * u.z * OMC, 0.f,
		           0.0f, 0.0f, 0.0f, 1.0f);
}

//Transforms a point by a matrix
Vector3 Matrix4::TransformPoint(const Matrix4 & mat, const Vector3 & p)
{
	return Vector3(mat[0] * p.x + mat[4] * p.y + mat[8] * p.z + mat[3],
				   mat[1] * p.x + mat[5] * p.y + mat[9] * p.z + mat[7],
		           mat[2] * p.x + mat[6] * p.y + mat[10] * p.z + mat[11]);
}

//Transform a vector by matrix
Vector3 Matrix4::TransformDirection(const Matrix4 & mat, const Vector3 & n)
{
	return Vector3(n.x * mat[0] + n.y * mat[4] + n.z * mat[8],
		           n.x * mat[1] + n.y * mat[5] + n.z * mat[9],
		           n.x * mat[2] + n.y * mat[6] + n.z * mat[10]);
}

Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs)
{
	return Matrix4(
		(lhs[0 ] * rhs[0] + lhs[1 ] * rhs[4] + lhs[2 ] * rhs[8] + lhs[3 ] * rhs[12]), (lhs[0 ] * rhs[1] + lhs[1 ] * rhs[5] + lhs[2 ] * rhs[9] + lhs[3 ] * rhs[13]), (lhs[0 ] * rhs[2] + lhs[1 ] * rhs[6] + lhs[2 ] * rhs[10] + lhs[3 ] * rhs[14]), (lhs[0 ] * rhs[3] + lhs[1 ] * rhs[7] + lhs[2 ] * rhs[11] + lhs[3 ] * rhs[15]),
		(lhs[4 ] * rhs[0] + lhs[5 ] * rhs[4] + lhs[6 ] * rhs[8] + lhs[7 ] * rhs[12]), (lhs[4 ] * rhs[1] + lhs[5 ] * rhs[5] + lhs[6 ] * rhs[9] + lhs[7 ] * rhs[13]), (lhs[4 ] * rhs[2] + lhs[5 ] * rhs[6] + lhs[6 ] * rhs[10] + lhs[7 ] * rhs[14]), (lhs[4 ] * rhs[3] + lhs[5 ] * rhs[7] + lhs[6 ] * rhs[11] + lhs[7 ] * rhs[15]),
		(lhs[8 ] * rhs[0] + lhs[9 ] * rhs[4] + lhs[10] * rhs[8] + lhs[11] * rhs[12]), (lhs[8 ] * rhs[1] + lhs[9 ] * rhs[5] + lhs[10] * rhs[9] + lhs[11] * rhs[13]), (lhs[8 ] * rhs[2] + lhs[9 ] * rhs[6] + lhs[10] * rhs[10] + lhs[11] * rhs[14]), (lhs[8 ] * rhs[3] + lhs[9 ] * rhs[7] + lhs[10] * rhs[11] + lhs[11] * rhs[15]),
		(lhs[12] * rhs[0] + lhs[13] * rhs[4] + lhs[14] * rhs[8] + lhs[15] * rhs[12]), (lhs[12] * rhs[1] + lhs[13] * rhs[5] + lhs[14] * rhs[9] + lhs[15] * rhs[13]), (lhs[12] * rhs[2] + lhs[13] * rhs[6] + lhs[14] * rhs[10] + lhs[14] * rhs[14]), (lhs[12] * rhs[3] + lhs[13] * rhs[7] + lhs[14] * rhs[11] + lhs[15] * rhs[15])
		);
}
/*
//Prints out a pretty matrix, prettily. Nooo, don't remove me! I'm useful!
void Matrix4::printMatrix4()
{
	cout << "|" << m[0] << "\t" << m[4] << "\t" << m[8]  << "\t" << m[12] << "|" << endl;
	cout << "|" << m[1] << "\t" << m[5] << "\t" << m[9]  << "\t" << m[13] << "|" << endl;
	cout << "|" << m[2] << "\t" << m[6] << "\t" << m[10] << "\t" << m[14] << "|" << endl;
	cout << "|" << m[3] << "\t" << m[7] << "\t" << m[11] << "\t" << m[15] << "|" << endl;
	cout << endl;
}


//	Print out a vector 3
//	Usage: ("label" as string, Vector3 as Vector3);
void printVector3(char* lbl, Vector3 &a)
{
	cout << lbl << ": ";
	cout << a.x << "," << a.y << "," << a.z << endl;
	cout << endl;
}

void main()
{
	Matrix4 ident = Matrix4::Identity();
	ident.printMatrix4();

	Matrix4 m = Matrix4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	m.printMatrix4();

	Matrix4::Transpose(m).printMatrix4();

	Vector3 point = Vector3(2.0f, 3.0f, 4.1f);
	printVector3("point", point);
	Vector3 transVect = Vector3(1.0f, 1.0f, 1.2f);

	Matrix4 n = Matrix4::SetTranslation(transVect);
	Vector3 a = Matrix4::TransformPoint(n, point);
	printVector3("a", a);
	Vector3 f = Matrix4::TransformDirection(n, point);
	printVector3("f", f);

	Vector3 sclVec = Vector3(2.0f, 2.0f, 3.0f);
	Matrix4 sclMat = Matrix4::SetScale(sclVec);

	Vector3 b = Matrix4::TransformPoint(sclMat, point);
	printVector3("b", b);
	Vector3 e = Matrix4::TransformDirection(sclMat, point);
	printVector3("e", e);

	float pi = 3.1415926;
	Vector3 axV = Vector3(0.0f, 10.0f, 0.0f);
	Matrix4 roM = Matrix4::SetRotationAxis(axV, pi / 2);
	Vector3 c = Matrix4::TransformPoint(roM, point);
	printVector3("c", c);

	Vector3 d = Matrix4::TransformDirection(roM, point);
	printVector3("d",d);


	Vector3 g = Matrix4::TransformPoint(m, point);
	printVector3("g",g);
	Vector3 h = Matrix4::TransformDirection(m, point);
	printVector3("h", h);

	
	Matrix4 rotationMatrix = Matrix4::SetRotationAxis(axV, pi / 6);
	for (int i = 0;i < 12;i++)
	{
		Vector3 j = Matrix4::TransformPoint(rotationMatrix, point);
		point = j;
		printVector3("j", j);
	}

	Matrix4 multTest = m * ident;
	multTest.printMatrix4();


	system("pause");
}*/