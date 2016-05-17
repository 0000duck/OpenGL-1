#include "Light.h"

Light::Light(Vector3f lightColor, float intensityAmbient, float intensityDiffuse, Vector3f direction):
	_lightColor(lightColor), _intensityAmbient(intensityAmbient),
	_intensityDiffuse(intensityDiffuse), _direction(direction)
{
}
