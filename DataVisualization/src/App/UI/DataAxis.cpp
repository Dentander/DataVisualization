#include <imgui.h>
#include <UI/DataAxis.h>


void DataAxis::OnStart() {
	_data = AppObject::GetObjectOfType<Data>();
	_input = AppObject::GetObjectOfType<Input>();
	_cameraInput = AppObject::GetObjectOfType<CameraInput>();
}

void DataAxis::OnUpdate() {
	if (_cameraInput->IsViewerMode()) { return; }

	if (_input->IsKeyJustPressed("A")) { enabled = false; }
}

void DataAxis::OnDisabledUpdate() {
	if (_cameraInput->IsViewerMode()) { return; }
	
	if (_input->IsKeyJustPressed("A")) { enabled = true; }
}

void DataAxis::OnDraw() {
	if (_cameraInput->IsViewerMode() or _data->GetSize() == 0) { return; }

	ImGui::Begin("Select Axis");

	ImGui::Combo("Axis X", &currentAxisX, _data->GetColumns().data(), _data->GetColumns().size());
	ImGui::Combo("Axis Y", &currentAxisY, _data->GetColumns().data(), _data->GetColumns().size());
	ImGui::Combo("Axis Z", &currentAxisZ, _data->GetColumns().data(), _data->GetColumns().size());

	if (ImGui::Button("Save")) {
		_data->columnX = _data->GetColumns()[currentAxisX];
		_data->columnY = _data->GetColumns()[currentAxisY];
		_data->columnZ = _data->GetColumns()[currentAxisZ];

		currentAxisX = 0;
		currentAxisY = 0;
		currentAxisZ = 0;
		_data->isReady = true;
		enabled = false;
	}

	ImGui::End();
}
