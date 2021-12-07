#include "movecoll.h"

MoveColl::MoveColl(Rect rect){
	this->rect = rect;
}
float MoveColl::setPos(float x, float y){
	float bx = this->rect.center.x, by = this->rect.center.y;
	this->rect.center.setPos(x, by);
	for(int i = 0; i < StaticColl::counter; i++){
		if(StaticColl::container[i]->isEnabled){
			if(StaticColl::container[i]->rect.isIntersect(this->rect)){
				x = bx;
				this->rect.center.setPos(x, by);
				break;
			}
		}
	}
	this->rect.center.setPos(x, y);
	for(int i = 0; i < StaticColl::counter; i++){
		if(StaticColl::container[i]->isEnabled){
			if(StaticColl::container[i]->rect.isIntersect(this->rect)){
				y = by;
				this->rect.center.setPos(x, y);
				break;
			}
		}
	}
	
	return sqrt(pow(x-bx, 2)+pow(y-by, 2));
}

