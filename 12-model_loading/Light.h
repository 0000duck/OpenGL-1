#ifndef __LIGHT_H
#define __LIGHT_H

#include "math_3d.h"

class Light
{
public:
	Vector4f _lightColorAmbient;
	//float _intensityAmbient;
	Vector4f _lightColorDiffuse;
	//float _intensityDiffuse;
	Vector3f _direction;
};

#endif