#ifndef __PIPELINE_H
#define __PIPELINE_H

#include "math_3d.h"
#include "Camera.h"
#include "Object.h"

class Pipeline {
public:
	Pipeline();
	void setScaling(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setTranslation(float x, float y, float z);
	void changeWireframeView(void);

	void setFOV(float FOV);
	void setWinSize(unsigned int width, unsigned int height);
	void setNearClippingPlane(float zNear);
	void setFarClippingPlane(float zFar);

	void setCameraPosition(float x, float y, float z);
	void setCameraTarget(float x, float y, float z);
	void setCameraUpDirection(float x, float y, float z);

	Matrix4f const *getMatrix(void);

private:
	void getObjectScaling(Matrix4f& dst);
	void getObjectRotation(Matrix4f& dst);
	void getObjectTranslation(Matrix4f& dst);
	void getPerspctiveProjection(Matrix4f& dst);
	void getCameraTranslation(Matrix4f& dst);
	void getCameraOrientation(Matrix4f& dst);
	
	struct {
        float FOV;
        unsigned int Width;
        unsigned int Height;
        float zNear;
        float zFar;
    }_projection;

	Object _object;
	Camera _camera;

	Matrix4f _matrix;
};

#endif
