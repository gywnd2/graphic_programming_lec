#include "vec.h"

void testvec()
{
	// A.
	// the length and the unit vector of the following vectors
	// [ 1 3 -1]
	// [ 4 2 0]
	// [ 5 1 0]

	vector3D a1;
	a1 = vector3D(1, 3, -1);
	std::cout << a1;
	std::cout << "'s length: " << length(a1) << ", ";
	std::cout << "Unit vector: " << normalize(a1) << std::endl;

	vector3D b1;
	b1 = vector3D(4, 2, 0);
	std::cout << b1;
	std::cout << "'s length: " << length(b1) << ", ";
	std::cout << "Unit vector: " << normalize(b1) << std::endl;

	vector3D c1;
	c1 = vector3D(5, 1, 0);
	std::cout << c1;
	std::cout << "'s length: " << length(c1) << ", ";
	std::cout << "Unit vector: " << normalize(c1) << std::endl;

	// B.
	// adding vectors
	// [3 4] + [2 5]
	// [5 2 4] + [ 3 2 7]
	vector2D a2(3, 4);
	vector2D b2(2, 5);
	std::cout << a2 << " + " << b2 << " 는 " << a2 + b2 << std::endl;

	vector3D c2(5, 2, 4);
	vector3D d2(3, 2, 7);
	std::cout << c2 << " + " << d2 << " 는 " << c2 + d2 << std::endl;

	// C.
	// subtracting vectors
	// [3 7] - [2 4]
	// [3 8 4] - [8 2 1]

	vector2D a3(3, 7);
	vector2D b3(2, 4);
	std::cout << a3 << " - " << b3 << " 는 " << a3 - b3 << std::endl;

	vector3D c3(3, 8, 4);
	vector3D d3(8, 2, 1);
	std::cout << c3 << " - " << d3 << " 는 " << c3 - d3 << std::endl;

	// D.
	// multiplying vectors
	// 0.2 [ 3 4]
	// [5 7 8] * [3 4 5]
	float mul = 0.2;
	vector2D a4(3, 4);
	std::cout << mul << " * " << a4 << " 는 " << mul * a4 << std::endl;

	vector3D b4(5, 7, 8);
	vector3D c4(3, 4, 5);
	std::cout << b4 << " * " << c4 << " 는 " << b4 * c4 << std::endl;

	// E.
	// addition and subtration
	// [ 4 5 6] + [7 -3 0] - [1 2 3]
	vector3D a5(4, 5, 6);
	vector3D b5(7, -3, 0);
	vector3D c5(1, 2, 3);
	std::cout << a5 << " + " << b5 << " - " << c5 << " 는 " << a5 + b5 - c5 << std::endl;

	// F. 내적
	// [2 6] o [-3 8]
	// -7 [1 2] o [11 -4]
	vector2D a6(2, 6);
	vector2D b6(-3, 8);
	std::cout << a6 << " o " << b6 << " 는 " << dot(a6, b6) << std::endl;

	float mul2 = -7;
	vector2D c6(1, 2);
	vector2D d6(11, -4);
	std::cout << mul2 << " * " << c6 << " o " << d6 << " 는 " << dot((mul2 * c6), d6) << std::endl;

	// G.
	// cross product ; a x b  and b x a
	// a = [0 -1 0]  b = [ 0 0 1]
	// a = [-2 4 1]  b = [1 -2 -1]
	vector3D a7(0, -1, 0);
	vector3D b7(0, 0, 1);
	std::cout << a7 << " x " << b7 << " 는 " << cross(a7, b7) << " 이고 " << b7 << " x " << a7 << " 는 " << cross(b7, a7) << std::endl;

	vector3D a8(-2, 4, 1);
	vector3D b8(1, -2, -1);
	std::cout << a8 << " x " << b8 << " 는 " << cross(a8, b8) << " 이고 " << b8 << " x " << a8 << " 는 " << cross(b8, a8) << std::endl;
}

int main()
{
	// 2D vector
	vector2D a, b;
	vector2D c(3.0, 4.0);
	a = vector2D(5.0, 2.0);
	b = vector2D(c);

	float len, dott;
	len = length(a);
	dott = dot(a, b);
	vector2D d = normalize(c);

	std::cout << "a: " << a << std::endl; // a: ( ,  )
	std::cout << "b: " << b << std::endl;
	std::cout << "c: " << c << std::endl;

	testvec();

	return 0;
}
