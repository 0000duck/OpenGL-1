#include "Pipeline.h"
#include <math.h>

Pipeline::Pipeline()
{
	/* The following parameters will give the inputs to build the projection matrix to give the feel of depth */
	setWinSize(winWidth, winHeight);
	setFOV(30.0f);
	setNearClippingPlane(1.0f);
	setFarClippingPlane(100.0f);

}

void Pipeline::setScaling(float x, float y, float z)
{
	_object.setScaling(Vector3f(x, y, z));
}

void Pipeline::setRotation(float x, float y, float z)
{
	_object.setRotation(Vector3f(x, y, z));
}

void Pipeline::setTranslation(float x, float y, float z)
{
	_object.setTranslation(Vector3f(x, y, z));
}

void Pipeline::changeWireframeView(void)
{
	_object.changeWireframeView();
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

void Pipeline::setCameraPosition(float x, float y, float z)
{
	_camera.changeCameraPosition(Vector3f(x, y, z));
}

void Pipeline::setCameraUpDirection(float x, float y, float z)
{
	_camera.setCameraUpDirection(Vector3f(x, y, z));
}

void Pipeline::setCameraTarget(float x, float y, float z)
{
	_camera.changeCameraTarget(Vector3f(x, y, z));
}

void Pipeline::getObjectScaling(Matrix4f& dst)
{
	dst.m[0][0] = _object.getScaling().getX();
	dst.m[1][1] = _object.getScaling().getY();
	dst.m[2][2] = _object.getScaling().getZ();
}

void Pipeline::getObjectRotation(Matrix4f& dst)
{
	float angle;
	Matrix4f mX, mY, mZ;
	if(_object.getRotation().getX()) {
		//rotate around X
		angle = ToRadian(_object.getRotation().getX());
		mX.m[1][1] = cosf(angle);
		mX.m[1][2] = -sinf(angle);
		mX.m[2][1] = sinf(angle);
		mX.m[2][2] = cosf(angle);
	}

	if(_object.getRotation().getY()) {
		//rotate around y
		angle = ToRadian(_object.getRotation().getY());
		mY.m[0][0] = cosf(angle);
		mY.m[0][2] = -sinf(angle);
		mY.m[2][0] = sinf(angle);
		mY.m[2][2] = cosf(angle);
	}

	if(_object.getRotation().getZ()) {
		//rotate around z
		angle = ToRadian(_object.getRotation().getZ());
		mZ.m[0][0] = cosf(angle);
		mZ.m[0][1] = -sinf(angle);
		mZ.m[1][0] = sinf(angle);
		mZ.m[1][1] = cosf(angle);
	}
	dst = mZ * mY * mX;
}
	
void Pipeline::getObjectTranslation(Matrix4f& dst)
{
	dst.m[0][3] = _object.getTranslation().getX();
	dst.m[1][3] = _object.getTranslation().getY();
	dst.m[2][3] = _object.getTranslation().getZ();
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
	dst.m[0][3] = -(_camera.getCameraPosition().getX());
	dst.m[1][3] = -(_camera.getCameraPosition().getY());
	dst.m[2][3] = -(_camera.getCameraPosition().getZ());
}

void Pipeline::getCameraOrientation(Matrix4f& dst)
{
	
	Vector3f N = _camera.getCameraTarget();
	N.Normalize();	//lookAt normalized

	Vector3f U = _camera.getCameraUpDirection();
	U.Normalize();
	U = U.Cross(N);
	Vector3f V = N.Cross(U);
	V.Normalize();
	
	//Vector3f U = N.Cross(V);
	//U.Normalize();

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

	/* I commented the camera orientation because it's outside the scope of this particular lesson */
	_matrix = projectionM * cameraOrientation * cameraPos * translationM * rotationM * scalingM;
	return &_matrix;
}