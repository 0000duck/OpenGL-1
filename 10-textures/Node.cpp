#include "Node.h"

Node::Node()
{
	_rotation = Vector3f(0.0f, 0.0f, 0.0f);
	_scaling = Vector3f(1.0f, 1.0f, 1.0f);
	_translation = Vector3f(0.0f, 0.0f, 0.0f);
	setWinSize(winWidth, winHeight);
	setFOV(30.0f);
	setNearClippingPlane(1.0f);
	setFarClippingPlane(100.0f);
}

void Node::setScaling(float x, float y, float z)
{
	_scaling += Vector3f(x, y, z);
}

void Node::setRotation(float x, float y, float z)
{
	_rotation += Vector3f(x, y, z);
}

void Node::setTranslation(float x, float y, float z)
{
	_translation += Vector3f(x, y, z);
}

void Node::setFOV(float FOV)
{
	_projection.FOV = FOV;
}

void Node::setWinSize(unsigned int width, unsigned int height)
{
	_projection.Width = width;
	_projection.Height = height;
}

void Node::setNearClippingPlane(float zNear)
{
	_projection.zNear = zNear;
}

void Node::setFarClippingPlane(float zFar)
{
	_projection.zFar = zFar;
}

void Node::setCameraPosition(float x, float y, float z)
{
	_camera.changeCameraPosition(Vector3f(x, y, z));
}

void Node::setCameraUpDirection(float x, float y, float z)
{
	_camera.setCameraUpDirection(Vector3f(x, y, z));
}

void Node::setCameraTarget(float x, float y, float z)
{
	_camera.changeCameraTarget(Vector3f(x, y, z));
}

void Node::getObjectScaling(Matrix4f& dst)
{
	dst.m[0][0] = _scaling.getX();
	dst.m[1][1] = _scaling.getY();
	dst.m[2][2] = _scaling.getZ();
}

void Node::getObjectRotation(Matrix4f& dst)
{
	float angle;
	Matrix4f mX, mY, mZ;
	if(this->_rotation.getX()) {
		//rotate around X
		angle = ToRadian(_rotation.getX());
		mX.m[1][1] = cos(angle);
		mX.m[1][2] = -sin(angle);
		mX.m[2][1] = sin(angle);
		mX.m[2][2] = cos(angle);
	}

	if(this->_rotation.getY()) {
		//rotate around y
		angle = ToRadian(_rotation.getY());
		mY.m[0][0] = cos(angle);
		mY.m[0][2] = sin(angle);
		mY.m[2][0] = -sin(angle);
		mY.m[2][2] = cos(angle);
	}

	if(this->_rotation.getZ()) {
		//rotate around z
		angle = ToRadian(_rotation.getZ());
		mZ.m[0][0] = cos(angle);
		mZ.m[0][1] = -sin(angle);
		mZ.m[1][0] = sin(angle);
		mZ.m[1][1] = cos(angle);
	}
	dst = mX * mY * mZ;
}
	
void Node::getObjectTranslation(Matrix4f& dst)
{
	dst.m[0][3] = _translation.getX();
	dst.m[1][3] = _translation.getY();
	dst.m[2][3] = _translation.getZ();
}

void Node::getPerspctiveProjection(Matrix4f& dst)
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

void Node::getCameraTranslation(Matrix4f& dst)
{
	dst.m[0][3] = -(_camera.getCameraPosition().getX());
	dst.m[1][3] = -(_camera.getCameraPosition().getY());
	dst.m[2][3] = -(_camera.getCameraPosition().getZ());
}

void Node::getCameraOrientation(Matrix4f& dst)

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

Matrix4f const *Node::getMatrix(void)
{
	Matrix4f translationM, rotationM, scalingM, projectionM, cameraPos, cameraOrientation;
	getObjectScaling(scalingM);
	getObjectTranslation(translationM);
	getObjectRotation(rotationM);
	getPerspctiveProjection(projectionM);
	getCameraTranslation(cameraPos);
	getCameraOrientation(cameraOrientation);

	_transformationMatrix = projectionM * cameraOrientation * cameraPos * translationM * rotationM * scalingM;
	return &_transformationMatrix;
}

void Node::setVBO(unsigned int newVBO)
{
	VBO = newVBO;
}

unsigned int Node::getVBO()
{
	return VBO;
}

void Node::setIBO(unsigned int newIBO)
{
	IBO = newIBO;
}

unsigned int Node::getIBO()
{
	return IBO;
}

void Node::setTBO(unsigned int newTBO)
{
	TBO = newTBO;
}

unsigned int Node::getTBO()
{
	return TBO;
}

void Node::setNumIndices(unsigned int n)
{
	numIndices = n;
}

unsigned int Node::getNumIndices(void)
{
	return numIndices;
}