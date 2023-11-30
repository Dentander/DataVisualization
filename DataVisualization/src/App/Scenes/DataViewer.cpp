#include <Scenes/DataViewer.h>
#include <Visualization/Data.h>
#include <Visualization/CameraInput.h>
#include <Visualization/Camera.h>
#include <Visualization/Spheres.h>
#include <Visualization/Background.h>
#include <UI/DataLoader.h>
#include <UI/DataAxis.h>


void DataViewer::OnInstaniate() {
	// ========== 3D RENDER ==========
	Data* data = new Data();
	CameraInput* cameraInput = new CameraInput();
	Camera* camera = new Camera();

	Background* background = new Background();
	Spheres* spheres = new Spheres();
	
	
	data->Instaniate(Tag::Camera);
	cameraInput->Instaniate(Tag::Camera);
	camera->Instaniate(Tag::Camera);
	
	background->Instaniate(Tag::Visualization, 0, 0);
	spheres->Instaniate(Tag::Visualization, 0, 1);

	// ========== UI ==========
	DataLoader* _dataFrameLoader = new DataLoader();
	DataAxis* _dataAxes = new DataAxis();

	_dataFrameLoader->Instaniate(Tag::UI, 0, std::numeric_limits<float>::max());
	_dataAxes->Instaniate(Tag::UI, 0, std::numeric_limits<float>::max());
}
