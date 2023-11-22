#pragma once
#include <BaseClasses/AppObject.h>
#include <Visualization/CameraInput.h>
#include <AdditionalStd/vec3.h>


class Camera : public AppObject {
private:
	CameraInput* _cameraInput;
	vec3f _position = vec3f(0);
	vec2f _rotation = vec2f(0);

	void OnStart();
	void OnUpdate();

	void UpdateRotation();
	void UpdatePosition();

public:
	vec3f GetPosition();
	vec2f GetRotation();
};

