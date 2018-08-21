#pragma once
#include "Vector3D.h"
#define constG 1

Vector3D uniform_motion(Vector3D r0, Vector3D v,double dt)//����ֱ���˶�
{
	return (r0 + v*dt);
}


Vector3D uniform_acceleration(Vector3D v0, Vector3D a, double dt)//�ȼ���
{
	return (v0 + a*dt);
}


Vector3D Gravitation(double mass, Vector3D r)//��������Ϊmass������Ծ���Ϊr������������������ٶ�
{
	return r*(-1)*constG*mass / pow(r.magnitude(), 3);
}

Vector3D Gravitation(double mass, Vector3D r2, Vector3D r1)//r1Ϊ����Ϊmass�������λ�ã�r2Ϊ�ܵ������������λ��
{
	return Gravitation(mass, r2 - r1);
}

void unit_varying_accelerated_motion(Vector3D &r0, Vector3D &v0, Vector3D a,double dt)
{
	r0 = r0 + v0*dt;
	v0 = v0 + a*dt;
}

void Motion_by_Gravitation(Vector3D &r0, Vector3D &v0, double mass, Vector3D R, double dt, double t)
{
	double timing=0;
	while(timing<=t)
	{
		unit_varying_accelerated_motion(r0, v0, Gravitation(mass, r0 - R), dt);
		//cout << r0 << v0 << endl;
		timing += dt;
	}
}

void Motion_by_Gravitation(object &sth, double mass, Vector3D R, double dt, double t)
{
	Motion_by_Gravitation(sth.location, sth.speed, mass, R, dt, t);
}

void Motion_by_Gravitation(object &sth, object core, double dt, double t)
{
	Motion_by_Gravitation(sth, core.mass, core.location, dt, t);
}