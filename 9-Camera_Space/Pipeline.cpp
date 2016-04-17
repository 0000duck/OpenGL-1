#include "Pipeline.h"
#include <math.h>

const float M_PI = 3.1415;

/* This displacement puts the object away from the near clipping plane so we avoid to get our object clipped */
const float zDisplacement = 5.0f;

Pipeline::Pipeline()
{
	this->_rotation = Vector3f(0.0f, 0.0f, 0.0f);
	this->_scaling = Vector3f(1.0f, 1.0f, 1.0f);
	this->_translation = Vector3f(0.0f, 0.0f, zDisplacement);
	/* The following parameters will give the inputs to build the projection matrix to give the feel of depth */
	setWinSize(winWidth, winHeight);
	setFOV(30.0f);
	setNearClippingPlane(0.1f);
	setFarClippingPlane(100.0f);

	setCameraPosition(Vector3f(3.0f, 0.0f, -3.0f));
	setCameraTarget(Vector3f(0.75f, 0.0f, 1.0f)); 
	setCameraUpDirection(Vector3f(0.0f, 1.0f, 0.0f));

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
	this->_translation = Vector3f(x, y, z + zDisplacement);				// z-displacement used to stay away from the near clipping plane
}

void Pipeline::setFOV(float FOV)
{
	_projection.FOV = FOV;
}

void Pipeline::setWinSize(unsigned int width, unsigned int height)
{
	_projection.Width = width;
	_projection.Height = height;
}

void Pipeline::setNearClippingPlane(float zNear)
{
	_projection.zNear = zNear;
}

void Pipeline::setFarClippingPlane(float zFar)
{
	_projection.zFar = zFar;
}

void Pipeline::setCameraPosition(Vector3f& pos)
{
	_camera.position = pos;
}

void Pipeline::setCameraUpDirection(Vector3f& Up)
{
	_camera.Up = Up;
}

void Pipeline::setCameraTarget(Vector3f& target)
{
	_camera.target = target;
}

void Pipeline::getObjectScaling(Matrix4f& dst)
{
	dst.m[0][0] = this->_scaling.getX();
	dst.m[1][1] = this->_scaling.getY();
	dst.m[2][2] = this->_scaling.getZ();
}

void Pipeline::getObjectRotation(Matrix4f& dst)
{
	float angle;
	Matrix4f mX, mY, mZ;
	if(this->_rotation.getX()) {
		//rotate around X
		angle = ToRadian(this->_rotation.getX());
		mX.m[1][1] = cosf(angle);
		mX.m[1][2] = -sinf(angle);
		mX.m[2][1] = sinf(angle);
		mX.m[2][2] = cosf(angle);
	}

	if(this->_rotation.getY()) {
		//rotate around y
		angle = ToRadian(this->_rotation.getY());
		mY.m[0][0] = cosf(angle);
		mY.m[0][2] = -sinf(angle);
		mY.m[2][0] = sinf(angle);
		mY.m[2][2] = cosf(angle);
	}

	if(this->_rotation.getZ()) {
		//rotate around z
		angle = ToRadian(this->_rotation.getZ());
		mZ.m[0][0] = cosf(angle);
		mZ.m[0][1] = -sinf(angle);
		mZ.m[1][0] = sinf(angle);
		mZ.m[1][1] = cosf(angle);
	}
	dst = mZ * mY * mX;
}
	
void Pipeline::getObjectTranslation(Matrix4f& dst)
{
	dst.m[0][3] = this->_translation.getX();
	dst.m[1][3] = this->_translation.getY();
	dst.m[2][3] = this->_translation.getZ();
}

void Pipeline::getPerspctiveProjection(Matrix4f& dst)
{
	const float ar = ((float)_projection.Width / _projection.Height);
	const float rangeZ = (_projection.zNear - _projection.zFar);
	const float focalLength = (1.0f / (tanf(ToRadian(_projection.FOV / 2.0f))));

	dst.m[0][0] = (focalLength) / ar;
	dst.m[1][1] = focalLength;
	dst.m[2][2] = (-_projection.zNear - _projection.zFar) / rangeZ;
	dst.m[2][3] = (2.0f * _projection.zNear * _projection.zFar) / rangeZ;
	dst.m[3][2] = 1.0f;
	dst.m[3][3] = 0.0f;
}

void Pipeline::getCameraTranslation(Matrix4f& dst)
{
	dst.m[0][3] = -(this->_camera.position.getX());
	dst.m[1][3] = -(this->_camera.position.getY());
	dst.m[2][3] = -(this->_camera.position.getZ());
}

void Pipeline::getCameraOrientation(Matrix4f& dst)
{
	
	Vector3f N = _camera.target - _camera.position;
	N.Normalize();	//lookAt normalized

	Vector3f tmp = _camera.Up.Cross(N);
	Vector3f V = N.Cross(tmp);
	V.Normalize();
	
	Vector3f U = N.Cross(V);
	U.Normalize();

	dst.m[0][0] = U.getX();
	dst.m[0][1] = U.getY();
	dst.m[0][2] = U.getZ();
	dst.m[1][0] = V.getX();
	dst.m[1][1] = V.getY();
	dst.m[1][2] = V.getZ();
	dst.m[2][0] = N.getX();
	dst.m[2][1] = N.getY();
	dst.m[2][2] = N.getZ();
}

Matrix4f const *Pipeline::getMatrix(void)
{
	Matrix4f translationM, rotationM, scalingM, projectionM, cameraPos, cameraOrientation;
	getObjectScaling(scalingM);
	getObjectTranslation(translationM);
	getObjectRotation(rotationM);
	getPerspctiveProjection(projectionM);
	getCameraTranslation(cameraPos);
	getCameraOrientation(cameraOrientation);

	this->_matrix = projectionM * cameraOrientation * cameraPos * translationM * rotationM * scalingM;
	return &this->_matrix;
}