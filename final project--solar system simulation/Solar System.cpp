// Solar System.cpp : 定义控制台应用程序的入口点。
//
#include "Vector3D.h"
#include "object.h"
#include "stdafx.h"
#include "movement.h"


int main()
{
	space_sphere ball("ball",5, 2);
	ball.location = Vector3D(1,0,0);
	ball.speed = Vector3D(0, 1, 0);
	Motion_by_Gravitation(ball.location, ball.speed, 1, Vector3D(), 0.0000001, 1.5707963);
	//Motion_by_Gravitation(ball, 1, Vector3D(1, 0, 0), 0.1, 2.01);
	//unit_varying_accelerated_motion(ball.location, ball.speed, Vector3D(1,0,0), 3);
	cout << ball.location << endl << ball.speed << endl;
	Vector3D gravity = Gravitation(1, ball.location, Vector3D());
	cout << gravity << endl;
	cout << ball.name<< " " << ball.Phi() <<" "<< ball.Theta();


	/*Vector3D b(3, 4, 7); Vector3D c(6, 6, 6); Vector3D d;
	c = (1.0 / 6.0)*c;
	cout << d.distance(1, 1, 1) <<" "<<c.magnitude()<< endl;
	double bsss = b.dot(1,-1,-1); cout << bsss << endl;
	sphere ball(5,2,b); 
	ball.speed = c;
	cout << ball.radius <<" "<<ball.distance(1,1,1)<<" "<<ball.distance(c)<<" "<<ball.velocity()<< endl;
	cout << ball.kinetic_energy() << endl ;
	cout<<ball.angular_momentum(0)<<" "<<ball.momentum();*/
    return 0;
}

