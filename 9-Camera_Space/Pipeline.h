#ifndef __PIPELINE_H
#define __PIPELINE_H

#include "math_3d.h"

class Pipeline {
public:
	Pipeline();
	void setScaling(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setTranslation(float x, float y, float z);

	void setFOV(float FOV);
	void setWinSize(unsigned int width, unsigned int height);
	void setNearClippingPlane(float zNear);
	void setFarClippingPlane(float zFar);

	void setCameraPosition(Vector3f& pos);
	void setCameraTarget(Vector3f& target);
	void setCameraUpDirection(Vector3f& Up);

	Matrix4f const *getMatrix(void);

private:
	void getObjectScaling(Matrix4f& dst);
	void getObjectRotation(Matrix4f& dst);
	void getObjectTranslation(Matrix4f& dst);
	void getPerspctiveProjection(Matrix4f& dst);
	void getCameraTranslation(Matrix4f& dst);
	void getCameraOrientation(Matrix4f& dst);

	Vector3f _scaling;
	Vector3f _rotation;
	Vector3f _translation;
	
	struct {
        float FOV;
        unsigned int Width;
        unsigned int Height;
        float zNear;
        float zFar;
    }_projection;

	struct {
		Vector3f target;
		Vector3f Up;
		Vector3f position;
	}_camera;

	Matrix4f _matrix;
};

#endif
