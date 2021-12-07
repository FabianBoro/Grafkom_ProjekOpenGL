/******************
Circle adalah objek lingkaran yang
memiliki titik pusat dan radius
serta metode pendeteksi irisan
******************/

#ifndef CIRCLE_H
#define CIRCLE_H
#include "vector2.h"

class Circle{
	public:
		Vector2 center;
		float radius;
		Circle(float x, float y, float r);
		bool isIntersect(Circle other);
		bool isInside(Vector2 point);
};

#endif
