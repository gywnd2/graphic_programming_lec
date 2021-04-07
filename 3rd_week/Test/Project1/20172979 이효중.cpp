#include "vec.h"

vector2D vadd(vector2D u, vector2D v);

void main(int)
{
	vector2D a, b, c, d;

	a = vector2D(1, 3);
	b = vector2D(4, 5);
	c = vector2D(7, 2);
	d = vector2D(2, 5);

	vector2D e = vadd(a, c);
	vector2D f = vadd(d, b);

	std::cout << "problem1:  " << e.x << ", " << e.y <<std::endl;
	std::cout << "problem2:  " << f.x << ", " << f.y << std::endl;
	system("pause");
}

vector2D vadd(vector2D u, vector2D v)
{
	return vector2D( u.x + v.x, u.y + v.y);
}
