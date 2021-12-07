/******************
Rect adalah objek persegi panjang yang
memiliki titik pusat dan ukuran, serta
memiliki metode-metode pendeteksi irisan
dengan Rect lainnya dan titik berada dalam
objek ini.
Objek ini adalah objek utama dalam segala
interaksi dalam program ini
******************/

#ifndef RECT_H
#define RECT_H
#include "vector2.h"

class Rect{
	public:
		Vector2 center;
		Vector2 size;
		Rect();
		Rect(float x, float y, float w, float h);
		bool isIntersect(Rect other);
		bool isInside(Vector2 point);
};

#endif
