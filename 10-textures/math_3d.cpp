#include "math_3d.h"

Vector2f::Vector2f()
{
}

Vector2f::Vector2f(float xF, float yF)
{
	x = xF;
	y = yF;
}

float Vector2f::getX() const
{
	return x;
}

float Vector2f::getY() const
{
	return y;
}

Vector3f::Vector3f()
{
}

Vector3f::Vector3f(float xF, float yF, float zF)
{
    x = xF;
    y = yF;
    z = zF;
}

Vector3f& Vector3f::operator+=(const Vector3f& r)
{
    x += r.x;
    y += r.y;
    z += r.z;

    return *this;
}

Vector3f Vector3f::operator+(const Vector3f& r)
{
	return Vector3f(x + r.x, y + r.y, z + r.z);
}

Vector3f& Vector3f::operator-=(const Vector3f& r)
{
    x -= r.x;
    y -= r.y;
    z -= r.z;

    return *this;
}

Vector3f Vector3f::operator-(const Vector3f& r)
{
	return Vector3f(x - r.x, y - r.y, z - r.z);
}

Vector3f& Vector3f::operator*=(float f)
{
    x *= f;
    y *= f;
    z *= f;

    return *this;
}

Vector3f Vector3f::operator*(const float f)
{
	return Vector3f(f * x, f * y, f * z);
}

/* the cross product produces a vector perpendicular to the plane defined by the vectors */
Vector3f Vector3f::Cross(const Vector3f& B) const
{
	const float xTmp = ((y * B.z) - (z * B.y)); 
	const float yTmp = ((z * B.x) - (x * B.z)); 
	const float zTmp = ((x * B.y) - (y * B.x)); 

	return Vector3f(xTmp, yTmp, zTmp);
}

void Vector3f::Normalize()
{
	const float length = sqrtf((x * x) + (y * y) + (z * z));

	x /= length;
	y /= length;
	z /= length;
}

void Vector3f::rotate(float angle, Vector3f axis)
{
	const float sinHalfAngle = sinf(ToRadian(angle/2));
	const float cosHalfAngle = cosf(ToRadian(angle/2));

	Quaternion rot(axis.getX() * sinHalfAngle, axis.getY() * sinHalfAngle, axis.getZ() * sinHalfAngle, cosHalfAngle);
	Quaternion conj = rot.Conjugate();

	Quaternion W = rot * (*this) * conj;
	x = W.getX();
	y = W.getY();
	z = W.getZ();
}

float Vector3f::getX() const
{
	return x;
}

float Vector3f::getY() const
{
	return y;
}

float Vector3f::getZ() const
{
	return z;
}

Matrix4f::Matrix4f()
{
	InitIdentity();
}
    
   
Matrix4f Matrix4f::Transpose() const
{
    Matrix4f n;
        
    for (unsigned int i = 0 ; i < 4 ; i++) {
        for (unsigned int j = 0 ; j < 4 ; j++) {
            n.m[i][j] = m[j][i];
        }
    }
        
    return n;
}


inline void Matrix4f::InitIdentity()
{
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

Matrix4f Matrix4f::operator*(const Matrix4f& Right) const
{
    Matrix4f Ret;

    for (unsigned int i = 0 ; i < 4 ; i++) {
        for (unsigned int j = 0 ; j < 4 ; j++) {
            Ret.m[i][j] = m[i][0] * Right.m[0][j] +
                            m[i][1] * Right.m[1][j] +
                            m[i][2] * Right.m[2][j] +
                            m[i][3] * Right.m[3][j];
        }
    }

    return Ret;
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Quaternion::Quaternion(Vector3f v, float constant)
{
	x = v.getX();
	y = v.getZ();
	z = v.getZ();
	w = constant;
}

void Quaternion::Normalize()
{
	const float length = sqrtf((x * x) + (y * y) + (z * z) + (w * w));

	x /= length;
	y /= length;
	z /= length;
	w /= length;
}


Quaternion Quaternion::Conjugate()
{
	Quaternion ret(-x, -y, -z, w);
	return ret;
}

Quaternion operator*(const Quaternion& l, const Quaternion& r)
{
    const float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
    const float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
    const float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
    const float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);

    Quaternion ret(x, y, z, w);

    return ret;
}

Quaternion operator*(const Quaternion& q, const Vector3f& v)
{
    const float w = - (q.x * v.getX()) - (q.y * v.getY()) - (q.z * v.getZ());
    const float x =   (q.w * v.getX()) + (q.y * v.getZ()) - (q.z * v.getY());
    const float y =   (q.w * v.getY()) + (q.z * v.getX()) - (q.x * v.getZ());
    const float z =   (q.w * v.getZ()) + (q.x * v.getY()) - (q.y * v.getX());

    Quaternion ret(x, y, z, w);

    return ret;
}

float Quaternion::getX(void)
{
	return x;
}

float Quaternion::getY(void)
{
	return y;
}

float Quaternion::getZ(void)
{
	return z;
}