/******************
MoveColl adalah objek bergerak yang
menabrak StaticColl
******************/

#ifndef MOVECOLL_H
#define MOVECOLL_H
#include <math.h>
#include "rect.h"
#include "staticcoll.h"

class MoveColl{
	public:
		Rect rect;
		MoveColl(Rect rect);
		float setPos(float x, float y);
	protected:
};

#endif
