#include "decorcross.h"

DecorCross *DecorCross::container[100];
int DecorCross::counter = 0;

DecorCross::DecorCross(){
	DecorCross::container[DecorCross::counter] = this;
	DecorCross::counter++;
}
DecorCross::DecorCross(GLuint image, float w, float h){
	this->image = image;
	this->w = w;
	this->h = h;
	DecorCross::container[DecorCross::counter] = this;
	DecorCross::counter++;
}
void DecorCross::set(GLuint image, float w, float h){
	this->image = image;
	this->w = w;
	this->h = h;
}
void DecorCross::add(float x, float y){
	Vector2 n(x, y);
	this->position.push_back(n);
}

