#ifndef __PIPELINE_H
#define __PIPELINE_H

#include "math_3d.h"

class Pipeline {
public:
	Pipeline();
	void setScaling(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setTranslation(float x, float y, float z);
	Matrix4f const *getMatrix(void);

private:
	void scalingV2M(Matrix4f& dst);
	void rotationV2M(Matrix4f& dst);
	void translationV2M(Matrix4f& dst);
	Vector3f _scaling;
	Vector3f _rotation;
	Vector3f _translation;
	Matrix4f _matrix;
};

#endif
