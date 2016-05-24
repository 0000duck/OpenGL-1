#ifndef __NODE_H
#define __NODE_H

#include "math_3d.h"
#include <memory>
#include "Camera.h"
#include <vector>

class Node
{
public:
	Node();
	void setVBO(unsigned int newVBO);
	int getVBO(unsigned int index);

	void setIBO(unsigned int newIBO);
	int getIBO(unsigned int index);

	void setTBO(unsigned int newTBO);
	int getTBO(unsigned int index);

	void setUBO(unsigned int newUBO);
	int getUBO(unsigned int index);

	void setNumIndices(unsigned int n);
	unsigned int getNumIndices(unsigned int index);

	void setScaling(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setTranslation(float x, float y, float z);

	void setFOV(float FOV);
	void setWinSize(unsigned int width, unsigned int height);
	void setNearClippingPlane(float zNear);
	void setFarClippingPlane(float zFar);

	void setCameraPosition(float x, float y, float z);
	void setCameraTarget(float x, float y, float z);
	void setCameraUpDirection(float x, float y, float z);

	Matrix4f const *getMatrix(void);
	Matrix4f const *getCamera(void);

	Camera _camera;
	unsigned int numMeshes;
private:
	void getObjectScaling(Matrix4f& dst);
	void getObjectRotation(Matrix4f& dst);
	void getObjectTranslation(Matrix4f& dst);
	void getPerspctiveProjection(Matrix4f& dst);
	void getCameraTranslation(Matrix4f& dst);
	void getCameraOrientation(Matrix4f& dst);

private:
	std::vector<Node> children;
	std::shared_ptr<unsigned int> _indices;

	
	std::vector<unsigned int> VBO;
	std::vector<unsigned int> TBO;
	std::vector<unsigned int> numIndices;
	std::vector<unsigned int> IBO;
	std::vector<unsigned int> UBO;
	

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

	Matrix4f _transformationMatrix;
	Matrix4f _cameraMatrix;
};

#endif