#include "rect.h"
Rect::Rect(){
}
Rect::Rect(float x, float y, float w, float h){
	this->center.setPos(x,y);
	this->size.setPos(w,h);
}
bool Rect::isIntersect(Rect other){
	return 
	this->center.x+this->size.x > other.center.x - other.size.x && 
	this->center.x-this->size.x < other.center.x + other.size.x &&
	this->center.y+this->size.y > other.center.y - other.size.y && 
	this->center.y-this->size.y < other.center.y + other.size.y;
}
bool Rect::isInside(Vector2 point){
	return
	point.x < this->center.x+this->size.x &&
	point.x > this->center.x-this->size.x &&
	point.y < this->center.y+this->size.y &&
	point.y > this->center.y-this->size.y;
}
