#ifndef __CAMERA_H
#define __CAMERA_H

#include "math_3d.h"

/* This class handles a camera transformation view */
/* Starting from 3 vectors (position, target, up) we are able to tilt, zoom and move the camera */

class Camera {
public:
	Camera();

	void setCameraPosition(Vector3f& pos);
	void changeCameraPosition(Vector3f& direction);
	void setCameraUpDirection(Vector3f& up);
	void setCameraTarget(Vector3f& tgt);
	void changeCameraTarget(Vector3f& tgt);

	Vector3f getCameraPosition(void) const;
	Vector3f getCameraUpDirection(void) const;
	Vector3f getCameraTarget(void) const;
	float getCameraSpeed(void);

private:
	void update();

	Vector3f _position;
	Vector3f _up;
	Vector3f _target;
	float speed;
	float _angleH;
	float _angleV;
};

#endif