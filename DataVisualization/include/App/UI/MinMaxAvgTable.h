#pragma once
#include <Visualization/Data.h>
#include <Systems/Input.h>
#include <Visualization/CameraInput.h>


class MinMaxAvgTable : public AppObject {
private:
	Data* _data;
	Input* _input;
	CameraInput* _cameraInput;

	bool _cached = false;
	float _minX=9999999, _minY=9999999, _minZ=9999999;
	float _maxX=-9999999, _maxY=-9999999, _maxZ=-9999999;
	float _avgX=0, _avgY=0, _avgZ=0;

	void OnStart();
	void OnUpdate();
	void OnDisabledUpdate();
	void OnDraw();

	void Cache();
};

