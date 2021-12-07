#include "circle.h"

Circle::Circle(float x, float y, float r){
	this->center.x = x;
	this->center.y = y;
	this->radius = r;
}
bool Circle::isIntersect(Circle other){
	return 
	this->center.dist(other.center) < 
	this->radius+other.radius;
}
bool Circle::isInside(Vector2 point){
	return point.dist(this->center) < this->radius;
}
