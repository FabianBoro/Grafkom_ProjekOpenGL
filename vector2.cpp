#include "vector2.h"

Vector2::Vector2(){
	this->x = 0;
	this->y = 0;
}
Vector2::Vector2(float x, float y){
	this->x = x; this->y = y;
}
void Vector2::setPos(float x, float y){
	this->x = x; this->y = y;
}
void Vector2::movePos(float x, float y){
	this->x += x; this->y += y;
}
float Vector2::dist(Vector2 other){
	return sqrt(pow(this->x-other.x, 2) + pow(this->y-other.y, 2));
}
float Vector2::length(){
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}
void Vector2::rad2Vec(float rad){
	this->setPos(cos(rad), sin(rad));
}
float Vector2::toRad(){
	float res = acos(this->x);
	return this->y >= 0? res : -res+2*M_PI;
}
void Vector2::mult(float v, Vector2 *res){
	res->setPos(res->x*v, res->y*v);
}
void Vector2::normalize(){
	float len = this->length();
	if(len != 0){
		this->x /= len;
		this->y /= len;
	}
}
void Vector2::scale(float scalar){
	this->x *= scalar;
	this->y *= scalar;
}
