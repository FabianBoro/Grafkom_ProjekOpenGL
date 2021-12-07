/******************
DecorCross adalah objek dekorasi berbentuk
kotak/balok
(sebelumnya nama DecorCross diambil
dari konsep sebelumnya yaitu
membuat dekorasi dengan menyilangkan
gambar yang sama)
******************/

#ifndef DECORCROSS_H
#define DECORCROSS_H
#include "vector2.h"
#include <GL/glut.h>
#include <vector>

class DecorCross{
	public:
		static DecorCross *container[100];
		static int counter;
		GLuint image;
		float w;
		float h;
		std::vector<Vector2> position;
		DecorCross();
		DecorCross(GLuint image, float w, float h);
		void set(GLuint image, float w, float h);
		void add(float x, float y);
		static void draw();
	protected:
};

#endif
