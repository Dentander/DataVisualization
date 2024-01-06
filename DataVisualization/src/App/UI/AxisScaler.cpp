#include <imgui.h>
#include <UI/AxisScaler.h> 


void AxisScaler::OnStart() {
	_data = AppObject::GetObjectOfType<Data>();
	_input = AppObject::GetObjectOfType<Input>();
	_cameraInput = AppObject::GetObjectOfType<CameraInput>();
	enabled = false;
}

void AxisScaler::OnUpdate() {
	if (_cameraInput->IsViewerMode()) { return; }
	if (_input->IsKeyJustPressed("S")) { enabled = false; }
}

void AxisScaler::OnDisabledUpdate() {
	if (_cameraInput->IsViewerMode()) { return; }
	if (_input->IsKeyJustPressed("S")) { enabled = true; }
}

void AxisScaler::OnDraw() {
	if (_cameraInput->IsViewerMode() or _data->GetSize() == 0) { return; }

	ImGui::Begin("Axis Scaler");
	ImGui::SliderFloat("Axis X", &_data->userScale.x, 0.05, 20);
	ImGui::SliderFloat("Axis Y", &_data->userScale.y, 0.05, 20);
	ImGui::SliderFloat("Axis Z", &_data->userScale.z, 0.05, 20);
	ImGui::End();
}
