#pragma once
#include <BaseClasses/AppObject.h>
#include <AdditionalStd/DataFrame.h>
#include <AdditionalStd/vec3.h>


class Data : public AppObject, public DataFrame {
private:
	void OnStart();

public:
	bool isReady = false;

	float radius = 1;
	vec3f userScale = vec3f(1);
	std::string columnX = "None";
	std::string columnY = "None";
	std::string columnZ = "None";
	std::string columnTarget = "None";

	std::vector<DataFrameCell>& GetColumnX();
	std::vector<DataFrameCell>& GetColumnY();
	std::vector<DataFrameCell>& GetColumnZ();
};
