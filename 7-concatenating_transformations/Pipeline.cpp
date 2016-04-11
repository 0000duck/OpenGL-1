#include "Pipeline.h"
#include <math.h>

const float M_PI = 3.1415;

Pipeline::Pipeline()
{
	this->_rotation = Vector3f(0.0f, 0.0f, 0.0f);
	this->_scaling = Vector3f(1.0f, 1.0f, 1.0f);
	this->_translation = Vector3f(0.0f, 0.0f, 0.0f);
}


void Pipeline::setScaling(float x, float y, float z)
{
	this->_scaling = Vector3f(x, y, z);
}

void Pipeline::setRotation(float x, float y, float z)
{
	this->_rotation = Vector3f(x, y, z);
}

void Pipeline::setTranslation(float x, float y, float z)
{
	this->_translation = Vector3f(x, y, z);
}

void Pipeline::scalingV2M(Matrix4f& dst)
{
	dst.m[0][0] = this->_scaling.getX();
	dst.m[1][1] = this->_scaling.getY();
	dst.m[2][2] = this->_scaling.getZ();
}

void Pipeline::rotationV2M(Matrix4f& dst)
{
	float angle;
	Matrix4f mX, mY, mZ;
	if(this->_rotation.getX()) {
		//rotate around X
		angle = ToRadian(this->_rotation.getX());
		mX.m[1][1] = cos(angle);
		mX.m[1][2] = -sin(angle);
		mX.m[2][1] = sin(angle);
		mX.m[2][2] = cos(angle);
	}

	if(this->_rotation.getY()) {
		//rotate around y
		angle = ToRadian(this->_rotation.getY());
		mY.m[0][0] = cos(angle);
		mY.m[0][2] = sin(angle);
		mY.m[2][0] = -sin(angle);
		mY.m[2][2] = cos(angle);
	}

	if(this->_rotation.getZ()) {
		//rotate around z
		angle = ToRadian(this->_rotation.getZ());
		mZ.m[0][0] = cos(angle);
		mZ.m[0][1] = -sin(angle);
		mZ.m[1][0] = sin(angle);
		mZ.m[1][1] = cos(angle);
	}
	dst = mX * mY * mZ;
}
	
void Pipeline::translationV2M(Matrix4f& dst)
{
	dst.m[0][3] = this->_translation.getX();
	dst.m[1][3] = this->_translation.getY();
	dst.m[2][3] = this->_translation.getZ();
}

Matrix4f const *Pipeline::getMatrix(void)
{
	Matrix4f translationM, rotationM, scalingM;
	scalingV2M(scalingM);
	translationV2M(translationM);
	rotationV2M(rotationM);
	this->_matrix = translationM * rotationM * scalingM;
	return &this->_matrix;
}