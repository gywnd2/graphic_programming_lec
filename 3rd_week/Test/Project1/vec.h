#pragma once

#include <cmath>
#include <iostream>

#define M_PI 3.14159265358979323846
#define radians(x) x*M_PI/180.0
#define degrees(x) x*180.0/M_PI

//////////////////////////////////////////////////////////////////////////////
//
//  2D vector
//
/////////////////////////////////////////////////////////////////////////////

class vector2D {
public:
	int  x; int  y;

	//
	//  --- Constructors and Destructors ---
	//
	vector2D() { x = 0; y = 0; }
	vector2D(int s) { x = s; y = s; }
	vector2D(int a, int b) { x = a; y = b; }
	vector2D(const vector2D& v) { x = v.x;  y = v.y; }
};