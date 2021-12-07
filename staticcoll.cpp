#include "staticcoll.h"

int StaticColl::counter = 0;
StaticColl *StaticColl::container[100];

StaticColl::StaticColl(Rect rect){
	this->rect = rect;
	this->isEnabled = true;
	StaticColl::container[StaticColl::counter] = this;
	StaticColl::counter++;
}
