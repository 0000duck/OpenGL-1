#ifndef __LIGHT_H
#define __LIGHT_H

#include "math_3d.h"

class Light
{
public:
	Light(Vector3f lightColor, float intensityAmbient, float intensityDiffuse, Vector3f direction);

	Vector3f _lightColor;
	float _intensityAmbient;
	float _intensityDiffuse;
	Vector3f _direction;
};

#endif