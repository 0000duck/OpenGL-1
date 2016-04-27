#ifndef MATH_3D_H
#define	MATH_3D_H

#include <stdio.h>
#include <math.h>

int const winWidth = 800;
int const winHeight = 800;

const float M_PI = 3.1415;

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

class Vector3f
{
public:
    Vector3f();
    Vector3f(float xF, float yF, float zF);

    Vector3f& operator+=(const Vector3f& r);
	Vector3f operator+(const Vector3f& r);
    Vector3f& operator-=(const Vector3f& r);
	Vector3f operator-(const Vector3f& r);
    Vector3f& operator*=(float f);
	Vector3f operator*(const float f);
	Vector3f Cross(const Vector3f& B) const;

	void Normalize();

	void rotate(float angle, Vector3f axis);

	float getX() const;
	float getY() const;
	float getZ() const;
	
private:
    float x;
    float y;
    float z;
};

class Matrix4f
{
public:
    float m[4][4];

    Matrix4f(); 
    Matrix4f Transpose() const;
    inline void InitIdentity();
   
	Matrix4f operator*(const Matrix4f& Right) const;
  
};

class Quaternion {
public:
	Quaternion(float _x, float _y, float _z, float _w);
	Quaternion(Vector3f v, float constant);
	void Normalize();
	Quaternion Conjugate();

	float getX(void);
	float getY(void);
	float getZ(void);

	friend Quaternion operator*(const Quaternion& l, const Quaternion& r);
	friend Quaternion operator*(const Quaternion& q, const Vector3f& v);
	
private:
	float x, y, z, w;
};

#endif

