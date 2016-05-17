#include "Camera.h"

Camera::Camera()
{
	speed = 0.1f;
	setCameraPosition(Vector3f(0.0f, 0.0f, -5.0f));
	setCameraTarget(Vector3f(0.0f, 0.0f, 1.0f));
	setCameraUpDirection(Vector3f(0.0f, 1.0f, 0.0f));

	Vector3f HTarget(_target.getX(), 0.0, _target.getZ());
    HTarget.Normalize();
    if (HTarget.getZ() >= 0.0f) {
        if (HTarget.getX() >= 0.0f) {
            _angleH = 360.0f - ToDegree(asin(HTarget.getZ()));
        } else {
            _angleH = 180.0f + ToDegree(asin(HTarget.getZ()));
        }
    } else {
        if (HTarget.getX() >= 0.0f) {
            _angleH = ToDegree(asin(-HTarget.getZ()));
        } else {
            _angleH = 90.0f + ToDegree(asin(-HTarget.getZ()));
        }
    }

    _angleV = -ToDegree(asin(_target.getY()));
}

void Camera::setCameraPosition(Vector3f& pos)
{
	_position = pos;
}

void Camera::changeCameraPosition(Vector3f& direction)
{
	if (direction.getY() < 0)
		_position -= (_target * speed);
	else if (direction.getY() > 0)
		_position += (_target * speed);
	if (direction.getX() < 0){
		Vector3f tmp = _target.Cross(_up);
		tmp.Normalize();
		_position += (tmp * speed);
	} else if (direction.getX() > 0){
		Vector3f tmp = _up.Cross(_target);
		tmp.Normalize();
		_position += (tmp * speed);
	}
}

void Camera::setCameraUpDirection(Vector3f& up)
{
	_up = up;
}

void Camera::setCameraTarget(Vector3f& tgt)
{
	_target = tgt;
	_target.Normalize();
}

void Camera::changeCameraTarget(Vector3f& tgt)
{
	_angleH += tgt.getX() / 20.0f;
    _angleV += tgt.getY() / 20.0f;

	const Vector3f Vaxis(0.0f, 1.0f, 0.0f);

    // Rotate the view vector by the horizontal angle around the vertical axis
    Vector3f View = Vector3f(1.0f, 0.0f, 0.0f);
    View.rotate(_angleH, Vaxis);
    View.Normalize();

    // Rotate the view vector by the vertical angle around the horizontal axis
    Vector3f Haxis = Vaxis.Cross(View);
    Haxis.Normalize();
    View.rotate(_angleV, Haxis);
       
    _target = View;
    _target.Normalize();
    _up = _target.Cross(Haxis);
    _up.Normalize();
}

Vector3f Camera::getCameraPosition(void) const
{
	return _position;
}

Vector3f Camera::getCameraUpDirection(void) const
{
	return _up;
}

Vector3f Camera::getCameraTarget(void) const
{
	return _target;
}

float Camera::getCameraSpeed()
{
	return speed;
}

void Camera::update()
{
    const Vector3f Vaxis(0.0f, 1.0f, 0.0f);

    // Rotate the view vector by the horizontal angle around the vertical axis
    Vector3f View = Vector3f(1.0f, 0.0f, 0.0f);
    View.rotate(_angleH, Vaxis);
    View.Normalize();

    // Rotate the view vector by the vertical angle around the horizontal axis
    Vector3f Haxis = Vaxis.Cross(View);
    Haxis.Normalize();
    View.rotate(_angleV, Haxis);
       
    _target = View;
    _target.Normalize();
    _up = _target.Cross(Haxis);
    _up.Normalize();

}