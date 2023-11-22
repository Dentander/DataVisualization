#include <Visualization/Camera.h>


void Camera::OnStart() {
	_cameraInput = AppObject::GetObjectOfType<CameraInput>();
}

void Camera::OnUpdate() {
	UpdateRotation();
	UpdatePosition();
}

void Camera::UpdateRotation() {
	_rotation += _cameraInput->GetAngleDirection();
	if (_rotation.y >  3.14 / 2) { _rotation.y =  3.14 / 2; }
	if (_rotation.y < -3.14 / 2) { _rotation.y = -3.14 / 2; }
}


void Camera::UpdatePosition() {
	vec3f direction = vec3f(
		_cameraInput->GetMoveDirection().x,
		0, 
		_cameraInput->GetMoveDirection().y
	);

	_position += direction.Rotate(_rotation.x, _rotation.y);
}

vec3f Camera::GetPosition() {
	return _position;
}

vec2f Camera::GetRotation() {
	return _rotation;
}
