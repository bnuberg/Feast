#include "vector3.h"
#include <iostream>
using namespace std;


//Default Constructor
Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

//Constructor with Inputs
Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//Copy Constructor
Vector3::Vector3(const Vector3& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}

//+= Operator
void Vector3::operator+= (const Vector3 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

//-= Operator
void Vector3::operator-= (const Vector3 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

//*= Operator
void Vector3::operator*= (const float s)
{
	x *= s;
	y *= s;
	z *= s;
}

// / Operator
Vector3 Vector3::operator/  (const float s) const
{
	return Vector3(x / s, y / s, z / s);
}

//- Operator
Vector3 Vector3::operator- (const Vector3 &v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

//+ Operator
Vector3 Vector3::operator+  (const Vector3 &v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

//* Operator
Vector3 Vector3::operator*  (const float    s) const
{
	return Vector3(x * s, y * s, z * s);
}

//Unary - Operator
Vector3 Vector3::operator- () const
{
	return Vector3(x * -1, y * -1, z * -1);
}

//Cross product
Vector3 Vector3::Cross(const Vector3 &vA, const Vector3 &vB)
{
	//(a2*b3-a3*b2)i + (a3*b1-a1*b3)j + (a1*b2-a2*b1)k
	return Vector3(vA.y * vB.z - vA.z * vB.y, vA.z * vB.x - vA.x * vB.z, vA.x * vB.y - vA.y * vB.x);
}

//Dot product
float Vector3::Dot(const Vector3 &vA, const Vector3 &vB)
{
	//u.v = u1v1 + u2v2 + u3v3
	return float(vA.x * vB.x + vA.y * vB.y + vA.z * vB.z);
}

//Normalize
Vector3 Vector3::Normalize(const Vector3& v)
{
	return v / Vector3::Length(v);
}

//Length
float Vector3::Length(const Vector3& v)
{
	return sqrt(LengthSq(v));
}

//Square Length
float Vector3::LengthSq(const Vector3& v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

/*
//Tests
int main(int argc, char **argv)
{

Vector3 bob(1.0f,2.0f,3.0f);
cout << "bob = {" << bob.x << ", " << bob.y << ", " << bob.z << "}" << endl;

Vector3 barry;
cout << "barry: " << barry.x << endl;

bob.x = 1.5f;
Vector3 bill(bob);
cout << "bill = {" << bill.x << ", " << bill.y << ", " << bill.z << "}" << endl;

barry.y = 30.0f;
bill += barry;
cout << "bill = {" << bill.x << ", " << bill.y << ", " << bill.z << "}" << endl;

Vector3 jim = barry / 3.0f;
cout << "jim = {" << jim.x << ", " << jim.y << ", " << jim.z << "}\n" << endl;


cout << "bill = {" << bill.x << ", " << bill.y << ", " << bill.z << "}" << endl;
cout << "bob = {" << bob.x << ", " << bob.y << ", " << bob.z << "}" << endl;
Vector3 alan = Vector3::Cross(bill, bob);
cout << "alan = {" << alan.x << ", " << alan.y << ", " << alan.z << "}" << endl;

float brian = Vector3::Dot(bill, bob);
cout << "brian = bill . bob = " << brian << endl;

alan = -alan;
cout << "-alan = {" << alan.x << ", " << alan.y << ", " << alan.z << "}" << endl;//because -0 is a thing.

Vector3 nalan = Vector3::Normalize(alan);
cout << "-nalan = {" << nalan.x << ", " << nalan.y << ", " << nalan.z << "}" << endl;



system("pause");
return 0;
}
*/