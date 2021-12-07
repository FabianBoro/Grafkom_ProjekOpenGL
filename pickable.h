/******************
Pickable adalah objek yang dapat
diambil/dipick/digrab oleh pemain
******************/

#ifndef PICKABLE_H
#define PICKABLE_H
#include <GL/glut.h> 
#include "staticcoll.h"
#include "circle.h"

class Pickable{
	public:
		static Pickable *hold;
		static bool isHold;
		static Pickable *container[100];
		static int counter;
		GLuint image;
		
		Pickable();
		void set(float x, float y, float l, GLuint image);
		void setPos(float x, float y);
		static void draw();
		static bool togglePick(Vector2 *playerPos);
		
	private:
		StaticColl *coll;
		Circle *radius;
};

#endif
