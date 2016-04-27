//wrapper class to interact with the pipeline to handle a camera

#include "glew.h"
#include "math_3d.h"

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