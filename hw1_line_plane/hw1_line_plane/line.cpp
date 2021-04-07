#include "vec.h"

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

	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	std::cout << "c: " << c << std::endl;

	testvec();

	return 0;
}


vector3D projected_pt_onto_line(vector3D p, vector3D v, vector3D q)
{
	// the line is defined as p+t*v
	// where p is the point position on the line 
	//       v is the directional vector along the line
	//       t is the scalar values

	// Compute the projected point of q on the line "p+t*v" 
	//
	vector3D result = 0.0;
	vector3D pq = q - p;
	float t = dot(pq, v) / length(v);
	result = p + t * v;

	return result;
}

float dist_btw_pt_line(vector3D p, vector3D v, vector3D q)
{
	// compute the distance between the point q and the line "p+t*v"
	float dist = 0.0;
	dist = length(q - projected_pt_onto_line(p, v, q));
	return dist;
}


bool forward_direction_of_robot(vector2D p, vector2D v, vector2D x)
{
	// robot position: p
	// robot forward direction: v
	// x is in front of robot? or not?
	// p = [-3 4]
	// v = [5, -2]
	// x = [0, 0]   [1 6] [-6 0] [-4 7] [5 5] [-3 0] 
	bool forward = false;
	vector2D px = x - p;
	float cos = dot(px, v) / (length(px) * length(v));
	if (cos > 0) { forward = true; }
	return forward;
}


bool same_side_of_plane(vector3D a, vector3D b, vector3D c, vector3D p, vector3D q)
{
	// point a, b, c define the plane 
	// Let's decide wheter point p and point q are on the same side of the plane
	bool same_side = false;
	vector3D ba = a - b;
	vector3D ac = c - a;
	vector3D ap = p-a;
	vector3D aq = q-a;
	vector3D n = cross(ba, ac);
	float cosapn = dot(ap, n) / (length(ap) * length(n));
	float cosaqn = dot(aq, n) / (length(aq) * length(n));
	
	if (cosapn*cosaqn>0) {same_side = true;}
	return same_side;
}

float dist_from_pt_to_plane(vector3D a, vector3D b, vector3D c, vector3D q)
{
	// point a, b, c define the plane 
	// Compute the distance from point q to the plane
	float dist = 0.0;
	vector3D ba = a - b;
	vector3D ac = c - a;
	vector3D n = normalize(cross(ba, ac));
	vector3D aq = q - a;
	dist = dot(aq, n);

	return dist;
}

