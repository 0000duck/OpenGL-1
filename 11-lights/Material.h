#ifndef __MATERIAL_H
#define __MATERIAL_H

class Material
{
public:
	Material(float specularIntensity, float specularPower);
	float _specularIntensity;
	float _specularPower;
};

#endif