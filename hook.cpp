#include "hook.h"

Hook::Hook(float x1, float y1, float x2, float y2){
	this->pos.x = x1;
	this->pos.y = y1;
	this->tpos.x = x2;
	this->tpos.y = y2;
	Vector2 diff;
	Vector2 temp(x2, y2);
	diff.setPos(x2-x1, y2-y1);
	diff.normalize();
	this->len = pos.dist(temp);
	this->dir = diff.toRad();
	delete &diff;
	delete &temp;
}
void Hook::setPos(float x, float y, Vector2 *diffhelper){
	diffhelper->setPos(this->tpos.x-x, this->tpos.y-y);
	this->pos.x = x;
	this->pos.y = y;
	diffhelper->normalize();
	this->dir = diffhelper->toRad();
	diffhelper->scale(this->len);
	this->tpos.setPos(this->pos.x + diffhelper->x, this->pos.y + diffhelper->y);
}
