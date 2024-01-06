#include <imgui.h>
#include <UI/MinMaxAvgTable.h>


void MinMaxAvgTable::OnStart() {
	_data = AppObject::GetObjectOfType<Data>();
	_input = AppObject::GetObjectOfType<Input>();
	_cameraInput = AppObject::GetObjectOfType<CameraInput>();
	enabled = false;
}

void MinMaxAvgTable::OnUpdate() {
	if (_cameraInput->IsViewerMode()) { return; }

	if (_input->IsKeyJustPressed("M")) { enabled = false; }
}

void MinMaxAvgTable::OnDisabledUpdate() {
	if (_cameraInput->IsViewerMode()) { return; }

	if (_input->IsKeyJustPressed("M")) { enabled = true; }
}

void MinMaxAvgTable::OnDraw() {
	if (_cameraInput->IsViewerMode() or _data->GetSize() == 0) { return; }

	Cache();

	ImGui::Begin("Select Axis");

	ImGui::Text("Min");
	if (ImGui::BeginTable("Min", 3)) {

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text(_data->columnX.c_str());
		ImGui::TableSetColumnIndex(1);
		ImGui::Text(_data->columnY.c_str());
		ImGui::TableSetColumnIndex(2);
		ImGui::Text(_data->columnZ.c_str());

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text(std::to_string(_minX).c_str());
		ImGui::TableSetColumnIndex(1);
		ImGui::Text(std::to_string(_minY).c_str());
		ImGui::TableSetColumnIndex(2);
		ImGui::Text(std::to_string(_minZ).c_str());

		ImGui::EndTable();
	}

	ImGui::Text("Max");
	if (ImGui::BeginTable("Min", 3)) {

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text(_data->columnX.c_str());
		ImGui::TableSetColumnIndex(1);
		ImGui::Text(_data->columnY.c_str());
		ImGui::TableSetColumnIndex(2);
		ImGui::Text(_data->columnZ.c_str());

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text(std::to_string(_maxX).c_str());
		ImGui::TableSetColumnIndex(1);
		ImGui::Text(std::to_string(_maxY).c_str());
		ImGui::TableSetColumnIndex(2);
		ImGui::Text(std::to_string(_maxZ).c_str());

		ImGui::EndTable();
	}

	ImGui::Text("Avg");
	if (ImGui::BeginTable("Min", 3)) {

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text(_data->columnX.c_str());
		ImGui::TableSetColumnIndex(1);
		ImGui::Text(_data->columnY.c_str());
		ImGui::TableSetColumnIndex(2);
		ImGui::Text(_data->columnZ.c_str());

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text(std::to_string(_avgX).c_str());
		ImGui::TableSetColumnIndex(1);
		ImGui::Text(std::to_string(_avgY).c_str());
		ImGui::TableSetColumnIndex(2); 
		ImGui::Text(std::to_string(_avgZ).c_str());
	
		ImGui::EndTable();
	}

	ImGui::End();
}

void MinMaxAvgTable::Cache() {
	if (_cached) { return; }

	auto& columnX = _data->GetColumnX();
	auto& columnY = _data->GetColumnY();
	auto& columnZ = _data->GetColumnZ();

	for (auto& i : columnX) {
		if (i.IsNum()) {
			_minX = std::min(_minX, i.vFloat);
			_maxX = std::max(_minX, i.vFloat);
			_avgX += i.vFloat;
		}
	}
	_avgX /= columnX.size();

	for (auto& i : columnY) {
		if (i.IsNum()) {
			_minY = std::min(_minY, i.vFloat);
			_maxY = std::max(_minY, i.vFloat);
			_avgY += i.vFloat;
		}
	}
	_avgY /= columnY.size();

	for (auto& i : columnZ) {
		if (i.IsNum()) {
			_minZ = std::min(_minZ, i.vFloat);
			_maxZ = std::max(_minZ, i.vFloat);
			_avgZ += i.vFloat;
		}
	}
	_avgZ /= columnZ.size();

	_cached = true;
}
