#pragma once
#include <iostream>
#include <math.h>
using namespace std;

struct Vector3D
{
	double x, y, z;
	Vector3D(double a = 0, double b = 0, double c = 0) :x(a), y(b), z(c) {};
	double magnitude()
	{
		return sqrt(x*x + y*y + z*z);
	}
	double distance(double a=0, double b=0, double c=0)
	{
		return sqrt((x - a)*(x - a) + (x - b)*(x - b) + (x - c)*(x - c));
	}
	Vector3D operator + (const Vector3D &a)
	{
		return Vector3D(x + a.x, y + a.y, z + a.z);
	}
	Vector3D operator - (const Vector3D &a)
	{
		return Vector3D(x - a.x, y - a.y, z - a.z);
	}
	Vector3D operator * (const double &a)//矢量数乘
	{
		return Vector3D(x*a, y*a, z*a);
	}
	Vector3D operator / (const double &a)//矢量数乘
	{
		return Vector3D(x/a, y/a, z/a);
	}
	double dot(double a = 0, double b = 0, double c = 0)//矢量点乘
	{
		return x*a + y*b + z*c;
	}
	double dot(Vector3D a=Vector3D())
	{
		return x*a.x + y*a.y + z*a.z;
	}
	Vector3D cross(double a = 0, double b = 0, double c = 0)//叉乘
	{
		return Vector3D(y*c - z*b, z*a - x*c, x*b - y*a);
	}
	Vector3D cross(Vector3D a = Vector3D())
	{
		return cross(a.x, a.y, a.z);
	}
	friend ostream & operator << (ostream & os, const Vector3D &c)
	{
		os << "(" << c.x << "," << c.y << "," << c.z << ")";
		return os;
	}
};

Vector3D operator * (const double &a, const Vector3D &b)
{
	return Vector3D(a*b.x, a*b.y, a*b.z);
}