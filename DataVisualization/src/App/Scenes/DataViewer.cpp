#include <Scenes/DataViewer.h>
#include <Visualization/CameraInput.h>
#include <Visualization/Camera.h>


void DataViewer::OnInstaniate() {
	CameraInput* _cameraInput = new CameraInput();
	Camera* _camera = new Camera();

	_cameraInput->Instaniate();
	_camera->Instaniate();
}
