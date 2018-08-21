#pragma once
#include "Vector3D.h"
#include <string>

struct object
{
	double mass=0;
	Vector3D location=Vector3D();
	Vector3D speed=Vector3D();
	object(double m = 0, Vector3D l = Vector3D(), Vector3D v = Vector3D()) :mass(m), location(l), speed(v) {};
	double distance(double a = 0, double b = 0, double c = 0)
	{
		return location.distance(a, b, c);
	}
	double distance(Vector3D a=Vector3D())
	{
		return (location-a).magnitude();
	}
	double velocity()//ËÙÂÊ
	{
		return speed.magnitude();
	}
	Vector3D momentum()
	{
		return speed*mass;
	}
	double kinetic_energy() 
	{
		return (speed.dot(speed))*0.5*mass;
	}
	Vector3D angular_momentum(Vector3D reference=Vector3D())
	{
		return (location - reference).cross(speed*mass);
	}
	Vector3D angular_momentum(double x0=0, double y0=0, double z0=0)
	{
		Vector3D tmp(x0, y0, z0);
		return angular_momentum(tmp);
	}
};

struct sphere :public object
{
	double radius;
	sphere(double r =0, double m = 0,Vector3D l = Vector3D(), Vector3D v = Vector3D()) :radius(r), object(m,l,v) {};
};

struct space_sphere : public sphere
{
	string name;
	space_sphere(string n, double r = 0, double m = 0, Vector3D l = Vector3D(), Vector3D v = Vector3D()) :name(n), sphere(r, m, l, v) {};
	double Theta(Vector3D core=Vector3D())
	{
		return atan((location-core).y / (location-core).x);
	}
	double Phi(Vector3D core=Vector3D())
	{
		return acos((location-core).z /(location-core).magnitude());
	}
};

struct  planet: public:space_sphere
{
	int Satelites_num = 0;
};
struct star :public:space_sphere
{
	int Planet_num = 0;
	planet* Planets;
};