#include "Object.h"

Object::Object()
{
	currentView = GL_FILL;
	_rotate = Vector3f(0.0f, 0.0f, 0.0f);
	_translation = Vector3f(0.0f, 0.0f, 0.0f);
	_scale = Vector3f(1.0f, 1.0f, 1.0f);
}

void Object::changeWireframeView()
{
	if(currentView == GL_LINE)
		currentView = GL_FILL;
	else
		currentView = GL_LINE;
	glPolygonMode( GL_FRONT_AND_BACK, currentView);
}

void Object::setRotation(Vector3f& rot)
{
	_rotate += rot;
}

Vector3f& Object::getRotation(void)
{
	return _rotate;
}

void Object::setScaling(Vector3f& sca)
{
	_scale += sca;
}

Vector3f& Object::getScaling(void)
{
	return _scale;
}

void Object::setTranslation(Vector3f& tra)
{
	_translation += tra;
}
	
Vector3f& Object::getTranslation(void)
{
	return _translation;
}