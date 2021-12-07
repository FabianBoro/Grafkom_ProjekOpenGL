/******************
Hook adalah objek yang dipakai untuk
membuat efek mengular dengan mengaitkan
kepala dan ekor ke lokasi yang diinginkan
******************/

#ifndef HOOK_H
#define HOOK_H
#include "vector2.h"

class Hook{
	public:
		Vector2 pos;
		Vector2 tpos;
		float len;
		float dir;
		Hook(float x1, float y1, float x2, float y2);
		void setPos(float x, float y, Vector2 *diffhelper);
};

#endif
