#pragma once
#include <Visualization/Data.h>
#include <Systems/Input.h>
#include <Visualization/CameraInput.h>
#include "DataAxis.h"


class DataLoader : public AppObject {
private:
	Data* _data;
	Input* _input;
	CameraInput* _cameraInput;
	DataAxis* _dataAxis;

	void OnStart();
	void OnUpdate();
	void OnDraw();
};

