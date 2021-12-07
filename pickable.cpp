#include "pickable.h"

Pickable *Pickable::hold;
bool Pickable::isHold = false;
Pickable *Pickable::container[100];
int Pickable::counter = 0;
Pickable::Pickable(){
	Pickable::container[Pickable::counter] = this;
	Pickable::counter++;
}
void Pickable::set(float x, float y, float l, GLuint image){
	this->coll = new StaticColl(Rect(x, y, l, l));
	this->image = image;
	this->radius = new Circle(x, y, l+4);
}
void Pickable::setPos(float x, float y){
	this->coll->rect.center.x = x;
	this->coll->rect.center.y = y;
	this->radius->center.x = x;
	this->radius->center.y = y;
}
bool Pickable::togglePick(Vector2 *playerPos){
	if(Pickable::isHold){
		Pickable::isHold = false;
		Pickable::hold->coll->isEnabled = true;
		return true;
	}
	else{
		for(int i = 0; i < Pickable::counter; i++){
			if(Pickable::container[i]->radius->isInside(*playerPos)){
				Pickable::isHold = true;
				Pickable::hold = Pickable::container[i];
				Pickable::container[i]->coll->isEnabled = false;
				return true;
			}
		}
		return false;
	}
}
