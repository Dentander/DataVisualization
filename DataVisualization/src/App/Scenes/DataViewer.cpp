#include <Scenes/DataViewer.h>
#include <Visualization/Data.h>
#include <Visualization/CameraInput.h>
#include <Visualization/Camera.h>
#include <Visualization/Spheres.h>
#include <Visualization/Background.h>
#include <UI/DataLoader.h>
#include <UI/DataAxis.h>
#include <UI/AxisScaler.h>
#include <Visualization/Point3D.h>
#include <UI/MinMaxAvgTable.h>


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
	spheres->Instaniate(Tag::Visualization, 0, 10);

	Point3D* p = new Point3D();
	p->Instaniate(Tag::UI, 10000, 10000);

	// ========== UI ==========
	DataLoader* dataFrameLoader = new DataLoader();
	DataAxis* dataAxes = new DataAxis();
	AxisScaler* axisScaler = new AxisScaler();
	MinMaxAvgTable* minMaxAvgTable = new MinMaxAvgTable();

	dataFrameLoader->Instaniate(Tag::UI, 0, 1000);
	dataAxes->Instaniate(Tag::UI, 0, 1000);
	axisScaler->Instaniate(Tag::UI, 0, 1000);
	minMaxAvgTable->Instaniate(Tag::UI, 0, 1000);
}
