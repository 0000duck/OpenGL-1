/*

	Copyright 2010 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MATH_3D_H
#define	MATH_3D_H

#include <stdio.h>
#include <math.h>

int const winWidth = 800;
int const winHeight = 800;

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

class Vector3f
{
public:
    Vector3f()
    {
    }

    Vector3f(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Vector3f& operator+=(const Vector3f& r)
    {
        x += r.x;
        y += r.y;
        z += r.z;

        return *this;
    }

    Vector3f& operator-=(const Vector3f& r)
    {
        x -= r.x;
        y -= r.y;
        z -= r.z;

        return *this;
    }

	Vector3f& operator-(const Vector3f& r)
    {
		Vector3f tmp;
        tmp.x = x - r.x;
        tmp.y = y - r.y;
        tmp.z = z - r.z;

        return tmp;
    }

    Vector3f& operator*=(float f)
    {
        x *= f;
        y *= f;
        z *= f;

        return *this;
    }

	/* the cross product produces a vector perpendicular to the plane defined by the vectors */
	Vector3f Cross(const Vector3f& B) const
	{
		const float xTmp = ((y * B.z) - (z * B.y)); 
		const float yTmp = ((z * B.x) - (x * B.z)); 
		const float zTmp = ((x * B.y) - (y * B.x)); 

		return Vector3f(xTmp, yTmp, zTmp);
	}

	void Normalize()
	{
		const float length = sqrtf((x * x) + (y * y) + (z * z));

		x /= length;
		y /= length;
		z /= length;
	}

    void Print() const
    {
        printf("(%.02f, %.02f, %.02f)", x, y, z);
    }

	float getX() const
	{
		return x;
	}

	float getY() const
	{
		return y;
	}

	float getZ() const
	{
		return z;
	}

private:
    float x;
    float y;
    float z;
};

class Matrix4f
{
public:
    float m[4][4];

    Matrix4f()
    {
		InitIdentity();
    }
    
   
    Matrix4f Transpose() const
    {
        Matrix4f n;
        
        for (unsigned int i = 0 ; i < 4 ; i++) {
            for (unsigned int j = 0 ; j < 4 ; j++) {
                n.m[i][j] = m[j][i];
            }
        }
        
        return n;
    }


    inline void InitIdentity()
    {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
    }

    inline Matrix4f operator*(const Matrix4f& Right) const
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
    
    void Print() const
    {
        for (int i = 0 ; i < 4 ; i++) {
            printf("%f %f %f %f\n", m[i][0], m[i][1], m[i][2], m[i][3]);
        }       
    }
};

#endif	/* MATH_3D_H */
