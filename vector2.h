/******************
Vector2 adalah objek vektor yang
memiliki atribut x dan y
serta memiliki metode yang bisa digunakan
untuk mengoperasikan vektor ini
******************/

#ifndef VECTOR2_H
#define VECTOR2_H
#include <math.h>

class Vector2{
	public:
		float x;
		float y;
		Vector2();
		Vector2(float x, float y);
		void rad2Vec(float rad);
		void setPos(float x, float y);
		void movePos(float x, float y);
		float dist(Vector2 other);
		float length();
		void mult(float v, Vector2 *res);
		void normalize();
		void scale(float scalar);
		float toRad();
};

#endif
