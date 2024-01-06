#pragma once
#include <Visualization/Data.h>
#include <Visualization/CameraInput.h>


class AxisScaler : public AppObject {
private:
	Data* _data;
	Input* _input;
	CameraInput* _cameraInput;

	void OnStart();
	void OnUpdate();
	void OnDisabledUpdate();
	void OnDraw();
};

