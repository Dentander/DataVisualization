#include <imgui.h>
#include <UI/DataLoader.h>


void DataLoader::OnStart() {
	_data = AppObject::GetObjectOfType<Data>();
	_input = AppObject::GetObjectOfType<Input>();
	_cameraInput = AppObject::GetObjectOfType<CameraInput>();
	_dataAxis = AppObject::GetObjectOfType<DataAxis>();
	ImGuiFileDialog::Instance()->OpenDialog("DataFrameLoader", "Choose File", ".csv", ".");
}

void DataLoader::OnUpdate() {
	if (_cameraInput->IsViewerMode()) { return; }

	if (_input->IsKeyJustPressed("L")) {
		if (ImGuiFileDialog::Instance()->IsOpened()) { ImGuiFileDialog::Instance()->Close(); }
		else { ImGuiFileDialog::Instance()->OpenDialog("DataFrameLoader", "Choose File", ".csv", "."); }
	}
}

void DataLoader::OnDraw() {
	if (_cameraInput->IsViewerMode()) { return; }

	if (ImGuiFileDialog::Instance()->Display("DataFrameLoader")) {
		if (ImGuiFileDialog::Instance()->IsOk()) {
			std::string path = ImGuiFileDialog::Instance()->GetFilePathName();
			_data->isReady = false;
			_data->ReadCsv(path);
			_dataAxis->enabled = true;
		}
		ImGuiFileDialog::Instance()->Close();
	}
}


