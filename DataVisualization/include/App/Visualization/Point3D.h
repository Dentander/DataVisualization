#pragma once
#include <BaseClasses/AppObject.h>
#include <AdditionalStd/vec3.h>
#include <Systems/Screen.h>
#include <Visualization/Camera.h>


class Point3D : public AppObject, public vec3<float> {
private:
	Screen* _screen;
	Camera* _camera;

	void OnStart();
	void OnDraw();

public:
	vec2f Project();
};

