/******************
StaticColl adalah objek diam yang dapat
ditabrak/tidak dapat dilewati oleh 
MoveColl
******************/

#ifndef STATICCOLL_H
#define STATICCOLL_H
#include "rect.h"

class StaticColl{
	public:
		static StaticColl *container[100];
		static int counter;
		Rect rect;
		bool isEnabled;
		StaticColl(Rect rect);
	protected:
};

#endif
