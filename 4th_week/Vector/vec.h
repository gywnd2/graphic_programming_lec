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

	float  x; float  y;

public:
	//
	//  --- Constructors and Destructors ---
	//
	vector2D() { x = 0.0; y = 0.0; }
	vector2D(float s) { x = s; y = s; }
	vector2D(float a, float b)	{ x = a;y = b;} 
	vector2D(const vector2D& v) { x = v.x;  y = v.y; }

	//
	//  --- Indexing Operator ---
	//
	float& operator [] (int i)  // v[0]=5와 같은 방식(배열 호출하듯이) 으로 v.x의 값 변경가능하게 해주는 operator
	{ 
		return *(&x + i); 
	}
	const float operator [] (int i) const // const함수 이므로 int n; n=v[0]과 같이 rhs에서 호출 가능하며 v.x의 값을 배열 형식을 바로 가져올 수 있게 해줌
	{ 
		return *(&x + i); 
	}
	//
	//  --- (non-modifying) Arithematic Operators ---
	//

	vector2D operator + (const vector2D& v) const 
	{
		return vector2D(x + v.x, y + v.y);
	}
	vector2D operator - (const vector2D& v) const
	{
		return vector2D(x - v.x, y - v.y);
	}
	vector2D operator * (const float s) const
	{
		return vector2D(s*x, s*y);
	}
	vector2D operator * (const vector2D& v) const
	{
		return vector2D(x*v.x, y*v.y);
	}

	
	friend vector2D operator * (const float s, const vector2D& v) // a*3뿐 아니라 3*a도 가능하게 해줌
	{
		return v * s;
	}
	vector2D operator / (const float s) const { // s분의 1을 r로 표현함으로써 r을 곱해주면 s를 분모로 나누는 것과 같음. 곱하는 것은 * 함수로 넘겨줌
		float r = float(1.0) / s;
		return *this * r;
	}
	vector2D operator - () const // unary minus operator. 뺄셈 아니라는 뜻
	{ 
		return vector2D(-x, -y);
	}

	//
	//  --- (modifying) Arithematic Operators ---
	//
	vector2D& operator += (const vector2D& v) 
	{ 
		x += v.x;  
		y += v.y;   
		return *this; 
	}
	vector2D& operator -= (const vector2D& v) 
	{ 
		x -= v.x;  
		y -= v.y;  
		return *this; 
	}
	vector2D& operator *= (const float s) 
	{ 
		x *= s;  
		y *= s;   
		return *this; 
	}
	vector2D& operator *= (const vector2D& v) 
	{ 
		x *= v.x;  
		y *= v.y; 
		return *this; 
	}
	vector2D& operator /= (const float s) 
	{
		float r = float(1.0) / s;
		*this *= r;
		return *this;
	}

	//
	//  --- Insertion and Extraction Operators ---
	// 
	friend std::ostream& operator << (std::ostream& os, const vector2D& v) // cout<<a
	{
		return os << "( " << v.x << ", " << v.y << " )";
	}

	friend std::istream& operator >> (std::istream& is, vector2D& v) // cin>>a
	{
		return is >> v.x >> v.y;
	}

};

//----------------------------------------------------------------------------
//
//  Non-class vec2 Methods
//

inline float dot(const vector2D& u, const vector2D& v) { return u[0] * v[0] + u[1] * v[1]; }

inline float length(const vector2D& v) { return std::sqrt(dot(v, v)); }

inline vector2D normalize(const vector2D& v) { return v / length(v); }

//////////////////////////////////////////////////////////////////////////////
//
//  3D vector
//
//////////////////////////////////////////////////////////////////////////////

class vector3D {

public:
	float  x;
	float  y;
	float  z;

	//
	//  --- Constructors and Destructors ---
	//
	vector3D() { x = 0.0; y = 0.0; z = 0.0; }
	vector3D(float s) 	{ x=s; y=s; z=s; }
	vector3D(float a, float b, float c) { x=a; y=b; z=c; }
	vector3D(const vector3D& v) { x = v.x;  y = v.y;  z = v.z; }
	vector3D(const vector2D& v, const float f) { x = v[0];  y = v[1];  z = f; }

	//
	//  --- Indexing Operator ---
	//

	float& operator [] (int i) { return *(&x + i); }
	const float operator [] (int i) const { return *(&x + i); }

	//
	//  --- (non-modifying) Arithematic Operators ---
	//

	vector3D operator - () const  // unary minus operator
	{
		return vector3D(-x, -y, -z);
	}

	vector3D operator + (const vector3D& v) const
	{
		return vector3D(x + v.x, y + v.y, z + v.z);
	}

	vector3D operator - (const vector3D& v) const
	{
		return vector3D(x - v.x, y - v.y, z - v.z);
	}

	vector3D operator * (const float s) const
	{
		return vector3D(s*x, s*y, s*z);
	}

	vector3D operator * (const vector3D& v) const
	{
		return vector3D(x*v.x, y*v.y, z*v.z);
	}

	friend vector3D operator * (const float s, const vector3D& v)
	{
		return v * s;
	}

	vector3D operator / (const float s) const {

		float r = float(1.0) / s;
		return *this * r;
	}

	//
	//  --- (modifying) Arithematic Operators ---
	//

	vector3D& operator += (const vector3D& v)
	{
		x += v.x;  y += v.y;  z += v.z;  return *this;
	}

	vector3D& operator -= (const vector3D& v)
	{
		x -= v.x;  y -= v.y;  z -= v.z;  return *this;
	}

	vector3D& operator *= (const float s)
	{
		x *= s;  y *= s;  z *= s;  return *this;
	}

	vector3D& operator *= (const vector3D& v)
	{
		x *= v.x;  y *= v.y;  z *= v.z;  return *this;
	}

	vector3D& operator /= (const float s) {

		float r = float(1.0) / s;
		*this *= r;

		return *this;
	}

	//
	//  --- Insertion and Extraction Operators ---
	//

	friend std::ostream& operator << (std::ostream& os, const vector3D& v) {
		return os << "( " << v.x << ", " << v.y << ", " << v.z << " )";
	}

	friend std::istream& operator >> (std::istream& is, vector3D& v)
	{
		return is >> v.x >> v.y >> v.z;
	}

};

//----------------------------------------------------------------------------
//
//  Non-class vec3 Methods
//

inline float dot(const vector3D& u, const vector3D& v) { return u.x*v.x + u.y*v.y + u.z*v.z; }
inline float length(const vector3D& v) { return std::sqrt(dot(v, v)); }
inline vector3D normalize(const vector3D& v) { return v / length(v); }
inline vector3D cross(const vector3D& a, const vector3D& b) {
	return vector3D(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}
///////////////////////////////////////////////////////////////////////