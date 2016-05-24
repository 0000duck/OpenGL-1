#ifndef __MATERIAL_H
#define __MATERIAL_H

#include "math_3d.h"
#include "Light.h"

class Material
{
public:
	Light _light;
	Vector4f _specularColor;
	//float _specularIntensity;
	float _specularPower;
	//Texture _texture;
};

#endif