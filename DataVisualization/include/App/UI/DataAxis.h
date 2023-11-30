#pragma once
#include <Visualization/Data.h>
#include <Visualization/CameraInput.h>


class DataAxis : public AppObject {
private:
	Data* _data;
	Input* _input;
	CameraInput* _cameraInput;

	int currentAxisX = 0;
	int currentAxisY = 0;
	int currentAxisZ = 0;
	
	void OnStart();
	void OnUpdate();
	void OnDisabledUpdate();
	void OnDraw();
};

